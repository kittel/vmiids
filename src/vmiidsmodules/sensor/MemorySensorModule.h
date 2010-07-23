/*
 * MemorySensorModule.h
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#ifndef MEMORYSENSORMODULE_H_
#define MEMORYSENSORMODULE_H_

#include "SensorModule.h"

/*!
 * \exception MemorySensorModuleException MemorySensorModule.h
 * \brief Exception for MemorySensorModule.
 */
class MemorySensorModuleException: public std::exception {
	virtual const char* what() const throw () {
		return "MemorySensorModule abort";
	}
};

class MemorySensorModule : public SensorModule{
public:
	MemorySensorModule();
	virtual ~MemorySensorModule();

	void getProcessList(std::string &processList);


	void initSensorModule();

private:
	NotificationModule * notify;

	std::string memtoolPath;
	std::string memtoolScriptPath;

	std::string savedDebugingSymbols;
	std::string memdumpFile;

	void runScript(std::string &scriptResult, std::string scriptName);

};

#endif /* MEMORYSENSORMODULE_H_ */
