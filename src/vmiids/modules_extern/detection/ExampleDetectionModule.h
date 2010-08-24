/*
 * ExampleDetectionModule.h
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#ifndef EXAMPLEDETECTIONMODULE_H_
#define EXAMPLEDETECTIONMODULE_H_

#include "vmiids/DetectionModule.h"

#include "vmiids/modules/sensor/QemuMonitorSensorModule.h"
#include "vmiids/modules/sensor/FileSystemSensorModule.h"
#include "vmiids/modules/sensor/ShellSensorModule.h"

class ExampleDetectionModule : public vmi::DetectionModule{
private:
	QemuMonitorSensorModule * qemu;
	FileSystemSensorModule * fs;
	ShellSensorModule * shell;
	bool wasRunning;

public:
	ExampleDetectionModule();
	virtual ~ExampleDetectionModule();

	virtual void run();
	virtual void runTime();
	virtual void runEvent();

	virtual void getThreadLevel();
};

#endif /* EXAMPLEDETECTIONMODULE_H_ */
