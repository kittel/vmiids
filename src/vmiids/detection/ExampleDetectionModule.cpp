/*
 * ExampleDetectionModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include <stdio.h>

#include "ExampleDetectionModule.h"

ADDMODULE(ExampleDetectionModule);

ExampleDetectionModule::ExampleDetectionModule() :
	DetectionModule("ExampleDetectionModule") {
	GETSENSORMODULE(this->fs, FileSystemSensorModule);
	GETSENSORMODULE(this->shell, ShellSensorModule);
	GETSENSORMODULE(this->qemu, QemuMonitorSensorModule);
	this->wasRunning = this->qemu->isRunning();
}

ExampleDetectionModule::~ExampleDetectionModule() {
	// TODO Auto-generated destructor stub
}

void ExampleDetectionModule::run() {

	bool isRunning;
	try {
		isRunning = this->qemu->isRunning();
	} catch (vmi::ModuleException &e) {
		printCritical("Could not use QemuMonitorSensorModule");
		return;
	}

	if (isRunning != this->wasRunning) {
		this->wasRunning = isRunning;
		printInfo("VM State Changed!");
		(isRunning) ? printInfo("\t VM State: running")
				: printInfo("\t VM State: stopped");
	}

	std::string commandResult;

	this->qemu->infoRegisters(commandResult);
	printInfo("Qemu Registers");
	info << "\t" << commandResult;

	if (this->fs->fileExists("/etc/hostname")) {
		printInfo("File /etc/hostname exists");
		std::ifstream fileHandle;
		this->fs->openFileRO("/etc/hostname", &fileHandle);
		std::string fileContent;
		std::string line;
		while (std::getline(fileHandle, line))
			fileContent += line;
		info << "\t" << fileContent;
		fileHandle.close();
	}

	if(isRunning){
		commandResult.clear();
		this->shell->parseCommandOutput("ps aux", commandResult);
		printInfo("Command \"ps aux\" executed");
		info << "\t" << commandResult;
	}
}

void ExampleDetectionModule::runTime() {

}

void ExampleDetectionModule::runEvent() {

}

void ExampleDetectionModule::getThreadLevel() {

}
