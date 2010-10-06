/*
 * VmiIDS.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef VMIIDS_H_
#define VMIIDS_H_

#include <map>
#include <string>
#include <set>

#include "vmiids/rpc/RpcServer.h"
#include "vmiids/util/Thread.h"
#include "vmiids/util/Mutex.h"

#include "DetectionThread.h"
#include "DetectionModule.h"
#include "SensorModule.h"

/**
 * @namespace vmi
 *
 * This is the default namespace for all classes belonging to the VmiIDS framework.
 * Modules are not neccessarily contained in namespace vmi.
 */
namespace vmi {

/**
 * @class VmiIDS VmiIDS.h "vmiids/VmiIDS.h"
 * @sa vmi::DetectionModule
 * @sa vmi::SensorModule
 * @sa vmi::NotificationModule
 *
 * @brief Frameworks main logic.
 *
 * This class is the main class of the VmiIDS framework. It is responsible for the frameworks
 * bootstraping process.<p>
 *
 */
class VmiIDS : public Module, protected OutputModule, public Thread{
	private:
		std::map<int, DetectionThread*> runModules; //!< Map of different detection module schedules.

		static VmiIDS *instance;  //!< Instance of the singleton class.
		RpcServer rpcServer;      //!< Instance of the rpc server thread.

		bool vmiRunning;    //!< Flag signalling whether the framework is currently running.

		/**
		 * Constructor
		 * Private to disallow external instances of this singleton.
		 */
		VmiIDS();
		/**
		 * Copy Constructor
		 * Private to disallow external instances of this singleton.
		 */
		VmiIDS(const VmiIDS&);
		/**
		 * Copy operator
		 * Private to disallow external instances of this singleton.
		 */
		VmiIDS& operator=(const VmiIDS&);

		void initVmiIDS();   //!< Bootstrap the framework
		void loadModules();  //!< Load all modules specified in the configuration file.

		/**
		 * Load all *.so files in the directory specified using the dl_open call.
		 * The modules are the inserted to the framework by the LOADMODULE() macro.
		 *
		 * @param path Path to look for modules to load.
		 */
		void loadSharedObjectsPath(std::string path);

	protected:
		/**
		 * Destructor
		 * @return
		 */
		virtual ~VmiIDS();

	public:

		/**
		 * The VmiIDS class is a singleton. This function is used to access the framework.
		 * @return Instance of class VmiIDS
		 */
		static VmiIDS *getInstance();

		/**
		 * @brief Default Exception Handler.
		 * @sa vmi::DetectionThread
		 * @sa signalHandler
		 *
		 * This function is called whenever an exception within a detection module was thrown,
		 * but was not catched. Using this function as default exception handler prevents the
		 * framework from failing, when an error within a module occurs.
		 *
		 * @param e Exception thrown.
		 */
		static void defaultExceptionHandler(std::exception& e);


		/**
		 * Stop the IDS
		 *
		 * @param signum signal to stop the IDS with. The signal is currently not taken into account.
		 * @return True, if the IDS was stopped.
		 */
		static bool stopIDS(int signum = 0);

		virtual void run(void);

		/**
		 * Load the module specified by path into the framework.
		 *
		 * @param path Path to look for modules to load.
		 * @return True, if the module could be loaded.
		 */
		bool loadSharedObject(std::string path);

		/**
		 * @brief Enqueue a detection module to a schedule
		 * @sa DetectionModule
		 * @sa DetectionThread
		 * @sa runModules
		 *
		 * Used to enqueue a DetectionModule to a specific schedule. The DetectionModule must
		 * be loaded into the framework in advance. The scheduler triggers the execution of all
		 * enqueued modules every timeInSeconds seconds. Afterwards all detectionModules are executed
		 * sequentially. Hence one run of the entire list of module scheduled may take longer, than
		 * the time specified. Therefore the execution is immediately retriggered in that case.
		 *
		 * @param detectionModuleName Name of the DetectionModule
		 * @param timeInSeconds Time between two executions of the module detectionModuleName.
		 * @return True, if the DetectionModule was enqueued successfully.
		 */
		bool enqueueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds = 0);

		/**
		 * @brief Denqueue a detection module to a schedule
		 * @sa DetectionModule
		 * @sa DetectionThread
		 * @sa runModules
		 *
		 * Used to dequeue a DetectionModule from a specific schedule.
		 *
		 * @param detectionModuleName Name of the DetectionModule
		 * @param timeInSeconds Reexecution time of the schedule to unload the module from.
		 * @return True, if the DetectionModule was dequeued successfully.
		 */
		bool dequeueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds = 0);

		/**
		 * Currently a stub.
		 * TODO Implement a function returning an overall thread level.
		 * TODO For example for all modules in a certain schedule.
		 */
		void collectThreadLevel();
};

}

using vmi::VmiIDS;

#endif /* VMIIDS_H_ */
