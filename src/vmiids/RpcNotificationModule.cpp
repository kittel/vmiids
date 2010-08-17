/*
 * RpcNotificationModule.cpp
 *
 *  Created on: Aug 16, 2010
 *      Author: kittel
 */

#include "RpcNotificationModule.h"
#include "vmiids/VmiIDS.h"


RpcNotificationModule::RpcNotificationModule() :
		NotificationModule("RpcNotificationModule") {
}

RpcNotificationModule::~RpcNotificationModule() {
}

std::string RpcNotificationModule::getRpcResult(){
	std::string result(stream.str());
	stream.str("");
	return result;
}

void RpcNotificationModule::doDebug(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_DEBUG){
		stream << "Debug:       " << module << ": " << message;
	}
}

void RpcNotificationModule::doInfo(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_INFO){
		stream << "Information: " << module << ": " << message;
	}
}

void RpcNotificationModule::doWarn(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_WARN){
		stream << "Warning:     " << module << ": " << message;
	}
}

void RpcNotificationModule::doError(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_ERROR){
		stream << "Error:       " << module << ": " << message;
	}
}

void RpcNotificationModule::doCritical(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_CRITICAL){
		stream << "Critical:    " << module << ": " << message;
	}
}

void RpcNotificationModule::doAlert(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_ALERT){
		stream << "Alert:       " << module << ": " << message;
	}
}
