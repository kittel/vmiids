/*
 * DetectionThread.h
 *
 *  Created on: Aug 25, 2010
 *      Author: tom
 */

#ifndef DETECTIONTHREAD_H_
#define DETECTIONTHREAD_H_

#include "vmiids/util/Thread.h"

#include <set>
#include <string>

namespace vmi {


/**
 * @class DetectionThread DetectionThread.h "vmiids/DetectionThread.h"
 * @brief Simple scheduler for DetectionModules.
 * @sa vmi::DetectionModule
 * @sa vmi::VmiIDS
 *
 * This class provides a simple scheduler for detection modules.
 * It executes a list of detection modules in from a separated thread.
 * Reexecution is triggered after the specified time has passed.
 *
 * Each detection module itself is executed within a single, separated thread.
 *
 * A list of module names is contained in an internal set.
 * The modules are executed one after the other.
 * If the execution of all modules takes longer, than the time specified between two
 * executions, reexecution is triggered immediately.
 */
class DetectionThread : public Thread{
private:
	pthread_mutex_t threadMutex; //!< Mutex for the m_detectionModules data structure.
	bool threadActive;   //!< Flag indicating if the thread is currently running.

	time_t m_seconds;   //!< Time between triggered executions.
	std::set<std::string> m_detectionModules;  //! Set containing detection modules which are executed.

	time_t lastRun;   //! Time of the last trigger. Used to calculate idle time between two triggers.

	/**
	 * @internal
	 * @brief Threads main function.
	 * @sa Thread::run()
	 *
	 * This function keeps track of the execution of the different detection modules enqueued.
	 */
	virtual void run();

public:
	/**
	 * Constructor
	 * @param seconds Time between two execution triggers.
	 *
	 * This constructor does not expect a list of detection modules to execute.
	 * Modules must be enqueue using the enqueueModule() function.
	 */
	DetectionThread(time_t seconds);

	/**
	 * Constructor
	 * @param seconds Time between two execution triggers.
	 * @param detectionModules Set of detection modules to execute,
	 *
	 * Further modules can be enqueue using the enqueueModule() function.
	 */
	DetectionThread(time_t seconds, std::set<std::string> detectionModules);


	/**
	 * Stop execution of scheduler and delete the object.
	 */
	virtual ~DetectionThread();

	/**
	 * Enqueue a detection module into the current scheduler.
	 *
	 * @param moduleName Name of the detection module to enqueue.
	 * @return True, if the detection module could be enqueued.
	 */
	bool enqueueModule(std::string moduleName);

	/**
	 * Dequeue a detection module from the current scheduler.
	 *
	 * @param moduleName Name of the detection module to dequeue.
	 * @return True, if the detection module could be dequeued.
	 */
	bool dequeueModule(std::string moduleName);

	/**
	 * Return the number of modules enqueued in the current scheduler.
	 * @return Number of modules enqueued.
	 */
	size_t getModuleCount();

	/**
	 * Stop execution of scheduler.
	 */
	void stopThread();
};

}

#endif /* DETECTIONTHREAD_H_ */
