/*
 * StateChangerDetectionModule.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#include <stdio.h>

#include "StateChangerDetectionModule.h"

ADDDYNAMICDETECTIONMODULE(StateChangerDetectionModule, __LINE__);

int StateChangerDetectionModule::runCounter = 0;

StateChangerDetectionModule::StateChangerDetectionModule()  : DetectionModule("StateChangerDetectionModule"){
	GETNOTIFICATIONMODULE(notify, ShellNotificationModule);

	qemu = dynamic_cast<QemuMonitorSensorModule *> (vmi::VmiIDS::getInstance()->getSensorModule(
					"QemuMonitorSensorModule"));
	if (!qemu) {
		notify->critical(this, "Could not load QemuMonitorSensorModule");
		return;
	}
}

StateChangerDetectionModule::~StateChangerDetectionModule() {

}

void StateChangerDetectionModule::run(){

	this->runCounter++;
	try{
		if(this->runCounter == 25){
			notify->info(this, "Pausing VM");
			qemu->pauseVM();
		}else if(this->runCounter == 50){
			this->runCounter = 0;
			notify->info(this, "Resuming VM");
			qemu->resumeVM();
		}
	}catch(vmi::ModuleException e){
		notify->critical(this, "Could not use QemuMonitorSensorModule");
		return;
	}
}

void StateChangerDetectionModule::runTime(){

}

void StateChangerDetectionModule::runEvent(){

}

void StateChangerDetectionModule::getThreadLevel(){

}
