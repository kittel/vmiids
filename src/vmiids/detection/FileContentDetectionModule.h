/*
 * FileContentDetectionModule.h
 *
 *  Created on: Jul 30, 2010
 *      Author: kittel
 */

#ifndef FILECONTENTDETECTIONMODULE_H_
#define FILECONTENTDETECTIONMODULE_H_

#include "vmiids/NotificationModule.h"

#include "vmiids/sensor/QemuMonitorSensorModule.h"
#include "vmiids/sensor/FileSystemSensorModule.h"
#include "vmiids/sensor/ShellSensorModule.h"

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
