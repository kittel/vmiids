/*
 * ExampleDetectionModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include <stdio.h>

#include "ExampleDetectionModule.h"

ADDDYNAMICDETECTIONMODULE(ExampleDetectionModule, __LINE__)
;

ExampleDetectionModule::ExampleDetectionModule() :
	DetectionModule("ExampleDetectionModule") {
	notify = vmi::VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	this->qemu
			= dynamic_cast<QemuMonitorSensorModule *> (vmi::VmiIDS::getInstance()->getSensorModule(
					"QemuMonitorSensorModule"));
	if (!this->qemu) {
		notify->critical(this, "Could not load QemuMonitorSensorModule");
		return;
	}
	this->wasRunning = this->qemu->isRunning();

	this->fs
			= dynamic_cast<FileSystemSensorModule *> (vmi::VmiIDS::getInstance()->getSensorModule(
					"FileSystemSensorModule"));
	if (!this->fs) {
		notify->critical(this, "Could not load FileSystemSensorModule");
		return;
	}

	this->shell
			= dynamic_cast<ShellSensorModule *> (vmi::VmiIDS::getInstance()->getSensorModule(
					"ShellSensorModule"));
	if (!this->shell) {
		notify->critical(this, "Could not load ShellSensorModule");
		return;
	}
}

ExampleDetectionModule::~ExampleDetectionModule() {
	// TODO Auto-generated destructor stub
}

void ExampleDetectionModule::run() {

	bool isRunning;
	try {
		isRunning = this->qemu->isRunning();
	} catch (libVMI::QemuMonitorException e) {
		notify->critical(this, "Could not use QemuMonitorSensorModule");
		return;
	}

	if (isRunning != this->wasRunning) {
		this->wasRunning = isRunning;
		notify->info(this, "VM State Changed!");
		(isRunning) ? notify->info(this, "\t VM State: running")
				: notify->info(this, "\t VM State: stopped");
	}

	std::string commandResult;

	this->qemu->infoRegisters(commandResult);
	notify->info(this, "Qemu Registers");
	notify->info(this, commandResult.insert(0, "\t"));

	if (this->fs->fileExists("/etc/hostname")) {
		notify->info(this, "File /etc/hostname exists");
		std::ifstream fileHandle;
		this->fs->openFileRO("/etc/hostname", &fileHandle);
		std::string fileContent;
		std::string line;
		while (std::getline(fileHandle, line))
			fileContent += line;
		notify->info(this, fileContent.insert(0, "\t"));
		fileHandle.close();
	}

	if(isRunning){
		commandResult.clear();
		this->shell->parseCommandOutput("ps aux", commandResult);
		notify->info(this, "Command \"ps aux\" executed");
		notify->info(this, commandResult.insert(0, "\t"));
	}
}

void ExampleDetectionModule::runTime() {

}

void ExampleDetectionModule::runEvent() {

}

void ExampleDetectionModule::getThreadLevel() {

}
