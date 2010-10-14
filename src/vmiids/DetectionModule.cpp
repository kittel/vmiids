/*
 * DetectionModule.cpp
 *
 *  Created on: Aug 26, 2010
 *      Author: kittel
 */

#include "DetectionModule.h"

#include "vmiids/util/MutexLocker.h"

namespace vmi {

std::map<std::string, vmi::DetectionModule *> vmi::DetectionModule::modules;
vmi::Mutex vmi::DetectionModule::mutex;

vmi::DetectionModule::DetectionModule(std::string moduleName) :
	vmi::Module(moduleName), vmi::OutputModule(moduleName) {
	threatLevel = false;

	debug << "Loading Module" << std::endl;

	mutex.lock();
	modules[moduleName] = this;
	mutex.unlock();
}
;

vmi::DetectionModule::~DetectionModule() {
	debug << "Unloading Module" << std::endl;
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, DetectionModule*>::iterator it =
			this->modules.begin(); it != this->modules.end(); ++it) {
		if (it->first.compare(this->getName()) == 0) {
			this->modules.erase(it);
		}
	}
}
;

vmi::DetectionModule *vmi::DetectionModule::getDetectionModule(
		std::string moduleName) {
	vmi::MutexLocker lock(&mutex);
	if (modules.find(moduleName) == modules.end()) {
		return NULL;
	}
	return modules[moduleName];
}

float vmi::DetectionModule::getThreatLevel() {
	return threatLevel;
}

void vmi::DetectionModule::killInstances() {
	while (!modules.empty()) {
		delete modules.begin()->second;
	}
}

std::list<std::string> vmi::DetectionModule::getListOfDetectionModules() {
	vmi::MutexLocker lock(&mutex);
	std::list<std::string> detectionModules;
	for (std::map<std::string, DetectionModule*>::iterator it =
		modules.begin(); it != modules.end(); ++it) {
		detectionModules.push_back(it->first);
	}
	detectionModules.sort();
	return detectionModules;
}

float vmi::DetectionModule::getGlobalThreatLevel() {
	vmi::MutexLocker lock(&mutex);
	float threatLevel = 0;
	for (std::map<std::string, DetectionModule*>::iterator it =
			modules.begin(); it
			!= modules.end(); ++it) {
		threatLevel += (it->second)->getThreadLevel();
	}
	return threatLevel / modules.size();
}

}
