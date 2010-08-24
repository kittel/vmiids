/*
 * MemorySensorModule.h
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#ifndef MEMORYSENSORMODULE_H_
#define MEMORYSENSORMODULE_H_

#include "vmiids/SensorModule.h"

#include <memtool/memtool.h>

#include <map>
#include <QCoreApplication>

/*!
 * \exception MemorySensorModuleException MemorySensorModule.h
 * \brief Exception for MemorySensorModule.
 */

class MemtoolNotRunningException: public vmi::ModuleException {
	virtual const char* what() const throw () {
		return "Memtool Not Running";
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
	static QCoreApplication* app;
	static Memtool* memtool;
	int null;

	static void stopMemtool(void);

    std::string memtooldPath;
	std::string libmemtoolPath;
	std::string memtoolScriptPath;

	std::string savedDebugingSymbols;
	std::string memdumpFile;

	std::string clearCacheCommand;

	bool clearFSCache();

};

#endif /* MEMORYSENSORMODULE_H_ */
