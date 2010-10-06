/*
 * DetectionModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef DETECTIONMODULE_H_
#define DETECTIONMODULE_H_

#include "Module.h"
#include "OutputModule.h"
#include "vmiids/util/Thread.h"

#include "vmiids/util/Mutex.h"

#include <string>
#include <map>
#include <list>

namespace vmi {

/**
 * @class DetectionModule DetectionModule.h "vmiids/DetectionModule.h"
 * @brief Detection Modules - The frameworks active component.
 * @sa vmi::SensorModule
 * @sa vmi::OutputModule
 *
 * This class is the base class of the frameworks active components.
 * Detection modules are executed periodically. Detection modules introspect a machine´s state
 * using the interfaces provided by different SensorModules.
 * Processing sensor data, DetectionModules provide an estimated threat level.
 *
 * The thread level describes the detection modules current estimate, how likely the monitored
 * state is compromised by malware.
 *
 * Detection Modules inherit from the Thread class, as each detection module is executed
 * within a separate thread. If the detection module contains an programmatic error, in worst case,
 * it causes the process to receive a segmentation fault. A detection module is thus unable
 * to cause a crash of the entire framework. The segmentation fault is catched by the framework and
 * the corresponding detection module will be aborted.
 *
 * TODO implement timeout for detection modules execution.
 */
class DetectionModule : public vmi::Module, protected OutputModule, public Thread{
	private:
		/**
		 * Map of DetectionModules currently loaded into the framework. The modules are hashed with
		 * the name of the detectionModule as key. This map is static and contains a list of all
		 * instances of this class. The detectionModules are enqueued in the Constructor.
		 *
		 * TODO Currently modules can not be unloaded.
		 */
		static std::map<std::string, vmi::DetectionModule *> modules;

		/**
		 * Mutex for the modules map. Allow multithreaded access to different detection modules.
		 */
		static vmi::Mutex mutex;

	protected:
		/**
		 * Thread level.
		 * Detection modules estimate a current probability of how likely it is, that the monitored
		 * state is compromised by malware.
		 */
		float threatLevel;

	public:

		/**
		 * Constructor
		 *
		 * The name of the module can be specified by the dynamic classloader provided by
		 * the module interface (LOADMODULE())
		 *
		 * @param moduleName Name of the detectionModule
		 */
		DetectionModule(std::string moduleName);

		/**
		 * Destructor
		 */
		virtual ~DetectionModule();

		/**
		 * Request a pointer to a special DetectionModules.
		 * @param detectionModuleName Name of the requested DetectionModule.
		 * @return Pointer to the DetectionModule.
		 */
		static vmi::DetectionModule *getDetectionModule(std::string detectionModuleName);

		/**
		 * Request a list of currently loaded DetectionModules. The list does not contain pointers
		 * to DetectionModule instances, but the names of the modules loaded.
		 * @return List of Names of currently loaded detection modules.
		 */
		static std::list<std::string> getListOfDetectionModules();

		/**
		 * Delete all currently loaded DetectionModule instances.
		 */
		static void killInstances();

		/**
		 * Request the threadLevel of the current DetectionModule.
		 * @return Thread level calculated by the current detection module.
		 */
		float getThreadLevel();
};

}

#endif /* DETECTIONMODULE_H_ */

