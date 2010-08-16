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

namespace vmi {

class SensorModule : public vmi::Module, protected OutputModule{
public:
		SensorModule(std::string moduleName) :
			vmi::Module(moduleName),
			vmi::OutputModule(moduleName){};
		virtual ~SensorModule(){};
		virtual void initSensorModule() = 0;
};

}

#include "Modintern.h"

#define GETSENSORMODULE(variable, modulename) \
		variable = dynamic_cast<modulename *> (vmi::VmiIDS::getInstance()->getSensorModule(QUOTE(modulename))); \
		if (!variable) { \
			throw vmi::DependencyNotFoundException(QUOTE(modulename)); \
		}

#endif /* SENSORMODULE_H_ */
