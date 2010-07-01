/*
 * ExampleDetectionModule.h
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#ifndef EXAMPLEDETECTIONMODULE_H_
#define EXAMPLEDETECTIONMODULE_H_

#include "NotificationModule.h"
#include "../sensor/QemuMonitorSensorModule.h"


class ExampleDetectionModule : public DetectionModule{
private:
	NotificationModule * notify;
	QemuMonitorSensorModule * qemu;
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
