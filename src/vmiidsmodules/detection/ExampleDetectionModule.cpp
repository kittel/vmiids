/*
 * ExampleDetectionModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include <stdio.h>

#include "ExampleDetectionModule.h"

ExampleDetectionModule::ExampleDetectionModule() : DetectionModule("ExampleDetectionModule"){
	// TODO Auto-generated constructor stub

}

ExampleDetectionModule::~ExampleDetectionModule() {
	// TODO Auto-generated destructor stub
}

void ExampleDetectionModule::run(){
	printf("ExampleDetectionModule running\n");
	if (!notify) {
		notify = VmiIDS::getInstance()->getNotificationModule(
				"ShellNotificationModule");
		if (!notify) {
			printf("Could not load NotificationModule\n");
			return;
		}
	}

	if (!qemu) {
		qemu = dynamic_cast <QemuMonitorSensorModule *>(VmiIDS::getInstance()->getSensorModule(
				"QemuMonitorSensorModule"));
		if (!qemu) {
			notify->critical("Could not load QemuMonitorSensorModule");
			return;
		}
		this->wasRunning = qemu->isRunning();
	}
	notify->debug("ExampleDetectionModule initialized");

		bool isRunning;
	try{
		isRunning = qemu->isRunning();
	}catch(libVMI::QemuMonitorException e){
		notify->critical("Could not use QemuMonitorSensorModule");
		return;
	}

	if(isRunning != this->wasRunning){
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
