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

class OutputModule {
	protected:
	vmi::NotificationStream debug;
	vmi::NotificationStream info;
	vmi::NotificationStream warn;
	vmi::NotificationStream error;
	vmi::NotificationStream critical;
	vmi::NotificationStream alert;

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
	void printWarn(const char * format, ...){
	  va_list args;
	  va_start (args, format);
	  char string[1024] = {0};
	  int length = vsnprintf(string, 1024, format, args);
	  if(length == 0) return;
	  warn << string;
	  va_end (args);
	}
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
	OutputModule(std::string moduleName) :
			debug(moduleName, vmi::NotificationModule::debug),
			info(moduleName, vmi::NotificationModule::info),
			warn(moduleName, vmi::NotificationModule::warn),
			error(moduleName, vmi::NotificationModule::error),
			critical(moduleName, vmi::NotificationModule::critical),
			alert(moduleName, vmi::NotificationModule::alert){};
		virtual ~OutputModule(){
		};

};

}

#endif /* OUTPUTMODULE_H_ */
