/*
 * RpcNotificationModule.h
 *
 *  Created on: Aug 16, 2010
 *      Author: kittel
 */

#ifndef RPCNOTIFICATIONMODULE_H_
#define RPCNOTIFICATIONMODULE_H_

#include "vmiids/NotificationModule.h"

#include <sstream>

class RpcNotificationModule: public vmi::NotificationModule {
private:
	std::stringstream stream;

public:
	RpcNotificationModule();
	virtual ~RpcNotificationModule();

	std::string getRpcResult();

	virtual void doDebug(std::string module, std::string message);
	virtual void doInfo(std::string module, std::string message);
	virtual void doWarn(std::string module, std::string message);
	virtual void doError(std::string module, std::string message);
	virtual void doCritical(std::string module, std::string message);
	virtual void doAlert(std::string module, std::string message);
};

#endif /* RPCNOTIFICATIONMODULE_H_ */
