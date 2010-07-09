#include "Shell.h"

#include <pthread.h>
#include <signal.h>

#include <string.h>
#include <iostream>

#define SHELLDEVICE "/dev/ttyS2"
#define LOGINSHELL "login:"

#define DEBUG

#ifdef DEBUG
#define VERBOSE "Shell"
#endif /* DEBUG */
#include "Debug.h"

namespace libVMI {

Shell::Shell() : ConsoleMonitor(SHELLDEVICE, LOGINSHELL){
	this->threadRunning = false;
}

Shell::~Shell(){
}

void Shell::signal_handler(int signum){
	signum = 0;
	pthread_exit(NULL);
}

void Shell::startShell(void){
	if(this->threadRunning) return;
	pthread_create(&this->readThread, NULL, &Shell::shellRead, (void *) this);
	pthread_create(&this->writeThread, NULL, &Shell::shellWrite, (void *) this);
	this->threadRunning = true;
}

void Shell::stopShell(void){
	while(this->threadRunning){
		pthread_yield();
	}

	pthread_kill(this->readThread, SIGTERM);
	pthread_kill(this->writeThread, SIGTERM);
	pthread_join(this->readThread, NULL);
	pthread_join(this->writeThread, NULL);


	LIBVMI_DEBUG_MSG("Shell Terminated");
}

void* Shell::shellRead(void * ptr){
	struct sigaction sa;
	sa.sa_handler = Shell::signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	LIBVMI_DEBUG_MSG("Signalhandler for shellRead installed");

	Shell * this_p = (Shell *) ptr;
	std::string string;

	while(this_p->threadRunning){
		try{
			this_p->parseOutput(string);
		}catch(ConsoleMonitorException &e){
			break;
		}
		if(!string.empty()){
			std::cout << string << std::flush;
			string.clear();
		}
		pthread_yield();
	}
	
	pthread_exit(NULL);	
}

void* Shell::shellWrite(void * ptr){
	struct sigaction sa;
	sa.sa_handler = Shell::signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	LIBVMI_DEBUG_MSG("Signalhandler for shellWrite installed");

	Shell * this_p = (Shell *) ptr;
	char string[256] = {0};
	int readLength = 0;

	while(this_p->threadRunning){
		std::cin.getline(string,256);
		readLength = std::cin.gcount();
		if(readLength < 0) {
			LIBVMI_DEBUG_MSG("Nothing read");
			continue;
		}
		if (memcmp("satan", string, 5) == 0) this_p->threadRunning = false;
		else this_p->sendCommand(string);
		memset(string, 0, 256);
		pthread_yield();
	}
	
	pthread_exit(NULL);	
}

}
