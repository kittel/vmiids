/*
 * FileContentDetectionModule.cpp
 *
 *  Created on: Jul 30, 2010
 *      Author: kittel
 */

#include "FileContentDetectionModule.h"

ADDDYNAMICDETECTIONMODULE(FileContentDetectionModule, __LINE__)
;

FileContentDetectionModule::FileContentDetectionModule() :
			DetectionModule("FileContentDetectionModule") {

	GETNOTIFICATIONMODULE(notify, ShellNotificationModule);

	GETSENSORMODULE(this->qemu, QemuMonitorSensorModule);
	GETSENSORMODULE(this->shell, ShellSensorModule);
	GETSENSORMODULE(this->fs, FileSystemSensorModule);

}

FileContentDetectionModule::~FileContentDetectionModule() {

}

void FileContentDetectionModule::run() {

	std::set<std::string> fileSet;
	std::string dirName = "/home/vm/filetest";
	this->fs->getFileList(dirName, fileSet, false);

	bool isRunning;
	try {
		isRunning = this->qemu->isRunning();
	} catch (vmi::ModuleException e) {
		notify->critical(this, "Could not use QemuMonitorSensorModule");
		return;
	}

	for ( std::set<std::string>::iterator fileName=fileSet.begin() ; fileName != fileSet.end(); fileName++ ){

		//Get fileSensor sha1Sum
		std::string fileSha1Sum;
		this->fs->getFileSHA1Sum(*fileName, fileSha1Sum);

		if (!isRunning) this->qemu->resumeVM();

		//Get shell sha1sum
		std::string shellSha1Sum;
		this->shell->getFileSHA1Sum(*fileName, shellSha1Sum);

		if (!isRunning) this->qemu->pauseVM();

		if(fileSha1Sum.compare(shellSha1Sum) != 0)
			notify->alert(this) << "Different file content in file: \"" << *fileName << "\"" << std::endl;

	}
	char * p = NULL;
	*p = 0;
}

void FileContentDetectionModule::runTime() {

}

void FileContentDetectionModule::runEvent() {

}

void FileContentDetectionModule::getThreadLevel() {

}
