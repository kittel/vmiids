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


MonitorParser::MonitorParser()  throw(MonitorParserException): ConsoleMonitor(MONITORDEVICE, MONITORSHELL){}

MonitorParser::~MonitorParser(){}

bool MonitorParser::isRunning() throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("isRunning called");
	std::string string;
	this->parseCommandOutput("info status", string);
	if(string.rfind("running") != std::string::npos) return true;
	else if(string.rfind("paused") != std::string::npos) return false;
	throw MonitorParserException();
}

void MonitorParser::pauseVM() throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("pauseVM called");
	std::string string;
	this->parseCommandOutput("stop", string);
}

void MonitorParser::resumeVM() throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("resumeVM called");
	std::string string;
	this->parseCommandOutput("c", string);
}

void MonitorParser::help(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("help called");
	this->parseCommandOutput("help", helptext);
}


void MonitorParser::infoHelp(std::string &helptext) throw(MonitorParserException){
	LIBVMI_DEBUG_MSG("infoHelp called");
	this->parseCommandOutput("info help", helptext);
}


}

