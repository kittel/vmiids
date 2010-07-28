/*
 * FileListDetectionModule.cpp
 *
 *  Created on: Jul 28, 2010
 *      Author: kittel
 */

#include "FileListDetectionModule.h"

#include <sstream>

ADDDYNAMICDETECTIONMODULE(FileListDetectionModule, __LINE__)
;


FileListDetectionModule::FileListDetectionModule() :
					DetectionModule("FileListDetectionModule") {
	this->notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!this->notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	this->qemu
			= dynamic_cast<QemuMonitorSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"QemuMonitorSensorModule"));
	if (!this->qemu) {
		this->notify->critical("Could not load QemuMonitorSensorModule");
		return;
	}

	this->shell
			= dynamic_cast<ShellSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"ShellSensorModule"));
	if (!this->shell) {
		this->notify->critical("Could not load ShellSensorModule");
		return;
	}

	this->fs
			= dynamic_cast<FileSystemSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"FileSystemSensorModule"));
	if (!this->fs) {
		this->notify->critical("Could not load FileSystemSensorModule");
		return;
	}

	libconfig::Setting *setting = VmiIDS::getInstance()->getSetting(
			this->getName());

	std::stringstream output;

	if (setting == NULL || !setting->lookupValue("directory",
			this->directory) ) {

		output.str("");
		output
				<< "Could not parse Options. Please add the following section to the config file:"
				<< std::endl << this->getName() << " = {" << std::endl
				<< "\tdirectory             =  \"<directory to compare>\"; e.g. \"/home/vm\""
				<< std::endl << "};";

		this->notify->critical(output.str());
		throw FileListDetectionModuleException();
	}
	while(directory.size() > 1 &&directory[directory.size()-1] == '/')
		directory.erase(directory.size()-1);

}

FileListDetectionModule::~FileListDetectionModule() {

}

void FileListDetectionModule::run() {

	bool isRunning;
	try {
		isRunning = this->qemu->isRunning();
	} catch (libVMI::QemuMonitorException e) {
		this->notify->critical("Could not use QemuMonitorSensorModule");
		return;
	}

	//Get filelist from fs
	std::set<std::string> fsFileList;
	fsFileList = this->fs->getFileList(this->directory);

	if (!isRunning) {
		this->qemu->resumeVM();
	}

	//Get filelist from ls
	std::set<std::string> shellFileList;
	shellFileList = this->shell->getFileList(this->directory);

	if (!isRunning) {
		this->qemu->pauseVM();
	}

	//Compare Process Lists
	std::set<std::string>::iterator s_it;
	std::set<std::string>::iterator f_it;

	//Find files in find not listed in FileSystem
	for (s_it = shellFileList.begin(); s_it != shellFileList.end(); s_it++) {
		if (fsFileList.find(*s_it) == fsFileList.end()) {
			std::stringstream output;
			output << "File not found on FileSystem: " << *s_it << std::endl;
			this->notify->critical(output.str());
		} else {
			fsFileList.erase(fsFileList.find(*s_it));
			shellFileList.erase(s_it);
		}
	}

	for (f_it = fsFileList.begin(); f_it != fsFileList.end(); f_it++){
		std::stringstream output;
				output << "File not found with find command: " << *f_it << std::endl;
				this->notify->critical(output.str());
	}

	//Compare with results of last run
	//FileSystem results
	for (f_it = fsFileList.begin(); f_it != fsFileList.end(); f_it++) {
		if (this->globalFsFileList.find(*f_it) != this->globalFsFileList.end()) {
			std::stringstream output;
			output << "Hidden file detected: " << (*f_it) << std::endl;
			this->notify->alert(output.str());
		}
	}
	this->globalFsFileList = fsFileList;

	//find results
	for (s_it = shellFileList.begin(); s_it != shellFileList.end(); s_it++) {
		if (this->globalShellFileList.find(*s_it) != this->globalShellFileList.end()) {
			std::stringstream output;
			output << "Virtual file detected: " << (*s_it) << std::endl;
			this->notify->alert(output.str());
		}
	}
	this->globalShellFileList = shellFileList;

}

void FileListDetectionModule::runTime() {

}

void FileListDetectionModule::runEvent() {

}

void FileListDetectionModule::getThreadLevel() {

}

