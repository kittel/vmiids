/*
 * ShellNotificationModule.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#include <iostream>

#include "ShellNotificationModule.h"

LOADNOTIFICATIONMODULE(ShellNotificationModule);

ShellNotificationModule::ShellNotificationModule() : NotificationModule("ShellNotificationModule"){

}

ShellNotificationModule::~ShellNotificationModule() {
	// TODO Auto-generated destructor stub
}

void ShellNotificationModule::doDebug(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_DEBUG)
		std::cout << "Debug:       " << module << ": " << message;
}

void ShellNotificationModule::doInfo(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_INFO)
		std::cout << "Information: " << module << ": " << message;
}

void ShellNotificationModule::doWarn(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_WARN)
		std::cout << "Warning:     " << module << ": " << message;
}

void ShellNotificationModule::doError(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_ERROR)
		std::cout << "Error:       " << module << ": " << message;
}

void ShellNotificationModule::doCritical(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_CRITICAL)
		std::cout << "Critical:    " << module << ": " << message;
}

void ShellNotificationModule::doAlert(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_ALERT)
		std::cout << "Alert:       " << module << ": " << message;
}
