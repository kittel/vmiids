/*
 * MemorySensorModule.h
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#ifndef MEMORYSENSORMODULE_H_
#define MEMORYSENSORMODULE_H_

#include "vmiids/SensorModule.h"

#include "vmiids/util/Mutex.h"

#include <memtool/memtool.h>

#include <map>
#include <QCoreApplication>

#include <stdint.h>

/*!
 * \exception MemorySensorModuleException MemorySensorModule.h "vmiids/modules/sensor/ShellSensorModule.h"
 * \brief Exception for MemorySensorModule.
 */

class MemtoolNotRunningException: public vmi::ModuleException {
	virtual const char* what() const throw () {
		return "Memtool Not Running";
	}
};

/**
 * Representation of a process in the shell sensor module.
 */
typedef struct{
	uint32_t pid;
	std::string processName;
} MemtoolProcess;

/*!
 * @class MemorySensorModule MemorySensorModule.h "vmiids/modules/sensor/MemorySensorModule.h"
 * @brief Sensor to create a view from the monitored machines physical memory state.
 * @sa vmi::SensorModule
 *
 * This sensor leverages the memtool written by Christian Schneider <chrschn@sec.in.tum.de>.
 *
 * To cope with file system caching, the sensor makes use of the clearfscache utility.
 */
class MemorySensorModule : public vmi::SensorModule{
public:
	/**
	 * Constructor
	 */
	MemorySensorModule();
	/**
	 * Destructor
	 */
	virtual ~MemorySensorModule();

	/**
	 * Receive a list of processes, currently executed in the monitored machine.
	 *
	 * This function leverages the script "tasklist.js" shipped with the memtool.
	 *
	 * @param memtoolProcessMap Map able to store the result of the requests.
	 */
	void getProcessList(std::map<uint32_t, MemtoolProcess> &memtoolProcessMap);

private:
	vmi::Mutex mutex; //!< Mutex to handle multithreaded execution

	int null;   //!< Instance of null pointer needed to initialize QCoreApplication

	/**
	 * Internal Qt dependency.
	 * The underlying memtool is built upon the Qt framework. An instance of QCoreApplication is required to
	 * use the memtool library. It is initialized in the sensor, as no other module currently requires Qt.
	 * This dependency must moved into an own sensor, if it is needed by other modules.
	 */
	static QCoreApplication* app;

	static Memtool* memtool;  //!< Instance of Memtool class. Used to access the Memtool for view generation.

	static void stopMemtool(void);  //!< Stop the memtool daemon, when it is no longer needed.

    std::string memtooldPath;        //!< Path of the memtool daemon (Must be set in config file @ref vmi::Settings)
	std::string libmemtoolPath;      //!< Path of the libmemtool directory (Must be set in config file @ref vmi::Settings)
	std::string memtoolScriptPath;   //!< Memtool script path (Must be set in config file @ref vmi::Settings)

	std::string savedDebugingSymbols;  //!< Path of a saved dump of debugging symbols (Must be set in config file @ref vmi::Settings)
	std::string memdumpFile;   //!< Path of the monitored machines memdump (Must be set in config file @ref vmi::Settings)

	std::string clearCacheCommand;   //!< Path of the clearCacheCommand (Must be set in config file @ref vmi::Settings)

	/**
	 * Executes the clearCacheCommand.
	 *
	 * The command to clear the underlying fs cache is separated into another binary.
	 * The framework is able to be run with user permissions. In order to execute the
	 * clearCacheCommand as privileged user, the executable must be owned by root and
	 * have the setuid bit set.
	 *
	 * @return True, if the cache was flushed successfully.
	 */
	bool clearFSCache();

};

#endif /* MEMORYSENSORMODULE_H_ */
