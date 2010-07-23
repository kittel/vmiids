/*
 * ProcessListDetectionModule.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#include "ProcessListDetectionModule.h"

ADDDYNAMICDETECTIONMODULE(ProcessListDetectionModule, __LINE__)
;

ProcessListDetectionModule::ProcessListDetectionModule() :
			DetectionModule("ProcessListDetectionModule") {

	this->notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!this->notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	this->qemu
			= dynamic_cast<QemuMonitorSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"QemuMonitorSensorModule"));
	if (!this->qemu) {
		this->notify->critical("Could not load QemuMonitorSensorModule");
		return;
	}

	this->shell
			= dynamic_cast<ShellSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"ShellSensorModule"));
	if (!this->shell) {
		this->notify->critical("Could not load ShellSensorModule");
		return;
	}

	this->memory
			= dynamic_cast<MemorySensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"MemorySensorModule"));
	if (!this->memory) {
		this->notify->critical("Could not load MemorySensorModule");
		return;
	}
}

ProcessListDetectionModule::~ProcessListDetectionModule() {

}

void ProcessListDetectionModule::run() {

	bool isRunning;
	try {
		isRunning = this->qemu->isRunning();
	} catch (libVMI::QemuMonitorException e) {
		this->notify->critical("Could not use QemuMonitorSensorModule");
		return;
	}


	if (!isRunning) {
		this->qemu->resumeVM();
	}

	std::string psResult;
	this->shell->parseCommandOutput("ps aux", psResult);
	this->notify->info("Command \"ps aux\" executed");
	this->notify->info(psResult.insert(0, "\t"));

	if (!isRunning) {
		this->qemu->pauseVM();
	}

	std::string memtoolResult;
	this->memory->getProcessList(memtoolResult);
	this->notify->info("Read processlist from memtool");
	this->notify->info(memtoolResult.insert(0, "\t"));
}

void ProcessListDetectionModule::runTime() {

}

void ProcessListDetectionModule::runEvent() {

}

void ProcessListDetectionModule::getThreadLevel() {

}
