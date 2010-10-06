/*
 * FileSystemSensorModule.h
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#ifndef FILESYSTEMSENSORMODULE_H_
#define FILESYSTEMSENSORMODULE_H_

#include "vmiids/SensorModule.h"

#include <string>
#include <fstream>

#include <sys/stat.h>

#include <set>

/*!
 * FileSystemSensorException FileSystemSensorModule.h "vmiids/modules/sensor/FileSystemSensorModule.h"
 * \brief Exception for FileSystemSensorModule.
 */
class FileSystemSensorException: public vmi::ModuleException {
	virtual const char* what() const throw () {
		return "FileSystemSensorModule abort";
	}
};

/*!
 * @class FileSystemSensorModule FileSystemSensorModule.h "vmiids/modules/sensor/FileSystemSensorModule.h"
 * @brief FileSystemSensorModule.
 * @sa vmi::SensorModule
 *
 * Sensor module to create a view from the underlying software state. The file system sensor module
 * is used to create a view of the monitored systems file system. As the partition table,
 * the file system type and the files are located using standard methodologies, the FileSystemSensorModule
 * is using out-of-band delivered and derived information to create its view.
 *
 * To cope with file system caching, the sensor makes use of the clearfscache utility.
 */
class FileSystemSensorModule : public vmi::SensorModule{
public:
	/**
	 * Constructor
	 */
	FileSystemSensorModule();

	/**
	 * Destructor
	 */
	virtual ~FileSystemSensorModule();


	/**
	 * Check if file exists within the monitored machines filesystem.
	 *
	 * @param absolutePath Absolute path of the file to check.
	 * @param stFileInfo Pointer to a struct stat object.
	 * @return True, if the requested file exists. Otherwise false.
	 */
	bool fileExists(const std::string absolutePath, struct stat * stFileInfo = NULL);
	/**
	 * Open a file on the monitored machines filesystem.
	 *
	 * @param absolutePath Absolute path of the file to open.
	 * @param fileHandle File handle to open the file into.
	 */
	void openFileRO(const std::string absolutePath, std::ifstream *fileHandle);
	/**
	 * Read the contents of the given directory into the set directories.
	 * If the flag withdirs is true, contents of subdirectories are included.
	 *
	 * @param directory Directory to create a list of contents from.
	 * @param directories Set to append the list of contents into.
	 * @param withdirs Flag, whether the content of subdirectories should be included.
	 */
	void getFileList(const std::string &directory, std::set<std::string> &directories, bool withdirs = true);
	/**
	 * Create an sha1 hash value of a given file.
	 *
	 * @param fileName File to create sha1 hash value from.
	 * @param sha1Sum Empty string to append calculated hash value to.
	 */
	void getFileSHA1Sum(const std::string &fileName, std::string &sha1Sum);

private:
	std::string clearCacheCommand;  //!< Path of the clearCacheCommand (Must be set in config file @ref vmi::Settings)
	std::string fileSystemPath;     //!< Path of the monitored file system (Must be set in config file @ref vmi::Settings)

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

#endif /* FILESYSTEMSENSORMODULE_H_ */
