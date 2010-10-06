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
/**
 * @class SensorModule SensorModule.h "vmiids/SensorModule.h"
 * @brief Sensor modules - Generate a view from the monitored machines state.
 * @sa vmi::DetectionModule
 * @sa vmi::VmiIDS
 *
 * SensorModules are built to generate different views from the monitored state.
 *
 * Sensormodule inherit from OutputModule, as these Modules also are able to
 * signal internal state to the user.
 *
 */
class SensorModule : public vmi::Module, protected OutputModule{
private:
	/**
	 * Map of SensorModules currently loaded into the framework. The modules are hashed with
	 * the name of the sensor module as key. This map is static and contains a list of all
	 * instances of this class. Detection modules are enqueued in the Constructor.
	 *
	 * TODO Currently modules can not be unloaded.
	 */
	static std::map<std::string, vmi::SensorModule *> modules;
	/**
	 * Mutex for the modules map. Allow multithreaded access to different sensor modules.
	 */
	static vmi::Mutex mutex;
public:
		/**
		 * Constructor
		 *
		 * The name of the module can be specified by the dynamic classloader provided by
		 * the module interface (LOADMODULE())
		 *
		 * @param moduleName Name of the detectionModule
		 */
		SensorModule(std::string moduleName);
		/**
		 * Destructor
		 */
		virtual ~SensorModule();

		/**
		 * Request a pointer to a special SensorModules.
		 * @param sensorModuleName Name of the requested SensorModule.
		 * @return Pointer to the SensorModule.
		 */
		static vmi::SensorModule *getSensorModule(std::string sensorModuleName);

		/**
		 * Delete all currently loaded DetectionModule instances.
		 */
		static void killInstances();
};

}

/**
 * @def GETSENSORMODULE
 * @brief Macro for DetectionModules to load a special SensorModule.
 * @sa vmi::DetectionModule
 * @sa vmi::VmiIDS
 *
 * This macro is used by detection modules to load special sensor modules.
 * If the dependency is not found a vmi::DependencyNotFoundException is thrown.
 */
#define GETSENSORMODULE(variable, modulename) \
		variable = dynamic_cast<modulename *> (vmi::SensorModule::getSensorModule(QUOTE(modulename))); \
		if (!variable) { \
			throw vmi::DependencyNotFoundException(QUOTE(modulename)); \
		}

#endif /* SENSORMODULE_H_ */
