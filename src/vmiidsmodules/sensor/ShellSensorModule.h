/*
 * ShellSensorModule.h
 *
 *  Created on: Jul 2, 2010
 *      Author: kittel
 */

#ifndef SHELLSENSORMODULE_H_
#define SHELLSENSORMODULE_H_

#include "SensorModule.h"
#include "NotificationModule.h"
#include "libvmi.h"

#include <map>
#include <set>

/*!
 * \exception ShellParserException ShellSensorModule.h
 * \brief Exception for ShellSensorModule.
 */
class ShellParserException: public std::exception {
	virtual const char* what() const throw () {
		return "ShellSensorModule abort";
	}
};

typedef struct{
	uint32_t pid;
	std::string processName;
} ShellProcess;

/*!
 * \class ShellSensorModule ShellSensorModule.h
 *
 * \brief Parser for a Serial Shell Session.
 */
class ShellSensorModule : public vmi::SensorModule , public libVMI::ConsoleMonitor {
private:
	vmi::NotificationModule * notify;

	std::string optionMonitorShell;
	std::string optionLoginShell;
	std::string optionPasswordShell;

	bool loggedin;
	bool login(std::string username, std::string password);
	void logout();

	bool isLoggedin(void);

public:
	ShellSensorModule();
	virtual ~ShellSensorModule();

	void initSensorModule();

	std::map<uint32_t, ShellProcess> getProcessList();
	std::set<std::string> getFileList(std::string directory);
};

#endif /* SHELLSENSORMODULE_H_ */
