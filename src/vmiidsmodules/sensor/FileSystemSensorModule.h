/*
 * FileSystemSensorModule.h
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#ifndef FILESYSTEMSENSORMODULE_H_
#define FILESYSTEMSENSORMODULE_H_

#include "SensorModule.h"

#include <string>
#include <fstream>

#include <sys/stat.h>

#include <set>

/*!
 * \exception FileSystemSensorModule FileSystemSensorModule.h
 * \brief Exception for FileSystemSensorModule.
 */
class FileSystemSensorException: public std::exception {
	virtual const char* what() const throw () {
		return "FileSystemSensorModule abort";
	}
};

class FileSystemSensorModule : public vmi::SensorModule{
public:
	FileSystemSensorModule();
	virtual ~FileSystemSensorModule();


	void initSensorModule();
	bool fileExists(std::string absolutePath, struct stat * stFileInfo = NULL);
	void openFileRO(std::string absolutePath, std::ifstream *fileHandle);
	std::set<std::string> getFileList(std::string directory);

private:
	vmi::NotificationModule * notify;

	std::string clearCacheCommand;
	std::string fileSystemPath;

	bool clearFSCache();
};

#endif /* FILESYSTEMSENSORMODULE_H_ */
