/*
 * NotificationModule.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: kittel
 */

#include "NotificationModule.h"

#include "VmiIDS.h"

namespace vmi {

NotificationModule::NotificationModule(std::string moduleName): Module(moduleName) {
	std::string debugLevelString;
	try{
		GETOPTION(debugLevel, debugLevelString);
		if (debugLevelString.compare("INFO") == 0) {
			this->debugLevel = vmi::OUTPUT_INFO;
		} else if (debugLevelString.compare("DEBUG") == 0) {
			this->debugLevel = vmi::OUTPUT_DEBUG;
		} else if (debugLevelString.compare("WARN") == 0) {
			this->debugLevel = vmi::OUTPUT_WARN;
		} else if (debugLevelString.compare("ERROR") == 0) {
			this->debugLevel = vmi::OUTPUT_ERROR;
		} else if (debugLevelString.compare("CRITICAL") == 0) {
			this->debugLevel = vmi::OUTPUT_CRITICAL;
		} else if (debugLevelString.compare("ALERT") == 0) {
			this->debugLevel = vmi::OUTPUT_ALERT;
		} else {
			this->debugLevel = vmi::OUTPUT_INFO;
		}
	}catch(OptionNotFoundException &e){
		this->debugLevel = vmi::OUTPUT_INFO;
	}
};

}
