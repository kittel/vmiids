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

	virtual void doDebug(std::string module, std::string message);
	virtual void doInfo(std::string module, std::string message);
	virtual void doWarn(std::string module, std::string message);
	virtual void doError(std::string module, std::string message);
	virtual void doCritical(std::string module, std::string message);
	virtual void doAlert(std::string module, std::string message);

};

#endif /* SHELLNOTIFICATIONMODULE_H_ */
