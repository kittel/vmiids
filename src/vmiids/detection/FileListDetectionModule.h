/*
 * FileListDetectionModule.h
 *
 *  Created on: Jul 28, 2010
 *      Author: kittel
 */

#ifndef FILELISTDETECTIONMODULE_H_
#define FILELISTDETECTIONMODULE_H_

#include "vmiids/DetectionModule.h"

#include "vmiids/NotificationModule.h"

#include "vmiids/sensor/QemuMonitorSensorModule.h"
#include "vmiids/sensor/FileSystemSensorModule.h"
#include "vmiids/sensor/ShellSensorModule.h"

/*!
 * \exception MemorySensorModuleException MemorySensorModule.h
 * \brief Exception for MemorySensorModule.
 */
class FileListDetectionModuleException: public std::exception {
	virtual const char* what() const throw () {
		return "FileListDetectionModule abort";
	}
};

class FileListDetectionModule : public vmi::DetectionModule{

private:
	vmi::NotificationModule * notify;
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
