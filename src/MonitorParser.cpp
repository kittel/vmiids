#include "MonitorParser.h"

#include <stdio.h>

#define DEBUG

#ifdef DEBUG
#define VERBOSE "MonitorParser"
#endif /* DEBUG */
#include "Debug.h"


namespace libVMI {

#define MONITORDEVICE "/dev/ttyS1"
#define MONITORSHELL  "(qemu)"

MonitorParser::MonitorParser() : ConsoleMonitor(MONITORDEVICE, MONITORSHELL){}

MonitorParser::~MonitorParser(){}

bool MonitorParser::isRunning(){
	LIBVMI_DEBUG_MSG("isRunning called");
	std::string string;
	this->parseCommandOutput("info status", string);

	if(string.rfind("running") != std::string::npos){
		return true;
	}
	return false;
}

void MonitorParser::pauseVM(){
	LIBVMI_DEBUG_MSG("pauseVM called");
	std::string string;
	this->parseCommandOutput("stop", string);
}

void MonitorParser::resumeVM(){
	LIBVMI_DEBUG_MSG("resumeVM called");
	std::string string;
	this->parseCommandOutput("c", string);
}

void MonitorParser::help(std::string &helptext){
	LIBVMI_DEBUG_MSG("help called");
	this->parseCommandOutput("help", helptext);
}


void MonitorParser::infoHelp(std::string &helptext){
	LIBVMI_DEBUG_MSG("infoHelp called");
	this->parseCommandOutput("info help", helptext);
}


}

