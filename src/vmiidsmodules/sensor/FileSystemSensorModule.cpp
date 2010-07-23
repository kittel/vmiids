/*
 * FileSystemSensorModule.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#include "FileSystemSensorModule.h"

#include <cstdlib>
#include <sstream>

ADDDYNAMICSENSORMODULE(FileSystemSensorModule, __LINE__)
;

#define FILESYSTEMPATH "/media/rootkitvm"

FileSystemSensorModule::FileSystemSensorModule() :
	SensorModule("FileSystemSensorModule") {
	//Get NotificationModule
	this->notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!this->notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	libconfig::Setting *setting = VmiIDS::getInstance()->getSetting(
			this->getName());

	std::stringstream output;

	if (setting == NULL || !setting->lookupValue("clearfsconfigCommand",
			this->clearfscacheCommand) || !setting->lookupValue(
			"fileSystemPath", this->fileSystemPath)) {
		output.str("");
		output
				<< "Could not parse Options. Please add the following section to the config file:"
				<< std::endl << this->getName() << " = {" << std::endl
				<< "\tclearfsconfigCommand  =  \"<path to clearfscacheCommand>\";      e.g. \"/usr/bin/clearfscache\""
				<< std::endl
				<< "\tfileSystemPath        =  \"<path to introspected filesystem>\";  e.g. \"/media/rootkitvm\""
				<< std::endl << "};";

		this->notify->critical(output.str());
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

bool FileSystemSensorModule::clearFSCache() {
	bool result = true;

	// To clear the file system cache and get the latest version of the rootkitvms file system.
	result = (system("sync") == -1) ? false : true;
	result = (system(this->clearfscacheCommand.c_str()) == -1) ? false : true;
	return result;
}
