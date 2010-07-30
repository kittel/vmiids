/*
 * SensorModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef SENSORMODULE_H_
#define SENSORMODULE_H_

#include "Module.h"

namespace vmi {

class SensorModule : public vmi::Module{
	public:
		SensorModule(std::string moduleName) : vmi::Module(moduleName) {};
		virtual void initSensorModule() = 0;
};

}

#include "VmiIDS.h"

#define ADDDYNAMICSENSORMODULE(classname, line) class CONCAT(proxy, line) { \
	public: \
	CONCAT(proxy, line)(){ vmi::VmiIDS::getInstance()->enqueueSensorModule(new classname);  } \
}; \
static CONCAT(proxy, line) CONCAT(p, line);

#endif /* SENSORMODULE_H_ */
