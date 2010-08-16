/*
 * ProcessListDetectionModule.h
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#ifndef PROCESSLISTDETECTIONMODULE_H_
#define PROCESSLISTDETECTIONMODULE_H_

#include "vmiids/DetectionModule.h"

#include "vmiids/sensor/QemuMonitorSensorModule.h"
#include "vmiids/sensor/MemorySensorModule.h"
#include "vmiids/sensor/ShellSensorModule.h"

class ProcessListDetectionModule : public vmi::DetectionModule{
	QemuMonitorSensorModule * qemu;
	ShellSensorModule * shell;
	MemorySensorModule * memory;

	std::map<uint32_t, MemtoolProcess> globalMemtoolProcessMap;
	std::map<uint32_t, ShellProcess> globalPsProcessMap;

public:
	ProcessListDetectionModule();
	virtual ~ProcessListDetectionModule();

	virtual void run();
	virtual void runTime();
	virtual void runEvent();

	virtual void getThreadLevel();
};

#endif /* PROCESSLISTDETECTIONMODULE_H_ */
