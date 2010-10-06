/*
 * ShellSensorModule.h
 *
 *  Created on: Jul 2, 2010
 *      Author: kittel
 */

#ifndef SHELLSENSORMODULE_H_
#define SHELLSENSORMODULE_H_

#include "vmiids/SensorModule.h"

#include "vmiids/util/Mutex.h"

#include "vmiids/ConsoleMonitor.h"

#include <map>
#include <set>
#include <stdint.h>

/**
 * Representation of a process in the shell sensor module.
 */
typedef struct{
	uint32_t pid;
	std::string processName;
} ShellProcess;

/*!
 * @class ShellSensorModule ShellSensorModule.h "vmiids/modules/sensor/ShellSensorModule.h"
 * @brief Parser for a Serial Shell Session.
 * @sa vmi::SensorModule
 * @sa vmi::ConsoleMonitor
 *
 * Sensor module providing an interface to the monitored machines internal view.
 * The shell sensor is used to execute commands within the monitored machine.
 * Note, that this information is not reliable for the purpose of rootkit detection.
 *
 * As underlying interface the shell sensor accesses the monitored machines serial shell.
 * A user must provide valid access data in the configuration file @ref vmi::Settings.
 */
class ShellSensorModule : public vmi::SensorModule , public vmi::ConsoleMonitor {
private:
	vmi::Mutex mutex; //!< Mutex to handle multithreaded execution

	std::string optionMonitorShell;  //! Shells commandline prompt (for the parser)
	std::string optionLoginShell;	//! Shells login prompt (for the parser)
	std::string optionPasswordShell;	//! Shells password prompt (for the parser)

	bool loggedin;  //!< Flag indicating if the Sensor is successfully logged in.
	/**
	 * Log into the serial shell
	 *
	 * @param username Username to log in with.
	 * @param password Password of the user to log in with.
	 * @return True, if the log in attempt was successful.
	 */
	bool login(std::string username, std::string password);
	/**
	 * Log out from the serial shell.
	 */
	void logout();

	/**
	 * Check if the sensor is currently logged in the serial shell.
	 * @return True, if the sensor is logged in.
	 */
	bool isLoggedin(void);

public:
	/**
	 * Constructor
	 */
	ShellSensorModule();
	/**
	 * Destructor
	 */
	virtual ~ShellSensorModule();

	/**
	 * Receive a list of processes, currently executed in the monitored machine.
	 *
	 * This function leverages the monitored machine "ps" utility.
	 *
	 * @param shellProcessMap Map able to store the result of the requests.
	 */
	void getProcessList(std::map<uint32_t, ShellProcess> &shellProcessMap);
	/**
	 * Receive a list of files in a directory. The file list does contain contents of subdirectories.
	 *
	 * This function leverages the monitored machine "find" utility.
	 *
	 * @param directory Path of the directory to gather the contents from.
	 * @param directories Data structure capable of holding the results of the query.
	 */
	void getFileList(const std::string &directory, std::set<std::string> &directories);
	/**
	 * Receive a files content.
	 *
	 * This function leverages the monitored machines hexdump utility.
	 *
	 * @param fileName Path of the file to receive the content from.
	 * @param fileContent Vector capable of holding the content of the file.
	 */
	void getFileContent(const std::string &fileName, std::vector<char> &fileContent);
	/**
	 * Calculate the sha1 hash value from a file within the monitored machine.
	 *
	 * This function leverages the monitored machines sha1sum utility.
	 *
	 * @param fileName Path of the file to receive the
	 * @param sha1Sum Data structure to hold the calculated hash value.
	 */
	void getFileSHA1Sum(const std::string &fileName, std::string &sha1Sum);
};

#endif /* SHELLSENSORMODULE_H_ */
