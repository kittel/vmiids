/*
 * StateChangerDetectionModule.h
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#ifndef STATECHANGERDETECTIONMODULE_H_
#define STATECHANGERDETECTIONMODULE_H_

#include "NotificationModule.h"
#include "../sensor/QemuMonitorSensorModule.h"

class StateChangerDetectionModule : public vmi::DetectionModule{
private:
	vmi::NotificationModule * notify;
	QemuMonitorSensorModule * qemu;

	static int runCounter;

public:
	StateChangerDetectionModule();
	virtual ~StateChangerDetectionModule();

	virtual void run();
	virtual void runTime();
	virtual void runEvent();

	virtual void getThreadLevel();
};

#endif /* STATECHANGERDETECTIONMODULE_H_ */
