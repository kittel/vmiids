/*
 * MemorySensorModule.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#include "MemorySensorModule.h"

#include <sstream>
#include <cstdlib>

#include <memtool/memtool.h>

ADDDYNAMICSENSORMODULE(MemorySensorModule);

MemorySensorModule::MemorySensorModule() :
			SensorModule("MemorySensorModule") {

	//Get NotificationModule
	GETNOTIFICATIONMODULE(notify, ShellNotificationModule);

	GETOPTION(memtooldPath, this->memtooldPath);
	GETOPTION(libmemtoolPath, this->libmemtoolPath);
	GETOPTION(memtoolScriptPath, this->memtoolScriptPath);
	GETOPTION(savedDebugingSymbols, this->savedDebugingSymbols);
	GETOPTION(memdumpFile, this->memdumpFile);

	//Start Memtool
	//Memtool Daemon must be in $PATH
	return;
	Memtool memtool;

	if(!memtool.isDaemonRunning()){
		notify->debug(this) << "Trying to start memtool..."
    		<< ((memtool.daemonStart()) ? "Success" : "Failed") << std::endl;

    		// Load Symbols with eval "symbols load this->savedDebugingSymbols ...
//    	std::stringstream memtooldCommand;
//    	memtooldCommand << "LD_LIBRARY_PATH=" << this->libmemtoolPath << " "
//    			<< this->memtooldPath << " -d -l " << this->savedDebugingSymbols << " 2>&1 > /dev/null";
//    	notify->debug(this) << memtooldCommand.str() << std::endl;

//    	notify->debug(this) << "Trying to start memtool..."
//    		<< ((system(memtooldCommand.str().c_str())) ? "Success" : "Failed") << std::endl;
    }
    sleep(1);

    if (memtool.isDaemonRunning() && memtool.connectToDaemon() == 0) {
		notify->debug(this) << "Memtool running" << std::endl;
		notify->debug(this) << "Trying to load memdump..."
				<< ((memtool.memDumpLoad("/dev/vda")) ? "Success" : "Failed") << std::endl;
	}
}

MemorySensorModule::~MemorySensorModule() {
	std::cout << "MemorySensorModule Destructor called!" << std::endl;
	return;
	Memtool memtool;
	std::cout << "Trying to stop memtool" << std::endl;
	if (memtool.isDaemonRunning() && memtool.connectToDaemon() == 0) {
		std::cout << "Trying to stop memtool..." << ((memtool.daemonStop()) ? "Success" : "Failed") << std::endl;
		memtool.disconnectFromDaemon();
	}
}

void MemorySensorModule::initSensorModule(){

}

void MemorySensorModule::getProcessList(std::map<uint32_t, MemtoolProcess> &memtoolProcessMap){
	std::string scriptResult;

	this->clearFSCache();

	Memtool memtool;
    if (memtool.isDaemonRunning() &&
    		memtool.connectToDaemon() == 0 &&
    		memtool.eval("sc /home/idsvm/workspace/DA/memorytool_chrschn/memtoold/scripts/tasklist.js") == 0) {
		scriptResult = memtool.readAllBinary().data();
		std::cout << scriptResult << std::endl;
	}else{
		throw MemtoolNotRunningException();
	}

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
