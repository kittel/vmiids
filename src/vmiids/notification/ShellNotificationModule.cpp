/*
 * ShellNotificationModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include <iostream>

#include "ShellNotificationModule.h"

ShellNotificationModule::ShellNotificationModule() : NotificationModule("ShellNotificationModule"){

}

ShellNotificationModule::~ShellNotificationModule() {
	// TODO Auto-generated destructor stub
}

void ShellNotificationModule::doDebug(std::string module, std::string message){
	std::cout << "Debug:       " << module << ": " << message;
}

void ShellNotificationModule::doInfo(std::string module, std::string message){
	std::cout << "Information: " << module << ": " << message;
}

void ShellNotificationModule::doWarn(std::string module, std::string message){
	std::cout << "Warning:     " << module << ": " << message;
}

void ShellNotificationModule::doError(std::string module, std::string message){
	std::cout << "Error:       " << module << ": " << message;
}

void ShellNotificationModule::doCritical(std::string module, std::string message){
	std::cout << "Critical:    " << module << ": " << message;
}

void ShellNotificationModule::doAlert(std::string module, std::string message){
	std::cout << "Alert:       " << module << ": " << message;
}

/*
std::ostream& ShellNotificationModule::debug(vmi::Module *module){
	std::ostream & stream = ((this->debugLevel >= vmi::OUTPUT_DEBUG) ? std::cout : this->nullStream );
	stream << "Debug:       " << module->getName() << ": ";
	return stream;
}

void ShellNotificationModule::info(vmi::Module *module, std::string message){
	this->info(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::info(vmi::Module *module){
	std::ostream & stream = ((this->debugLevel >= vmi::OUTPUT_INFO) ? std::cout : this->nullStream );
	stream << "Information: " << module->getName() << ": ";
	return stream;
}

void ShellNotificationModule::warn(vmi::Module *module, std::string message){
	this->warn(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::warn(vmi::Module *module){
	std::ostream & stream = ((this->debugLevel >= vmi::OUTPUT_DEBUG) ? std::cout : this->nullStream );
	stream << "Warning:     " << module->getName() << ": ";
	return stream;
}

void ShellNotificationModule::error(vmi::Module *module, std::string message){
	this->error(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::error(vmi::Module *module){
	std::ostream & stream = ((this->debugLevel >= vmi::OUTPUT_ERROR) ? std::cout : this->nullStream );
	stream << "Error:       " << module->getName() << ": ";
	return stream;
}

void ShellNotificationModule::critical(vmi::Module *module, std::string message){
	this->critical(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::critical(vmi::Module *module){
	std::ostream & stream = ((this->debugLevel >= vmi::OUTPUT_CRITICAL) ? std::cout : this->nullStream );
	stream << "Critical:    " << module->getName() << ": ";
	return stream;
}

void ShellNotificationModule::alert(vmi::Module *module, std::string message){
	this->alert(module) << message << std::endl;
}

std::ostream& ShellNotificationModule::alert(vmi::Module *module){
	std::ostream & stream = ((this->debugLevel >= vmi::OUTPUT_ALERT) ? std::cout : this->nullStream );
	stream << "Alert:       " << module->getName() << ": ";
	return stream;
}
*/
