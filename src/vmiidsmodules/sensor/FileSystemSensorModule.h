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

#define FILESYSTEMPATH "/media/rootkitvm"

class FileSystemSensorModule : public SensorModule{
public:
	FileSystemSensorModule();
	virtual ~FileSystemSensorModule();


	void initSensorModule();
	bool fileExists(std::string absolutePath, struct stat * stFileInfo = NULL);
	void openFileRO(std::string absolutePath, std::ifstream *fileHandle);

private:
	bool clearFSCache();
};

#endif /* FILESYSTEMSENSORMODULE_H_ */
