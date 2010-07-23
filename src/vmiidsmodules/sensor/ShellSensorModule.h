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

/*!
 * \exception ShellParserException ShellParser.h
 * \brief Exception for ShellParser.
 */
class ShellParserException: public std::exception {
	virtual const char* what() const throw () {
		return "ShellParser abort";
	}
};


/*!
 * \class ShellSensorModule ShellSensorModule.h
 *
 * \brief Parser for a Serial Shell Session.
 */
class ShellSensorModule : public SensorModule , public libVMI::ConsoleMonitor {
private:
	NotificationModule * notify;

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
};

#endif /* SHELLSENSORMODULE_H_ */
