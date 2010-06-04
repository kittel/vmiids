#include "MonitorParser.h"

#include <stdio.h>

namespace libVMI {

#define MONITORDEVICE "/dev/ttyS1"
#define MONITORSHELL  "(qemu)"

MonitorParser::MonitorParser() : ConsoleMonitor(MONITORDEVICE, MONITORSHELL){}

MonitorParser::~MonitorParser(){}

bool MonitorParser::isRunning(){
	printf("Test!\n");
	std::string string;
	this->parseCommandOutput("info status", string);
	printf("Test2!\n");

	if(string.rfind("running") != std::string::npos){
		return true;
	}
	return false;
}

void MonitorParser::pauseVM(){
	std::string string;
	this->parseCommandOutput("stop", string);
}

void MonitorParser::resumeVM(){
	std::string string;
	this->parseCommandOutput("c", string);
}

}

