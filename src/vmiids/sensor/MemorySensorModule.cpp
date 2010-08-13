/*
 * MemorySensorModule.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#include "MemorySensorModule.h"

#include <sstream>
#include <cstdlib>

ADDMODULE(MemorySensorModule);

Memtool* MemorySensorModule::memtool = NULL;
QCoreApplication* MemorySensorModule::app = NULL;

MemorySensorModule::MemorySensorModule() :
			 SensorModule("MemorySensorModule"), null(0){

    atexit(MemorySensorModule::stopMemtool);

    if(app == NULL) app = new QCoreApplication(null, NULL);
    if(memtool == NULL) memtool = new Memtool();

	//Get NotificationModule
	GETNOTIFICATIONMODULE(notify, ShellNotificationModule);

	GETOPTION(memtooldPath, this->memtooldPath);
	GETOPTION(libmemtoolPath, this->libmemtoolPath);
	GETOPTION(memtoolScriptPath, this->memtoolScriptPath);
	GETOPTION(savedDebugingSymbols, this->savedDebugingSymbols);
	GETOPTION(memdumpFile, this->memdumpFile);

	if(!memtool->isDaemonRunning()){
		bool daemonStart = false;
		notify->debug(this) << "Trying to start memtool..."
    		<< ((daemonStart = memtool->daemonStart()) ? "Success" : "Failed") << std::endl;
		if (daemonStart){
			while(!memtool->isDaemonRunning()){
				sched_yield();
			}

			std::stringstream loadSymbolsCmd;
			loadSymbolsCmd << "symbols load " << this->savedDebugingSymbols;
			notify->debug(this) << "Trying to load symbols..."
			    		<< ((daemonStart = (memtool->eval(loadSymbolsCmd.str().c_str()) == 0)) ? "Success" : "Failed") << std::endl;
			if(!daemonStart) throw MemtoolNotRunningException();

			notify->debug(this) << "Trying to to load memory image..."
			    		<< ((daemonStart = memtool->memDumpLoad(this->memdumpFile.c_str())) ? "Success" : "Failed") << std::endl;
			if(!daemonStart) throw MemtoolNotRunningException();
		}else{
			throw MemtoolNotRunningException();
		}
    }
	return;
    sleep(1);

    if (memtool->isDaemonRunning() && memtool->connectToDaemon() == 0) {
		notify->debug(this) << "Memtool running" << std::endl;
		notify->debug(this) << "Trying to load memdump..."
				<< ((memtool->memDumpLoad("/dev/vda")) ? "Success" : "Failed") << std::endl;
	}
}

MemorySensorModule::~MemorySensorModule() {
}

void MemorySensorModule::stopMemtool(void){
	if(memtool != NULL){
		if (memtool->isDaemonRunning()) {
			memtool->daemonStop();
		}
		delete (memtool);
		memtool = NULL;

	}

	//Deleting the qt Application causes an segfault. So ... don´t delete.
	//TODO FIXME
	if(app != NULL){
		//delete (app);
		//app = NULL;
	}
}

void MemorySensorModule::initSensorModule(){

}

void MemorySensorModule::getProcessList(std::map<uint32_t, MemtoolProcess> &memtoolProcessMap){
	std::string scriptResult;

	this->clearFSCache();

	std::stringstream runTasklistScript;
	runTasklistScript << "sc " << this->memtoolScriptPath << "/tasklist.js";
	notify->debug(this) << "Trying to read tasklist symbols..." << std::endl;

    if (memtool->isDaemonRunning() &&
    		memtool->eval(runTasklistScript.str().c_str()) == 0) {
		scriptResult = std::string(memtool->readAllStdOut().toStdString());
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
