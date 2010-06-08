#ifndef _MONITORPARSER_H_
#define _MONITORPARSER_H_

#include "ConsoleMonitor.h"

namespace libVMI {

class MonitorParser : public ConsoleMonitor {
	public:
		MonitorParser();
		virtual ~MonitorParser();

		bool isRunning();
		void pauseVM();
		void resumeVM();
		void help(std::string &helptext);
		void infoHelp(std::string &helptext);
};

}
#endif /* _MONITORPARSER_H_ */
