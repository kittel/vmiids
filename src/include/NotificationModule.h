/*
 * NotificationModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef NOTIFICATIONMODULE_H_
#define NOTIFICATIONMODULE_H_

#include <string>

class NotificationModule{
	private:
		std::string moduleName;

	public:
		NotificationModule(std::string moduleName){ this->moduleName = moduleName;};
		std::string getName(){ return this->moduleName; };
		virtual void warn() = 0;
		virtual void info() = 0;
		virtual void debug() = 0;
		virtual void error() = 0;
		virtual void critical() = 0;
};

#include "VmiIDS.h"

#define ADDDYNAMICNOTIFICATIONMODULE_H_(classname) class proxy { \
	public: \
	proxy(){ VmiIDS::getInstance()->enqueueNotificationModule(new classname);  } \
}; \
static proxy p;

#endif /* NOTIFICATIONMODULE_H_ */
