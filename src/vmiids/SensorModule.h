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
		std::string getName(){ return this->moduleName; };
};

#endif /* SENSORMODULE_H_ */
