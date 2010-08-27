/*
 * StateChangerDetectionModule.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#include <stdio.h>

#include "StateChangerDetectionModule.h"

LOADMODULE(StateChangerDetectionModule);

int StateChangerDetectionModule::runCounter = 0;

StateChangerDetectionModule::StateChangerDetectionModule()  : DetectionModule("StateChangerDetectionModule"){

	GETSENSORMODULE(this->qemu, QemuMonitorSensorModule);
}

StateChangerDetectionModule::~StateChangerDetectionModule() {

}

void StateChangerDetectionModule::run(){

	this->runCounter++;
	try{
		if(this->runCounter == 25){
			info << "Pausing VM";
			qemu->pauseVM();
		}else if(this->runCounter == 50){
			this->runCounter = 0;
			info << "Resuming VM";
			qemu->resumeVM();
		}
	}catch(vmi::ModuleException &e){
		critical << "Could not use QemuMonitorSensorModule";
		return;
	}
}
