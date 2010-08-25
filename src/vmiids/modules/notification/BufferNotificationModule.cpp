/*
 * BufferNotificationModule.cpp
 *
 *  Created on: Aug 16, 2010
 *      Author: kittel
 */

#include "BufferNotificationModule.h"
#include "vmiids/VmiIDS.h"


BufferNotificationModule::BufferNotificationModule() :
		NotificationModule("RpcNotificationModule") {
}

BufferNotificationModule::~BufferNotificationModule() {
}

std::string BufferNotificationModule::getBuffer(){
	std::string result(stream.str());
	stream.str("");
	return result;
}

void BufferNotificationModule::doDebug(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_DEBUG){
		stream << "Debug:       " << module << ": " << message;
	}
}

void BufferNotificationModule::doInfo(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_INFO){
		stream << "Information: " << module << ": " << message;
	}
}

void BufferNotificationModule::doWarn(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_WARN){
		stream << "Warning:     " << module << ": " << message;
	}
}

void BufferNotificationModule::doError(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_ERROR){
		stream << "Error:       " << module << ": " << message;
	}
}

void BufferNotificationModule::doCritical(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_CRITICAL){
		stream << "Critical:    " << module << ": " << message;
	}
}

void BufferNotificationModule::doAlert(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_ALERT){
		stream << "Alert:       " << module << ": " << message;
	}
}
