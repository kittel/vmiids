/*
 * FileSystemSensorModule.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#include "FileSystemSensorModule.h"

#include <cstdlib>

#include <dirent.h>

ADDDYNAMICSENSORMODULE(FileSystemSensorModule, __LINE__)
;

FileSystemSensorModule::FileSystemSensorModule() : SensorModule("FileSystemSensorModule") {
	//Get NotificationModule
	notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	libconfig::Setting *setting = VmiIDS::getInstance()->getSetting(
			this->getName());

	if (setting == NULL || !setting->lookupValue("clearCacheCommand",
			this->clearCacheCommand) || !setting->lookupValue(
			"fileSystemPath", this->fileSystemPath)) {
		notify->critical(this)
				<< "Could not parse Options. Please add the following section to the config file:"
				<< std::endl << this->getName() << " = {" << std::endl
				<< "\tclearCacheCommand  =  \"<path to clearCacheCommand>\";      e.g. \"/usr/bin/clearfscache\""
				<< std::endl
				<< "\tfileSystemPath        =  \"<path to introspected filesystem>\";  e.g. \"/media/rootkitvm\""
				<< std::endl << "};";
		throw FileSystemSensorException();
	}
}

FileSystemSensorModule::~FileSystemSensorModule() {
	// TODO Auto-generated destructor stub
}

void FileSystemSensorModule::initSensorModule() {

}

bool FileSystemSensorModule::fileExists(std::string absolutePath,
		struct stat * stFileInfo) {

	this->clearFSCache();

	if (!stFileInfo) {
		struct stat FileInfo;
		stFileInfo = &FileInfo;
	}
	if (stat(absolutePath.insert(0, this->fileSystemPath).c_str(), stFileInfo) == 0) {
		return true;
	}
	return false;
}

void FileSystemSensorModule::openFileRO(std::string absolutePath,
		std::ifstream *fileHandle) {
	this->clearFSCache();

	fileHandle->open(absolutePath.insert(0, this->fileSystemPath).c_str(),
			std::ifstream::in);
}

std::set<std::string> FileSystemSensorModule::getFileList(std::string directory){
	DIR *d;
	struct dirent *dir;

	std::set<std::string> directories;

	this->clearFSCache();
	d = opendir(std::string().insert(0, this->fileSystemPath).append("/").append(directory).c_str());
	if (d == NULL) {
		return directories;
	}
	directories.insert(directory);
	while ((dir = readdir(d))) {
		if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
			continue;
		}
		if (dir->d_type == DT_DIR) {
			std::set<std::string> subdir =
					this->getFileList(std::string(dir->d_name).insert(0, "/").insert(0,
							directory));
			directories.insert(subdir.begin(), subdir.end());
		} else {
			directories.insert(
					std::string(dir->d_name).insert(0, "/").insert(0, directory));
		}
	}
	closedir(d);
	return directories;
}

bool FileSystemSensorModule::clearFSCache() {
	bool result = true;

	// To clear the file system cache and get the latest version of the rootkitvms file system.
	result = (system("sync") == -1) ? false : true;
	result = (system(this->clearCacheCommand.c_str()) == -1) ? false : true;
	return result;
}
