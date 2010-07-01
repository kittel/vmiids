/*
 * QemuMonitorSensorModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include "QemuMonitorSensorModule.h"

ADDDYNAMICSENSORMODULE(QemuMonitorSensorModule, __LINE__);

#include <stdio.h>
QemuMonitorSensorModule::QemuMonitorSensorModule() : SensorModule("QemuMonitorSensorModule"), QemuMonitor(){
}

QemuMonitorSensorModule::~QemuMonitorSensorModule() {
	// TODO Auto-generated destructor stub
}

void QemuMonitorSensorModule::initSensorModule(){

}
