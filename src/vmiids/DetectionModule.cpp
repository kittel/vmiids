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
	vmi::Module(moduleName),
	vmi::OutputModule(moduleName){
	intrusionDetected = false;

	debug << "Loading Module" << std::endl;

	mutex.lock();
	modules[moduleName] = this;
	mutex.unlock();
};

vmi::DetectionModule::~DetectionModule(){
	debug << "Unloading Module" << std::endl;
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, DetectionModule*>::iterator it =
			this->modules.begin(); it
			!= this->modules.end(); ++it) {
		if (it->first.compare(this->getName()) == 0) {
			this->modules.erase(it);
		}
	}
};

vmi::DetectionModule *vmi::DetectionModule::getDetectionModule(std::string moduleName) {
	vmi::MutexLocker lock(&mutex);
    if(modules.find(moduleName) == modules.end()){
    	return NULL;
    }
   	return modules[moduleName];
}

bool vmi::DetectionModule::getThreadLevel(){
	return intrusionDetected;
}

void vmi::DetectionModule::killInstances(){
	while (!modules.empty()) {
		delete modules.begin()->second;
	}
}

}
