/*
 * NotificationModule.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: kittel
 */

#include "NotificationModule.h"

#include "VmiIDS.h"

namespace vmi {

std::map<std::string, vmi::NotificationModule *> NotificationModule::notificationModules;
pthread_mutex_t NotificationModule::notificationModuleMutex = PTHREAD_MUTEX_INITIALIZER;

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

	pthread_mutex_lock(&notificationModuleMutex);
	notificationModules[moduleName] = this;
	pthread_mutex_unlock(&notificationModuleMutex);
};

NotificationModule::~NotificationModule(){
	pthread_mutex_lock(&notificationModuleMutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			this->notificationModules.begin(); it
			!= this->notificationModules.end(); ++it) {
		if (it->first.compare(this->getName()) == 0) {
			this->notificationModules.erase(it);
		}
	}
	pthread_mutex_unlock(&notificationModuleMutex);
}

void NotificationModule::debug(std::string module, std::string message){
	pthread_mutex_lock(&notificationModuleMutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			notificationModules.begin(); it
			!= notificationModules.end(); ++it) {
		it->second->doDebug(module, message);
	}
	pthread_mutex_unlock(&notificationModuleMutex);
}

void NotificationModule::info(std::string module, std::string message){
	pthread_mutex_lock(&notificationModuleMutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			notificationModules.begin(); it
			!= notificationModules.end(); ++it) {
		it->second->doInfo(module, message);
	}
	pthread_mutex_unlock(&notificationModuleMutex);
}

void NotificationModule::warn(std::string module, std::string message){
	pthread_mutex_lock(&notificationModuleMutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			notificationModules.begin(); it
			!= notificationModules.end(); ++it) {
		it->second->doWarn(module, message);
	}
	pthread_mutex_unlock(&notificationModuleMutex);
}

void NotificationModule::error(std::string module, std::string message){
	pthread_mutex_lock(&notificationModuleMutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			notificationModules.begin(); it
			!= notificationModules.end(); ++it) {
		it->second->doError(module, message);
	}
	pthread_mutex_unlock(&notificationModuleMutex);
}

void NotificationModule::critical(std::string module, std::string message){
	pthread_mutex_lock(&notificationModuleMutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			notificationModules.begin(); it
			!= notificationModules.end(); ++it) {
		it->second->doCritical(module, message);
	}
	pthread_mutex_unlock(&notificationModuleMutex);
}

void NotificationModule::alert(std::string module, std::string message){
	pthread_mutex_lock(&notificationModuleMutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			notificationModules.begin(); it
			!= notificationModules.end(); ++it) {
		it->second->doAlert(module, message);
	}
	pthread_mutex_unlock(&notificationModuleMutex);
}


}
