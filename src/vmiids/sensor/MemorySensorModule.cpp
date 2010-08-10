/*
 * MemorySensorModule.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#include "MemorySensorModule.h"

#include <sstream>

ADDDYNAMICSENSORMODULE(MemorySensorModule, __LINE__)
;

MemorySensorModule::MemorySensorModule() :
			SensorModule("MemorySensorModule") {

	//Get NotificationModule
	GETNOTIFICATIONMODULE(notify, ShellNotificationModule);

	GETOPTION(memtooldPath, this->memtooldPath);
	GETOPTION(memtoolScriptPath, this->memtoolScriptPath);
	GETOPTION(savedDebugingSymbols, this->savedDebugingSymbols);
	GETOPTION(memdumpFile, this->memdumpFile);

	//Start Memtool
	//Memtool Daemon must be in $PATH
//	The following section is commented because currently no symbols can be loaded with libmemtool.
//    if(!memtool.isDaemonRunning()){
//            std::cout << "Trying to start memtool...";
//            if(memtool.daemonStart()){
//                    std::cout << "Success" << std::endl;
//            }else{
//                    std::cout << "Failed" << std::endl;
//            }
//    }

    if (memtool.isDaemonRunning()) {
		notify->debug(this) << "Memtool running" << std::endl;
		notify->debug(this) << "Trying to load memdump..."
				<< ((memtool.memDumpLoad("/dev/vda")) ? "Success" : "Failed") << std::endl;
//		notify->debug(this)
//				<< memtool.eval(
//						"sc /home/idsvm/workspace/DA/memorytool_chrschn/memtoold/scripts/tasklist.js").toStdString()
//				<< std::endl;
	}

}

MemorySensorModule::~MemorySensorModule() {
	//Stop Memtoold
	if (memtool.isDaemonRunning()) {
		notify->debug(this) << "Trying to stop memtool..." << ((memtool.daemonStop()) ? "Success" : "Failed") << std::endl;
	}
}


void MemorySensorModule::initSensorModule(){

}

void MemorySensorModule::runScript(std::string &scriptResult, std::string scriptName){
	std::stringstream command;

	std::string data;
	FILE *stream;
	char buffer[1024];

	command << "echo \"sc " << this->memtoolScriptPath << "/" << scriptName << "\" | "
			<< this->memtooldPath << " -l " << this->savedDebugingSymbols
			<< " -m " << this->memdumpFile << " 2>&1";

	stream = popen(command.str().c_str(), "r");
	while (fgets(buffer, 1024, stream) != NULL)
		data.append(buffer);
	pclose(stream);

	int firstChar;
	int lastChar;

	lastChar = data.rfind(">>>");

	firstChar = data.find(">>>");
	firstChar = data.find("\n", firstChar);
	firstChar++;

	scriptResult.append(data, firstChar, lastChar - firstChar);
}

void MemorySensorModule::getProcessList(std::map<uint32_t, MemtoolProcess> &memtoolProcessMap){
	std::string scriptResult;

	this->clearFSCache();

	this->runScript(scriptResult, "tasklist.js");

	size_t oldNewlineSeparator = 0;
	size_t newlineSeparator = 0;

	oldNewlineSeparator = scriptResult.find("\n");
	oldNewlineSeparator = scriptResult.find("\n", oldNewlineSeparator + 1); //Find the third line ...

	size_t position1 = 0;

	std::string currentLine;

	oldNewlineSeparator = scriptResult.find("\n", oldNewlineSeparator) + 1;
	while((newlineSeparator = scriptResult.find("\n", oldNewlineSeparator)) != std::string::npos){
		currentLine = scriptResult.substr(oldNewlineSeparator, newlineSeparator - oldNewlineSeparator);
		MemtoolProcess process;
		process.pid = atoi(currentLine.substr(5, 8).c_str());
		process.processName = currentLine.substr(23, 17);
		position1 = process.processName.find("\"");
		process.processName = process.processName.substr(0, position1);
		memtoolProcessMap.insert(std::pair<uint32_t, MemtoolProcess>(process.pid, process));
		oldNewlineSeparator = newlineSeparator+1;
	}
	return;
}


bool MemorySensorModule::clearFSCache() {
	bool result = true;

	// To clear the file system cache and get the latest version of the rootkitvms file system.
	result = (system("sync") == -1) ? false : true;
	result = (system(this->clearCacheCommand.c_str()) == -1) ? false : true;
	return result;
}
