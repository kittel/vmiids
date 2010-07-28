/*
 * ProcessListDetectionModule.h
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#ifndef PROCESSLISTDETECTIONMODULE_H_
#define PROCESSLISTDETECTIONMODULE_H_

#include "NotificationModule.h"

#include "../sensor/QemuMonitorSensorModule.h"
#include "../sensor/MemorySensorModule.h"
#include "../sensor/ShellSensorModule.h"

class ProcessListDetectionModule : public DetectionModule{
	NotificationModule * notify;
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
