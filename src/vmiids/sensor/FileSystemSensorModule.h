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
	bool fileExists(const std::string absolutePath, struct stat * stFileInfo = NULL);
	void openFileRO(const std::string absolutePath, std::ifstream *fileHandle);
	void getFileList(const std::string &directory, std::set<std::string> &directories, bool withdirs = true);
	void getFileSHA1Sum(const std::string &fileName, std::string &sha1Sum);

private:
	vmi::NotificationModule * notify;

	std::string clearCacheCommand;
	std::string fileSystemPath;

	bool clearFSCache();
};

#endif /* FILESYSTEMSENSORMODULE_H_ */
