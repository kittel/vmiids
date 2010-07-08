#include "ConsoleMonitor.h"

#include <signal.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <exception>

//#define DEBUG

#ifdef DEBUG
#define VERBOSE "ConsoleMonitor"
#endif /* DEBUG */
#include "Debug.h"

namespace libVMI {

void ConsoleMonitor::signal_handler(int signum) {
	LIBVMI_DEBUG_MSG("Signalhandler called");
	pthread_exit(0);
}

void *ConsoleMonitor::readMonitor(void *ptr) {

	struct sigaction sa;
	sa.sa_handler = ConsoleMonitor::signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	LIBVMI_DEBUG_MSG("Signalhandler installed");

	ConsoleMonitor * arguments = (ConsoleMonitor *) ptr;
	int fd_to_qemu;
	char buffer = 0;
	int readcount;

	fd_to_qemu = open(arguments->consoleName, O_RDONLY);
	if (fd_to_qemu < 0) {
		LIBVMI_WARN_MSG("Open %s readable failed", arguments->consoleName);
		arguments->threadRunning = false;
	}

	if (arguments->threadRunning) {
		struct termios tty;
		tcgetattr(fd_to_qemu, &tty);

		tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR
				| ICRNL | IXON);
		tty.c_oflag &= ~OPOST;
		tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
		tty.c_cflag &= ~(CSIZE | PARENB);
		tty.c_cflag |= CS8;

		tty.c_cc[VMIN] = 0;
		tty.c_cc[VTIME] = 0;

		tcsetattr(fd_to_qemu, TCSAFLUSH, &tty);
	}

	lseek(fd_to_qemu, 0,SEEK_END );
	arguments->threadStarted = true;

	while (arguments->threadRunning) {
		readcount = read(fd_to_qemu, &buffer, 1);
		if (readcount > 0) {
			pthread_mutex_lock(&(arguments->queuemutex));
			arguments->queuecontainer.push(buffer);
			pthread_mutex_unlock(&(arguments->queuemutex));
		} else if (readcount < 0) {
			arguments->threadRunning = false;
			close(fd_to_qemu);
			pthread_exit(0);
		}
	}
	if (fd_to_qemu > 0)
		close(fd_to_qemu);
	pthread_exit(0);
}

ConsoleMonitor::ConsoleMonitor(const char* consoleString,
		const char* shellString) throw(ConsoleMonitorException) {

	this->consoleName = consoleString;
	this->monitorShell = shellString;
	this->threadStarted = false;

	pthread_mutex_init(&(this->queuemutex), NULL);
	this->threadRunning = true;

	pthread_create(&(this->thread), NULL, ConsoleMonitor::readMonitor,
			(void *) this);
	while (!this->threadStarted) {
		sched_yield();
	}

	if (!this->threadRunning)
		throw ConsoleMonitorException();

	LIBVMI_DEBUG_MSG("Constructor finished");

}

ConsoleMonitor::~ConsoleMonitor(){
	this->killThread();
	LIBVMI_DEBUG_MSG("Destructor finished");
}

void ConsoleMonitor::killThread(void) throw(ConsoleMonitorException) {
	LIBVMI_DEBUG_MSG("Kill Thread");
	this->threadRunning = false;
	pthread_kill(this->thread, SIGTERM);
	pthread_join(this->thread, NULL);
	pthread_mutex_destroy(&(this->queuemutex));
}

int ConsoleMonitor::sendCommand(const char * command) throw(ConsoleMonitorException) {
	if (!this->threadRunning)
		throw ConsoleMonitorException();
	int fd_to_qemu;
	fd_to_qemu = open(this->consoleName, O_WRONLY);
	if (fd_to_qemu < 0) {
		LIBVMI_DEBUG_MSG("open %s writeable failed\n", this->consoleName);
		return -1;
	}
	LIBVMI_DEBUG_MSG("Writing command: %s", command);
	write(fd_to_qemu, command, strlen(command));
	write(fd_to_qemu, "\n", 1);
	close(fd_to_qemu);
	return 0;
}

void ConsoleMonitor::parseOutput(std::string &output) throw(ConsoleMonitorException){
	if (!this->threadRunning)
		throw ConsoleMonitorException();
	output.clear();
	while (!this->queuecontainer.empty()) {
		pthread_mutex_lock(&(this->queuemutex));
		output.append(&this->queuecontainer.front(), 1);
		this->queuecontainer.pop();
		pthread_mutex_unlock(&(this->queuemutex));
	}
}

void ConsoleMonitor::parseCommandOutput(std::string command,
		std::string &output) throw(ConsoleMonitorException){
	this->parseCommandOutput(command.c_str(), output);
}

void ConsoleMonitor::parseCommandOutput(const char *command,
		std::string &output) throw(ConsoleMonitorException){
	if (!this->threadRunning)
		throw ConsoleMonitorException();
	if (this->threadRunning)
		LIBVMI_DEBUG_MSG("Thread is running...");
	//Parse everything which was printed before the command was sent.

	while (!this->queuecontainer.empty()) {
		pthread_mutex_lock(&(this->queuemutex));
		this->queuecontainer.pop();
		pthread_mutex_unlock(&(this->queuemutex));
	}

	//Send command
	LIBVMI_DEBUG_MSG("sendCommand...");
	this->sendCommand(command);

	LIBVMI_DEBUG_MSG("parseCommand...");
	output.clear();
	//Delete command from result
	while (output.size() < strlen(command) || (output.rfind(command) == std::string::npos)) {
		while (this->queuecontainer.empty())
			sched_yield();
		pthread_mutex_lock(&(this->queuemutex));
		output.append(&this->queuecontainer.front(), 1);
		int crString;
		if((crString = output.rfind(" \r")) != std::string::npos) output.replace(crString, 2, "");
		this->queuecontainer.pop();
		pthread_mutex_unlock(&(this->queuemutex));
	}
	LIBVMI_DEBUG_MSG("Throwing away:\n%s\n", output.c_str());
	output.clear();

	LIBVMI_DEBUG_MSG("parseResult...");
	while (output.rfind(this->monitorShell) == std::string::npos) {
		while (this->queuecontainer.empty())
			sched_yield();
		pthread_mutex_lock(&(this->queuemutex));
		output.append(&this->queuecontainer.front(), 1);
		this->queuecontainer.pop();
		pthread_mutex_unlock(&(this->queuemutex));
	}
	LIBVMI_DEBUG_MSG("Complete String:\n%s\n", output.c_str());
	output.resize(output.rfind(this->monitorShell));
	LIBVMI_DEBUG_MSG("Truncated String:\n%s\n", output.c_str());
}

}
