/*
 * FileSystemSensorModule.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#include "FileSystemSensorModule.h"

#include <stdlib.h>

ADDDYNAMICSENSORMODULE(FileSystemSensorModule, __LINE__);

FileSystemSensorModule::FileSystemSensorModule() : SensorModule("FileSystemSensorModule"){
	// TODO Auto-generated constructor stub

}

FileSystemSensorModule::~FileSystemSensorModule() {
	// TODO Auto-generated destructor stub
}

void FileSystemSensorModule::initSensorModule(){

}

bool FileSystemSensorModule::fileExists(std::string absolutePath, struct stat * stFileInfo){

	this->clearFSCache();

	if(!stFileInfo){
		struct stat FileInfo;
		stFileInfo = &FileInfo;
	}
	if (stat(absolutePath.insert(0, FILESYSTEMPATH).c_str(), stFileInfo) == 0){
		return true;
	}
	return false;
}

void FileSystemSensorModule::openFileRO(std::string absolutePath, std::ifstream *fileHandle){
	this->clearFSCache();

	fileHandle->open(absolutePath.insert(0, FILESYSTEMPATH).c_str() , std::ifstream::in);
}

bool FileSystemSensorModule::clearFSCache(){
	// To clear the file system cache and get the latest version of the rootkitvms file system.
	int result = system("sync; echo 3 > /proc/sys/vm/drop_caches");
	if (result == -1) return false;
	return true;
}
