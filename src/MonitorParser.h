#ifndef _MONITORPARSER_H_
#define _MONITORPARSER_H_

/*!
 * \defgroup MonitorParser
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * \section QEMU
 * etc...
 */

#include "ConsoleMonitor.h"

namespace libVMI {

class MonitorParserException: public std::exception {
	virtual const char* what() const throw () {
		return "ConsoleMonitor abort";
	}
};

class MonitorParser : public ConsoleMonitor {
	public:
		MonitorParser() throw(MonitorParserException);
		virtual ~MonitorParser();

		/*
		 * is the vm running
		 */
		bool isRunning() throw(MonitorParserException);
		void pauseVM() throw(MonitorParserException);
		void resumeVM() throw(MonitorParserException);
		void help(std::string &helptext) throw(MonitorParserException);
		void infoHelp(std::string &helptext) throw(MonitorParserException);
};

}
#endif /* _MONITORPARSER_H_ */
