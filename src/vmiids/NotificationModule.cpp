/*
 * NotificationModule.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: kittel
 */

#include "NotificationModule.h"

#include "vmiids/util/MutexLocker.h"

#include "VmiIDS.h"

namespace vmi {

std::map<std::string, vmi::NotificationModule *> NotificationModule::modules;
vmi::Mutex NotificationModule::mutex;

NotificationModule::NotificationModule(std::string moduleName): Module(moduleName) {
	std::string debugLevelString;
	try{
		GETOPTION(debugLevel, debugLevelString);
		if (debugLevelString.compare("INFO") == 0) {
			this->debugLevel = vmi::OUTPUT_INFO;
		} else if (debugLevelString.compare("DEBUG") == 0) {
			this->debugLevel = vmi::OUTPUT_DEBUG;
		} else if (debugLevelString.compare("WARN") == 0) {
			this->debugLevel = vmi::OUTPUT_WARN;
		} else if (debugLevelString.compare("ERROR") == 0) {
			this->debugLevel = vmi::OUTPUT_ERROR;
		} else if (debugLevelString.compare("CRITICAL") == 0) {
			this->debugLevel = vmi::OUTPUT_CRITICAL;
		} else if (debugLevelString.compare("ALERT") == 0) {
			this->debugLevel = vmi::OUTPUT_ALERT;
		} else {
			this->debugLevel = vmi::OUTPUT_INFO;
		}
	}catch(OptionNotFoundException &e){
		this->debugLevel = vmi::OUTPUT_INFO;
	}

	mutex.lock();
	modules[moduleName] = this;
	mutex.unlock();
};

NotificationModule::~NotificationModule(){
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			this->modules.begin(); it
			!= this->modules.end(); ++it) {
		if (it->first.compare(this->getName()) == 0) {
			this->modules.erase(it);
		}
	}
}

void NotificationModule::debug(std::string module, std::string message){
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			modules.begin(); it
			!= modules.end(); ++it) {
		it->second->doDebug(module, message);
	}
}

void NotificationModule::info(std::string module, std::string message){
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			modules.begin(); it
			!= modules.end(); ++it) {
		it->second->doInfo(module, message);
	}
}

void NotificationModule::warn(std::string module, std::string message){
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			modules.begin(); it
			!= modules.end(); ++it) {
		it->second->doWarn(module, message);
	}
}

void NotificationModule::error(std::string module, std::string message){
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			modules.begin(); it
			!= modules.end(); ++it) {
		it->second->doError(module, message);
	}
}

void NotificationModule::critical(std::string module, std::string message){
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			modules.begin(); it
			!= modules.end(); ++it) {
		it->second->doCritical(module, message);
	}
}

void NotificationModule::alert(std::string module, std::string message){
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			modules.begin(); it
			!= modules.end(); ++it) {
		it->second->doAlert(module, message);
	}
}

void NotificationModule::killInstances(){
	while (!modules.empty()) {
		delete modules.begin()->second;
	}
}

}
