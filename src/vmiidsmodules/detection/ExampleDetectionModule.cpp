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
	this->wasRunning = this->qemu->isRunning();

	this->fs
			= dynamic_cast<FileSystemSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"FileSystemSensorModule"));
	if (!this->fs) {
		this->notify->critical("Could not load FileSystemSensorModule");
		return;
	}

	this->shell
			= dynamic_cast<ShellSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"ShellSensorModule"));
	if (!this->shell) {
		this->notify->critical("Could not load ShellSensorModule");
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
		this->notify->critical("Could not use QemuMonitorSensorModule");
		return;
	}

	if (isRunning != this->wasRunning) {
		this->wasRunning = isRunning;
		this->notify->info("VM State Changed!");
		(isRunning) ? this->notify->info("\t VM State: running")
				: this->notify->info("\t VM State: stopped");
	}

	std::string commandResult;

	this->qemu->infoRegisters(commandResult);
	this->notify->info("Qemu Registers");
	this->notify->info(commandResult.insert(0, "\t"));

	if (this->fs->fileExists("/etc/hostname")) {
		this->notify->info("File /etc/hostname exists");
		std::ifstream fileHandle;
		this->fs->openFileRO("/etc/hostname", &fileHandle);
		std::string fileContent;
		std::string line;
		while (std::getline(fileHandle, line))
			fileContent += line;
		this->notify->info(fileContent.insert(0, "\t"));
		fileHandle.close();
	}

	if(isRunning){
		commandResult.clear();
		this->shell->parseCommandOutput("ps aux", commandResult);
		this->notify->info("Command \"ps aux\" executed");
		this->notify->info(commandResult.insert(0, "\t"));
	}
}

void ExampleDetectionModule::runTime() {

}

void ExampleDetectionModule::runEvent() {

}

void ExampleDetectionModule::getThreadLevel() {

}
