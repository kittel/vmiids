/*
 * ShellNotificationModule.h
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#ifndef SHELLNOTIFICATIONMODULE_H_
#define SHELLNOTIFICATIONMODULE_H_

#include "NotificationModule.h"

class ShellNotificationModule : public NotificationModule {
public:

	ShellNotificationModule();
	virtual ~ShellNotificationModule();

	virtual void info(std::string message);
	virtual void debug(std::string message);
	virtual void warn(std::string message);
	virtual void error(std::string message);
	virtual void critical(std::string message);
	virtual void alert(std::string message);

	virtual std::ostream& info();
	virtual std::ostream& debug();
	virtual std::ostream& warn();
	virtual std::ostream& error();
	virtual std::ostream& critical();
	virtual std::ostream& alert();
};

#endif /* SHELLNOTIFICATIONMODULE_H_ */
