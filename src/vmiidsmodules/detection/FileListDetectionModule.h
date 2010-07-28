/*
 * FileListDetectionModule.h
 *
 *  Created on: Jul 28, 2010
 *      Author: kittel
 */

#ifndef FILELISTDETECTIONMODULE_H_
#define FILELISTDETECTIONMODULE_H_

#include "NotificationModule.h"

#include "../sensor/QemuMonitorSensorModule.h"
#include "../sensor/FileSystemSensorModule.h"
#include "../sensor/ShellSensorModule.h"

/*!
 * \exception MemorySensorModuleException MemorySensorModule.h
 * \brief Exception for MemorySensorModule.
 */
class FileListDetectionModuleException: public std::exception {
	virtual const char* what() const throw () {
		return "FileListDetectionModule abort";
	}
};

class FileListDetectionModule : public DetectionModule{

private:
	NotificationModule * notify;
	QemuMonitorSensorModule * qemu;
	ShellSensorModule * shell;
	FileSystemSensorModule * fs;

	std::string directory;

	std::set<std::string> globalFsFileList;
	std::set<std::string> globalShellFileList;

public:
	FileListDetectionModule();
	virtual ~FileListDetectionModule();

	virtual void run();
	virtual void runTime();
	virtual void runEvent();

	virtual void getThreadLevel();
};

#endif /* FILELISTDETECTIONMODULE_H_ */
