/*
 * SensorModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef SENSORMODULE_H_
#define SENSORMODULE_H_

#include <string>

class SensorModule{
	private:
		std::string moduleName;

	public:
		SensorModule(std::string moduleName){ this->moduleName = moduleName;};
		virtual void initSensorModule() = 0;
		std::string getName(){ return this->moduleName; };
};

#include "VmiIDS.h"

#define ADDDYNAMICSENSORMODULE(classname, line) class CONCAT(proxy, line) { \
	public: \
	CONCAT(proxy, line)(){ VmiIDS::getInstance()->enqueueSensorModule(new classname);  } \
}; \
static CONCAT(proxy, line) CONCAT(p, line);

#endif /* SENSORMODULE_H_ */
