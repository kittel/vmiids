/*
 * NotificationModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef NOTIFICATIONMODULE_H_
#define NOTIFICATIONMODULE_H_

#include "Module.h"

#include <ostream>

namespace vmi {

class NotificationModule : public vmi::Module{

	public:
		NotificationModule(std::string moduleName) : vmi::Module(moduleName) {};

		virtual void info(std::string message) = 0;
		virtual void debug(std::string message) = 0;
		virtual void warn(std::string message) = 0;
		virtual void error(std::string message) = 0;
		virtual void critical(std::string message) = 0;
		virtual void alert(std::string message) = 0;

		virtual std::ostream& info() = 0;
		virtual std::ostream& debug() = 0;
		virtual std::ostream& warn() = 0;
		virtual std::ostream& error() = 0;
		virtual std::ostream& critical() = 0;
		virtual std::ostream& alert() = 0;
};

}

#include "VmiIDS.h"

#define ADDDYNAMICNOTIFICATIONMODULE_H_(classname, line) class CONCAT(proxy, line) { \
	public: \
	CONCAT(proxy, line)(){ vmi::VmiIDS::getInstance()->enqueueNotificationModule(new classname);  } \
}; \
static CONCAT(proxy, line) CONCAT(p, line);

#endif /* NOTIFICATIONMODULE_H_ */
