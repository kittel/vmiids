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

/**
 * @class ExampleDetectionModule ExampleDetectionModule.h "vmiids/modules/detection/ExampleDetectionModule.h"
 * @brief Example Module checking the state of the monitored virtual machine.
 * @sa vmi::DetectionModule
 * @sa QemuMonitorSensorModule
 * @sa FileSystemSensorModule
 * @sa ShellSensorModule
 *
 * The ExampleDetectionModule is the counterpart of the StateChangerDetectionModule.
 * When executed it checks the monitored machines state. If its execution state (paused or running) changed, since the
 * last run of the ExampleDetectionModule, it prints a message for the user of the VmiIDS framework.
 *
 * If the current VM state is running, the Module furthermore prints information about the monitored machines hostname
 * and all processes running within the monitored machine. To read the hostname the DetectionModule leverages the
 * FileSystemSensorModule. To generate a list of currently running processes, the DetectionModule uses the ShellSensorModule.
 */
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
};

#endif /* EXAMPLEDETECTIONMODULE_H_ */
