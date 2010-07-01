/*
 * ExampleDetectionModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include <stdio.h>

#include "ExampleDetectionModule.h"

ADDDYNAMICDETECTIONMODULE(ExampleDetectionModule, __LINE__);

ExampleDetectionModule::ExampleDetectionModule() : DetectionModule("ExampleDetectionModule"){
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
	this->wasRunning = qemu->isRunning();
	notify->debug("ExampleDetectionModule initialized");
}

ExampleDetectionModule::~ExampleDetectionModule() {
	// TODO Auto-generated destructor stub
}

void ExampleDetectionModule::run(){

	bool isRunning;
	try{
		isRunning = qemu->isRunning();
	}catch(libVMI::QemuMonitorException e){
		notify->critical("Could not use QemuMonitorSensorModule");
		return;
	}

	if(isRunning != this->wasRunning){
		this->wasRunning = isRunning;
		notify->info("VM State Changed!");
		(isRunning) ? notify->info("\t VM State: running")
				    : notify->info("\t VM State: stopped");
	}
}

void ExampleDetectionModule::runTime(){

}

void ExampleDetectionModule::runEvent(){

}

void ExampleDetectionModule::getThreadLevel(){

}
