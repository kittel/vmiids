/*
 * ShellNotificationModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include <iostream>

#include "ShellNotificationModule.h"

ADDDYNAMICNOTIFICATIONMODULE(ShellNotificationModule, __LINE__);

ShellNotificationModule::ShellNotificationModule() : NotificationModule("ShellNotificationModule"){

}

ShellNotificationModule::~ShellNotificationModule() {
	// TODO Auto-generated destructor stub
}

void ShellNotificationModule::info(vmi::Module *module, std::string message){
	this->info(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::info(vmi::Module *module){
	std::cout << "Information: " << module->getName() << ": ";
	return std::cout;
}

void ShellNotificationModule::debug(vmi::Module *module, std::string message){
	this->debug(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::debug(vmi::Module *module){
	std::cout << "Debug:       " << module->getName() << ": ";
	return std::cout;
}

void ShellNotificationModule::warn(vmi::Module *module, std::string message){
	this->warn(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::warn(vmi::Module *module){
	std::cout << "Warning:     " << module->getName() << ": ";
	return std::cout;
}

void ShellNotificationModule::error(vmi::Module *module, std::string message){
	this->error(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::error(vmi::Module *module){
	std::cout << "Error:       " << module->getName() << ": ";
	return std::cout;
}

void ShellNotificationModule::critical(vmi::Module *module, std::string message){
	this->critical(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::critical(vmi::Module *module){
	std::cout << "Critical:    " << module->getName() << ": ";
	return std::cout;
}

void ShellNotificationModule::alert(vmi::Module *module, std::string message){
	this->alert(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::alert(vmi::Module *module){
	std::cout << "Alert:       " << module->getName() << ": ";
	return std::cout;
}
