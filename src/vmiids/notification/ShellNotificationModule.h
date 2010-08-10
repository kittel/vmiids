/*
 * ShellNotificationModule.h
 *
 *  Created on: Jun 30, 2010
 *      Author: kittel
 */

#ifndef SHELLNOTIFICATIONMODULE_H_
#define SHELLNOTIFICATIONMODULE_H_

#include "vmiids/NotificationModule.h"

class ShellNotificationModule : public vmi::NotificationModule {
public:

	ShellNotificationModule();
	virtual ~ShellNotificationModule();

	virtual void info(vmi::Module *module, std::string message);
	virtual void debug(vmi::Module *module, std::string message);
	virtual void warn(vmi::Module *module, std::string message);
	virtual void error(vmi::Module *module, std::string message);
	virtual void critical(vmi::Module *module, std::string message);
	virtual void alert(vmi::Module *module, std::string message);

	virtual std::ostream& info(vmi::Module *module);
	virtual std::ostream& debug(vmi::Module *module);
	virtual std::ostream& warn(vmi::Module *module);
	virtual std::ostream& error(vmi::Module *module);
	virtual std::ostream& critical(vmi::Module *module);
	virtual std::ostream& alert(vmi::Module *module);
};

#endif /* SHELLNOTIFICATIONMODULE_H_ */
