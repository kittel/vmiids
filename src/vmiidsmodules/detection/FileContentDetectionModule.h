/*
 * FileContentDetectionModule.h
 *
 *  Created on: Jul 30, 2010
 *      Author: kittel
 */

#ifndef FILECONTENTDETECTIONMODULE_H_
#define FILECONTENTDETECTIONMODULE_H_

#include "NotificationModule.h"

#include "../sensor/QemuMonitorSensorModule.h"
#include "../sensor/FileSystemSensorModule.h"
#include "../sensor/ShellSensorModule.h"

class FileContentDetectionModule : public vmi::DetectionModule{
	vmi::NotificationModule * notify;
	QemuMonitorSensorModule * qemu;
	ShellSensorModule * shell;
	FileSystemSensorModule * fs;

	std::string directory;

public:
	FileContentDetectionModule();
	virtual ~FileContentDetectionModule();

	virtual void run();
	virtual void runTime();
	virtual void runEvent();

	virtual void getThreadLevel();
};

#endif /* FILECONTENTDETECTIONMODULE_H_ */
