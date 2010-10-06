/*
 * BufferNotificationModule.h
 *
 *  Created on: Aug 16, 2010
 *      Author: kittel
 */

#ifndef BUFFERNOTIFICATIONMODULE_H_
#define BUFFERNOTIFICATIONMODULE_H_

#include "vmiids/NotificationModule.h"

#include <sstream>

/**
 * @class BufferNotificationModule BufferNotificationModule.h "vmiids/modules/notification/BufferNotificationModule.h"
 * @brief Output to a buffer
 * @sa vmi::NotificationModule
 *
 * This module is built to store the frameworks output in an internal buffer.
 * The buffer can be received by using the getBuffer() function.
 */
class BufferNotificationModule: public vmi::NotificationModule {
private:
	std::stringstream stream;

public:
	/**
	 * Constructor
	 */
	BufferNotificationModule();
	/**
	 * Destructor
	 */
	virtual ~BufferNotificationModule();

	/**
	 * Receive a buffer containing the currently recorded data.
	 * When the buffer is requested by a user the internal buffer is flushed.
	 *
	 * @return String containing the currently recorded data.
	 */
	std::string getBuffer();

	virtual void doDebug(std::string module, std::string message);
	virtual void doInfo(std::string module, std::string message);
	virtual void doWarn(std::string module, std::string message);
	virtual void doError(std::string module, std::string message);
	virtual void doCritical(std::string module, std::string message);
	virtual void doAlert(std::string module, std::string message);
};

#endif /* RPCNOTIFICATIONMODULE_H_ */
