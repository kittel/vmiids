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

		virtual void info(Module *module, std::string message) = 0;
		virtual void debug(Module *module, std::string message) = 0;
		virtual void warn(Module *module, std::string message) = 0;
		virtual void error(Module *module, std::string message) = 0;
		virtual void critical(Module *module, std::string message) = 0;
		virtual void alert(Module *module, std::string message) = 0;

		virtual std::ostream& info(Module *module) = 0;
		virtual std::ostream& debug(Module *module) = 0;
		virtual std::ostream& warn(Module *module) = 0;
		virtual std::ostream& error(Module *module) = 0;
		virtual std::ostream& critical(Module *module) = 0;
		virtual std::ostream& alert(Module *module) = 0;
};

}

#include "VmiIDS.h"

#define ADDDYNAMICNOTIFICATIONMODULE(classname, line) class CONCAT(proxy, line) { \
	public: \
	CONCAT(proxy, line)(){ try { \
		                       std::cerr << "Loading NotificationModule " << QUOTE(classname) << "... "; \
	                           vmi::VmiIDS::getInstance()->enqueueNotificationModule(new classname); \
		                       std::cerr << "Success" << std::endl; \
                           } \
	                       catch (vmi::ModuleException &e){ \
		                       std::cerr << "FAILED" << std::endl; \
	                    	   e.printException(); \
	                       } \
	                       catch (std::exception &e){ \
	                    	   std::cerr << "FAILED" << std::endl; \
	                    	   std::cerr << e.what() << std::endl; \
	                       } \
	                     } \
	}; \
static CONCAT(proxy, line) CONCAT(p, line);

#define GETNOTIFICATIONMODULE(variable, modulename) \
		variable = vmi::VmiIDS::getInstance()->getNotificationModule(QUOTE(modulename)); \
		if (!variable) { \
			throw vmi::DependencyNotFoundException(QUOTE(modulename)); \
		}

#endif /* NOTIFICATIONMODULE_H_ */
