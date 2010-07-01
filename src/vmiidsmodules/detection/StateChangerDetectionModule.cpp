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
	notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	qemu = dynamic_cast<QemuMonitorSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"QemuMonitorSensorModule"));
	if (!qemu) {
		notify->critical("Could not load QemuMonitorSensorModule");
		return;
	}
	notify->debug("StateChangerDetectionModule initialized");
}

StateChangerDetectionModule::~StateChangerDetectionModule() {

}

void StateChangerDetectionModule::run(){

	this->runCounter++;
	try{
		if(this->runCounter == 25){
			notify->info("Pausing VM");
			qemu->pauseVM();
		}else if(this->runCounter == 50){
			this->runCounter = 0;
			notify->info("Resuming VM");
			qemu->resumeVM();
		}
	}catch(libVMI::QemuMonitorException e){
		notify->critical("Could not use QemuMonitorSensorModule");
		return;
	}
}

void StateChangerDetectionModule::runTime(){

}

void StateChangerDetectionModule::runEvent(){

}

void StateChangerDetectionModule::getThreadLevel(){

}
