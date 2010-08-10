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

#define ADDDYNAMICSENSORMODULE(classname) class CONCAT(classname, proxy) { \
	public: \
	CONCAT(classname, proxy)(){ try { \
		                       std::cerr << "Loading SensorModule " << QUOTE(classname) << "... "; \
	                           vmi::VmiIDS::getInstance()->enqueueSensorModule(new classname); \
		                       std::cerr << "Success" << std::endl; \
                           } \
	                       catch (vmi::ModuleException &e){ \
		                       std::cerr << "FAILED" << std::endl; \
	                    	   e.printException(); \
	                       } \
	                       catch (std::exception &e){ \
	                    	   std::cerr << "FAILED" << std::endl; \
	                    	   std::cerr << e.what() << std::endl; \
	                       } \
	                     } \
	}; \
static CONCAT(classname, proxy) CONCAT(classname, p);

#define GETSENSORMODULE(variable, modulename) \
		variable = dynamic_cast<modulename *> (vmi::VmiIDS::getInstance()->getSensorModule(QUOTE(modulename))); \
		if (!variable) { \
			throw vmi::DependencyNotFoundException(QUOTE(modulename)); \
		}

#endif /* SENSORMODULE_H_ */
