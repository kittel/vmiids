/*
 * FileNotificationModule.cpp
 *
 *  Created on: Aug 16, 2010
 *      Author: kittel
 */

#include "FileNotificationModule.h"
#include "vmiids/VmiIDS.h"

#include <iostream>

LOADNOTIFICATIONMODULE(FileNotificationModule);

FileNotificationModule::FileNotificationModule() :
		NotificationModule("FileNotificationModule") {
	std::string fileName;
	GETOPTION(fileName, fileName);

	outfile.open(fileName.c_str(), std::ios_base::out | std::ios_base::trunc);
}

FileNotificationModule::~FileNotificationModule() {
	outfile.close();
}

void FileNotificationModule::doDebug(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_DEBUG){
		outfile << "Debug:       " << module << ": " << message;
		outfile.flush();
	}
}

void FileNotificationModule::doInfo(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_INFO){
		outfile << "Information: " << module << ": " << message;
		outfile.flush();
	}
}

void FileNotificationModule::doWarn(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_WARN){
		outfile << "Warning:     " << module << ": " << message;
		outfile.flush();
	}
}

void FileNotificationModule::doError(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_ERROR){
		outfile << "Error:       " << module << ": " << message;
		outfile.flush();
	}
}

void FileNotificationModule::doCritical(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_CRITICAL){
		outfile << "Critical:    " << module << ": " << message;
		outfile.flush();
	}
}

void FileNotificationModule::doAlert(std::string module, std::string message){
	if(debugLevel <= vmi::OUTPUT_ALERT){
		outfile << "Alert:       " << module << ": " << message;
		outfile.flush();
	}
}
