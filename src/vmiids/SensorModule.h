/*
 * SensorModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef SENSORMODULE_H_
#define SENSORMODULE_H_

#include "Module.h"
#include "OutputModule.h"

#include "vmiids/util/Mutex.h"

namespace vmi {

class SensorModule : public vmi::Module, protected OutputModule{
private:
	static std::map<std::string, vmi::SensorModule *> modules;
	static vmi::Mutex mutex;
public:
		SensorModule(std::string moduleName);
		virtual ~SensorModule();

		static vmi::SensorModule *getSensorModule(std::string sensorModuleName);

		static void killInstances();
};

}

#define GETSENSORMODULE(variable, modulename) \
		variable = dynamic_cast<modulename *> (vmi::SensorModule::getSensorModule(QUOTE(modulename))); \
		if (!variable) { \
			throw vmi::DependencyNotFoundException(QUOTE(modulename)); \
		}

#endif /* SENSORMODULE_H_ */
