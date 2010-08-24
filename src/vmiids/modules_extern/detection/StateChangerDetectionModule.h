/*
 * StateChangerDetectionModule.h
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#ifndef STATECHANGERDETECTIONMODULE_H_
#define STATECHANGERDETECTIONMODULE_H_

#include "vmiids/DetectionModule.h"

#include "vmiids/modules/sensor/QemuMonitorSensorModule.h"

class StateChangerDetectionModule : public vmi::DetectionModule{
private:
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
