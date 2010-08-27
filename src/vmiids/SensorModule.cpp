/*
 * SensorModule.cpp
 *
 *  Created on: Aug 26, 2010
 *      Author: kittel
 */

#include "SensorModule.h"

#include "vmiids/util/MutexLocker.h"

namespace vmi {

std::map<std::string, vmi::SensorModule *> vmi::SensorModule::modules;
vmi::Mutex vmi::SensorModule::mutex;

vmi::SensorModule::SensorModule(std::string moduleName) :
					vmi::Module(moduleName),
					vmi::OutputModule(moduleName){

	debug << "Loading Module" << std::endl;

	mutex.lock();
	modules[moduleName] = this;
	mutex.unlock();
};

vmi::SensorModule::~SensorModule(){
	debug << "Unloading Module" << std::endl;
	vmi::MutexLocker lock(&mutex);
	for (std::map<std::string, SensorModule*>::iterator it =
			this->modules.begin(); it
			!= this->modules.end(); ++it) {
		if (it->first.compare(this->getName()) == 0) {
			this->modules.erase(it);
		}
	}
};

vmi::SensorModule *vmi::SensorModule::getSensorModule(std::string moduleName) {
	vmi::MutexLocker lock(&mutex);
    if(modules.find(moduleName) == modules.end()){
    	return NULL;
    }
   	return modules[moduleName];
}

void SensorModule::killInstances(){
	while (!modules.empty()) {
		delete modules.begin()->second;
	}
}

}
