/*
 * MemorySensorModule.h
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#ifndef MEMORYSENSORMODULE_H_
#define MEMORYSENSORMODULE_H_

#include "vmiids/SensorModule.h"

#include <map>

/*!
 * \exception MemorySensorModuleException MemorySensorModule.h
 * \brief Exception for MemorySensorModule.
 */

#include <memtool/memtool.h>

class MemorySensorModuleException: public std::exception {
	virtual const char* what() const throw () {
		return "MemorySensorModule abort";
	}
};

typedef struct{
	uint32_t pid;
	std::string processName;
} MemtoolProcess;

class MemorySensorModule : public vmi::SensorModule{
public:
	MemorySensorModule();
	virtual ~MemorySensorModule();

	void getProcessList(std::map<uint32_t, MemtoolProcess> &memtoolProcessMap);

	void initSensorModule();

private:
	vmi::NotificationModule * notify;

    Memtool memtool;
	std::string memtooldPath;
	std::string memtoolScriptPath;

	std::string savedDebugingSymbols;
	std::string memdumpFile;

	std::string clearCacheCommand;

	void runScript(std::string &scriptResult, std::string scriptName);
	bool clearFSCache();

};

#endif /* MEMORYSENSORMODULE_H_ */
