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

void ShellNotificationModule::warn(std::string message){
	std::cout << "Warning:    " << message << std::endl;
}

void ShellNotificationModule::info(std::string message){
	std::cout << "Information " << message << std::endl;
}

void ShellNotificationModule::debug(std::string message){
	std::cout << "Debug:      " << message << std::endl;
}

void ShellNotificationModule::error(std::string message){
	std::cout << "Error:      " << message << std::endl;
}

void ShellNotificationModule::critical(std::string message){
	std::cout << "Critical:   " << message << std::endl;
}
