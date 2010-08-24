/*
 * FileNotificationModule.h
 *
 *  Created on: Aug 16, 2010
 *      Author: kittel
 */

#ifndef FILENOTIFICATIONMODULE_H_
#define FILENOTIFICATIONMODULE_H_

#include "vmiids/NotificationModule.h"

#include <fstream>

class FileNotificationModule: public vmi::NotificationModule {
private:
	std::ofstream outfile;

public:
	FileNotificationModule();
	virtual ~FileNotificationModule();

	virtual void doDebug(std::string module, std::string message);
	virtual void doInfo(std::string module, std::string message);
	virtual void doWarn(std::string module, std::string message);
	virtual void doError(std::string module, std::string message);
	virtual void doCritical(std::string module, std::string message);
	virtual void doAlert(std::string module, std::string message);
};

#endif /* FILENOTIFICATIONMODULE_H_ */
