/*
 * StateChangerDetectionModule.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#include <stdio.h>

#include "StateChangerDetectionModule.h"

ADDDYNAMICDETECTIONMODULE(StateChangerDetectionModule);

int StateChangerDetectionModule::runCounter = 0;

StateChangerDetectionModule::StateChangerDetectionModule()  : DetectionModule("StateChangerDetectionModule"){
	GETNOTIFICATIONMODULE(notify, ShellNotificationModule);

	GETSENSORMODULE(this->qemu, QemuMonitorSensorModule);
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