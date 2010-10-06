/*
 * OutputModule.h
 *
 *  Created on: Aug 16, 2010
 *      Author: kittel
 */

#ifndef OUTPUTMODULE_H_
#define OUTPUTMODULE_H_

#include "NotificationModule.h"
#include <cstdio>
#include <cstdarg>


namespace vmi {

/**
 * @class OutputModule OutputModule.h "vmiids/OutputModule.h"
 * @brief Wrapper for NotificationModules.
 * @sa vmi::NotificationModule
 * @sa vmi::NotificationStream
 *
 * This class contains output streams for different log severitys.
 * To output data, a Module must extend this class.
 *
 * Each message is prepended with the Name of the module causing the message.
 */
class OutputModule {
	protected:
	/**
	 * Debug stream
	 */
	vmi::NotificationStream debug;
	/**
	 * Information stream
	 */
	vmi::NotificationStream info;
	/**
	 * Warning stream
	 */
	vmi::NotificationStream warn;
	/**
	 * Error stream
	 */
	vmi::NotificationStream error;
	/**
	 * Critical stream
	 */
	vmi::NotificationStream critical;
	/**
	 * Alert stream
	 */
	vmi::NotificationStream alert;

	/**
	 * C-style debug function.
	 *
	 * Provided for convenience.
	 * Equal to printf(), this function expects an format string as input.
	 *
	 * @param format Format string
	 */
	void printDebug(const char * format, ...){
	  va_list args;
	  va_start (args, format);
	  char string[1024] = {0};
	  int length = vsnprintf(string, 1024, format, args);
	  if(length == 0) return;
	  debug << string;
	  debug.flush();
	  va_end (args);
	}

	/**
	 * C-style output function. Used for info output.
	 *
	 * Provided for convenience.
	 * Equal to printf(), this function expects an format string as input.
	 *
	 * @param format Format string
	 */
	void printInfo(const char * format, ...){
	  va_list args;
	  va_start (args, format);
	  char string[1024] = {0};
	  int length = vsnprintf(string, 1024, format, args);
	  if(length == 0) return;
	  info << string;
	  info.flush();
	  va_end (args);
	}

	/**
	 * C-style output function. Used for warn output.
	 *
	 * Provided for convenience.
	 * Equal to printf(), this function expects an format string as input.
	 *
	 * @param format Format string
	 */
	void printWarn(const char * format, ...){
	  va_list args;
	  va_start (args, format);
	  char string[1024] = {0};
	  int length = vsnprintf(string, 1024, format, args);
	  if(length == 0) return;
	  warn << string;
	  va_end (args);
	}

	/**
	 * C-style output function. Used for error output.
	 *
	 * Provided for convenience.
	 * Equal to printf(), this function expects an format string as input.
	 *
	 * @param format Format string
	 */
	void printError(const char * format, ...){
	  va_list args;
	  va_start (args, format);
	  char string[1024] = {0};
	  int length = vsnprintf(string, 1024, format, args);
	  if(length == 0) return;
	  error << string;
	  error.flush();
	  va_end (args);
	}

	/**
	 * C-style output function. Used for critical output.
	 *
	 * Provided for convenience.
	 * Equal to printf(), this function expects an format string as input.
	 *
	 * @param format Format string
	 */
	void printCritical(const char * format, ...){
	  va_list args;
	  va_start (args, format);
	  char string[1024] = {0};
	  int length = vsnprintf(string, 1024, format, args);
	  if(length == 0) return;
	  critical << string;
	  critical.flush();
	  va_end (args);
	}

	/**
	 * C-style output function. Used for alert output.
	 *
	 * Provided for convenience.
	 * Equal to printf(), this function expects an format string as input.
	 *
	 * @param format Format string
	 */
	void printAlert(const char * format, ...){
	  va_list args;
	  va_start (args, format);
	  char string[1024] = {0};
	  int length = vsnprintf(string, 1024, format, args);
	  if(length == 0) return;
	  alert << string;
	  alert.flush();
	  va_end (args);
	}

	public:
	/**
	 * Constructor
	 * @param moduleName Name to be prepended in front of any output.
	 */
	OutputModule(std::string moduleName) :
			debug(moduleName, vmi::NotificationModule::debug),
			info(moduleName, vmi::NotificationModule::info),
			warn(moduleName, vmi::NotificationModule::warn),
			error(moduleName, vmi::NotificationModule::error),
			critical(moduleName, vmi::NotificationModule::critical),
			alert(moduleName, vmi::NotificationModule::alert){};

	/**
	 * Destructor
	 */
	virtual ~OutputModule(){};

};

}

#endif /* OUTPUTMODULE_H_ */
