#ifndef __CONSOLEMONITOR_H_
#define __CONSOLEMONITOR_H_

#include <pthread.h>
#include <queue>
#include <string>

namespace libVMI {


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
	const char * consoleName;
	pthread_mutex_t queuemutex;
	std::queue <char> queuecontainer;
	bool threadRunning;
	bool threadStarted;

	protected:
		const char * monitorShell;
		
		int sendCommand(const char * command) throw(ConsoleMonitorException);
		void parseOutput(std::string &output) throw(ConsoleMonitorException);
	
	public:
		ConsoleMonitor(const char* consoleString, const char* shellString) throw(ConsoleMonitorException);
		virtual ~ConsoleMonitor();

		void parseCommandOutput(const char *command, std::string &output) throw(ConsoleMonitorException);
		void killThread(void) throw(ConsoleMonitorException);
	
	private:	

		static void signal_handler(int signum);
		static void* readMonitor(void *ptr);
};

}

#endif /* __CONSOLEMONITOR_H_ */
