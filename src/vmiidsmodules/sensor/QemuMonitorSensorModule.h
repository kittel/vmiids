/*
 * QemuMonitorSensorModule.h
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#ifndef QEMUMONITORSENSORMODULE_H_
#define QEMUMONITORSENSORMODULE_H_

#include "SensorModule.h"
#include "libvmi.h"

class QemuMonitorSensorModule: public SensorModule , public libVMI::QemuMonitor {
public:
	QemuMonitorSensorModule();
	virtual ~QemuMonitorSensorModule();

	void initSensorModule();
};

#endif /* QEMUMONITORSENSORMODULE_H_ */
