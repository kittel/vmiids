#include "ConsoleMonitor.h"

#include <signal.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <exception>
#include <inttypes.h>

//#define DEBUG

#ifdef DEBUG
#define VERBOSE "ConsoleMonitor"
#endif /* DEBUG */
#include "Debug.h"

namespace vmi {

void *ConsoleMonitor::readMonitor(void *ptr) {

	ConsoleMonitor * this_p = (ConsoleMonitor *) ptr;

	int fd = -1;
	char buffer = 0;
	int readcount;

	if ((fd = open(this_p->consoleName.c_str(), O_RDONLY)) < 0){
		this_p->threadRunning = false;
		this_p->threadStarted = -1;
		return NULL;
	}
	struct termios tty;
	if(tcgetattr(fd, &tty) < 0){
		this_p->threadRunning = false;
		this_p->threadStarted = -1;
		if (fd >= 0)
			close(fd);
		return NULL;
	}
	tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR
			| ICRNL | IXON);
	tty.c_oflag &= ~OPOST;
	tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	tty.c_cflag &= ~(CSIZE | PARENB);
	tty.c_cflag |= CS8;

	tty.c_cc[VMIN] = 0;
	tty.c_cc[VTIME] = 0;

	if(tcsetattr(fd, TCSAFLUSH, &tty) < 0){
		this_p->threadRunning = false;
		this_p->threadStarted = -1;
		if (fd >= 0)
			close(fd);
		return NULL;
	}

//	if(lseek(fd, 0,SEEK_END ) < 0){
//		printf("lseek\n");
//		this_p->threadRunning = false;
//		this_p->threadStarted = -1;
//		if (fd >= 0)
//			close(fd);
//		return NULL;
//	}

	this_p->threadStarted = 1;

	while (this_p->threadRunning) {
		readcount = read(fd, &buffer, 1);
		if (readcount > 0) {
			pthread_mutex_lock(&(this_p->queuemutex));
			this_p->queuecontainer.push(buffer);
			pthread_mutex_unlock(&(this_p->queuemutex));
		} else if (readcount < 0) {
			this_p->threadRunning = false;
			this_p->threadStarted = -1;
			if (fd >= 0)
				close(fd);
			return NULL;
		}
	}
	return NULL;
}

ConsoleMonitor::ConsoleMonitor() throw(ConsoleMonitorException) {

	this->threadStarted = 0;

	LIBVMI_DEBUG_MSG("Empty Constructor finished");
}


ConsoleMonitor::ConsoleMonitor(std::string consoleString,
		std::string shellString) throw(ConsoleMonitorException) {

	this->initConsoleMonitor(consoleString, shellString);

	LIBVMI_DEBUG_MSG("Constructor finished");

}

void ConsoleMonitor::initConsoleMonitor(std::string consoleString,
		std::string shellString) throw(ConsoleMonitorException) {

	this->consoleName = consoleString;
	this->monitorShell = shellString;
	this->threadStarted = false;

	pthread_mutex_init(&(this->queuemutex), NULL);
	this->threadRunning = true;

	pthread_create(&(this->thread), NULL, ConsoleMonitor::readMonitor,
			(void *) this);

	while (!this->threadStarted){
		sched_yield();
	}
	if (this->threadStarted == -1 || !this->threadRunning)
		throw ConsoleMonitorException();


	LIBVMI_DEBUG_MSG("Initialize finished");
}

ConsoleMonitor::~ConsoleMonitor(){
	this->killThread();
	LIBVMI_DEBUG_MSG("Destructor finished");
}

void ConsoleMonitor::killThread(void) throw(ConsoleMonitorException) {
	LIBVMI_DEBUG_MSG("Kill Thread");
	this->threadRunning = false;
	pthread_join(this->thread, NULL);
	pthread_mutex_destroy(&(this->queuemutex));
}

int ConsoleMonitor::sendCommand(const char * command) throw(ConsoleMonitorException) {
	if (!this->threadRunning)
		throw ConsoleMonitorException();
	int fd_to_qemu;
	fd_to_qemu = open(this->consoleName.c_str(), O_WRONLY);
	if (fd_to_qemu < 0) {
		LIBVMI_DEBUG_MSG("open %s writeable failed\n", this->consoleName.c_str());
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
		size_t crString;
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

	while (output[0] == '\n' || output[0] == '\r')
		output.erase(0, 1);

	LIBVMI_DEBUG_MSG("Complete String:\n%s\n", output.c_str());
	output.resize(output.rfind(this->monitorShell));
	LIBVMI_DEBUG_MSG("Truncated String:\n%s\n", output.c_str());
}

}
