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

/**
 * @class StateChangerDetectionModule StateChangerDetectionModule.h "vmiids/modules/detection/StateChangerDetectionModule.h"
 * @brief Example Module changing the state of the monitored virtual machine.
 * @sa vmi::DetectionModule
 * @sa QemuMonitorSensorModule
 *
 * The StateChangerDetectionModule is a simple DetectionModule illustrating the use of the VMM interface within the VmiIDS framework.
 * It changes the execution state alternating between running and paused.
 * Therefore the module counts how often it is executed. Every 25 executions the module switches the monitored machines state.
 */
class StateChangerDetectionModule : public vmi::DetectionModule{
private:
	QemuMonitorSensorModule * qemu;

	static int runCounter;

public:
	StateChangerDetectionModule();
	virtual ~StateChangerDetectionModule();

	virtual void run();
};

#endif /* STATECHANGERDETECTIONMODULE_H_ */
