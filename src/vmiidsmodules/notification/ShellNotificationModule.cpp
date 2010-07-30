/*
 * ShellNotificationModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include <iostream>

#include "ShellNotificationModule.h"

ADDDYNAMICNOTIFICATIONMODULE_H_(ShellNotificationModule, __LINE__);

ShellNotificationModule::ShellNotificationModule() : NotificationModule("ShellNotificationModule"){

}

ShellNotificationModule::~ShellNotificationModule() {
	// TODO Auto-generated destructor stub
}

void ShellNotificationModule::info(std::string message){
	this->info() << message << std::endl;
}

virtual std::ostream& info(){
	std::cout << "Information: ";
	return std::cout;
}

void ShellNotificationModule::debug(std::string message){
	this->debug() << message << std::endl;
}

virtual std::ostream& debug(){
	std::cout << "Debug:       ";
	return std::cout;
}

void ShellNotificationModule::warn(std::string message){
	this->warn() << message << std::endl;
}

virtual std::ostream& warn(){
	std::cout << "Warning:     ";
	return std::cout;
}

void ShellNotificationModule::error(std::string message){
	this->error() << message << std::endl;
}

virtual std::ostream& error(){
	std::cout << "Error:       ";
	return std::cout;
}

void ShellNotificationModule::critical(std::string message){
	this->critical() << message << std::endl;
}

virtual std::ostream& critical(){
	std::cout << "Critical:    ";
	return std::cout;
}

void ShellNotificationModule::alert(std::string message){
	this->alert() << message << std::endl;
}

virtual std::ostream& alert(){
	std::cout << "Alert:    ";
	return std::cout;
}
