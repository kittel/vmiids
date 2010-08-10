#ifndef __CONSOLEMONITOR_H_
#define __CONSOLEMONITOR_H_

#include <pthread.h>
#include <queue>
#include <string>

namespace vmi {

/*!
 * \exception ConsoleMonitorException ConsoleMonitor.h
 * \brief Exception for ConsoleMonitor.
 */
class ConsoleMonitorException: public std::exception {
	virtual const char* what() const throw () {
		return "ConsoleMonitor abort";
	}
};

/*!
 * \class ConsoleMonitor ConsoleMonitor.h
 *
 * \brief Backend for Serial Console parsing.
 *
 */
class ConsoleMonitor {
	
	pthread_t thread;

	pthread_mutex_t queuemutex;
	std::queue <char> queuecontainer;
	bool threadRunning;
	int threadStarted;

	protected:
		std::string monitorShell;

		int sendCommand(const char * command) throw(ConsoleMonitorException);
		void parseOutput(std::string &output) throw(ConsoleMonitorException);
	
	public:
		ConsoleMonitor() throw(ConsoleMonitorException);
		ConsoleMonitor(std::string consoleString,std::string shellString) throw(ConsoleMonitorException);
		virtual ~ConsoleMonitor();

		void initConsoleMonitor(std::string consoleString, std::string shellString) throw(ConsoleMonitorException);

		void parseCommandOutput(const char *command, std::string &output) throw(ConsoleMonitorException);
		void parseCommandOutput(std::string command, std::string &output) throw(ConsoleMonitorException);

		void killThread(void) throw(ConsoleMonitorException);
	
	private:	
		std::string consoleName;

		static void signal_handler(int signum);
		static void* readMonitor(void *ptr);
};

}

#endif /* __CONSOLEMONITOR_H_ */
