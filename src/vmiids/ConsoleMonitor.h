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
	
	pthread_t thread; //!< Thread to monitor the serial console

	pthread_mutex_t queuemutex; //!< Mutex to handle queue accesses.
	std::queue <char> queuecontainer; //!< Internal queue to hold received data.
	bool threadRunning; //!< Is the internal thread running?
	int threadStarted; //!< Is the internal thread started?

	pthread_mutex_t monitorMutex; //!< Mutex to handle reentrance.

	protected:
		std::string monitorShell; //!< Shell string

		/**
		 * Send a command to the associated shell.
		 * @param command
		 * @return Zero, if command was sent successfully, otherwise -1.
		 */
		int sendCommand(const char * command) throw(ConsoleMonitorException);

		/**
		 * Read the contents of the internal queue.
		 * @param output String to store contents in.
		 */
		void parseOutput(std::string &output) throw(ConsoleMonitorException);
	
	public:
		/**
		 * Default Constructor
		 * @return
		 */
		ConsoleMonitor() throw(ConsoleMonitorException);
		/**
		 * Constructor
		 * @param consoleString Shell device (eg. /dev/ttyS1)
		 * @param shellString Shell prompt (for the internal parser).
		 * @return
		 */
		ConsoleMonitor(std::string consoleString,std::string shellString) throw(ConsoleMonitorException);
		/**
		 * Destructor
		 * @return
		 */
		virtual ~ConsoleMonitor();

		/**
		 * Initialize the ConsoleMonitor
		 * @param consoleString Shell device (eg. /dev/ttyS1)
		 * @param shellString Shell prompt (for the internal parser).
		 * @return
		 */
		void initConsoleMonitor(std::string consoleString, std::string shellString) throw(ConsoleMonitorException);

		/**
		 * Send a command to the underlying shell and retrieve the result.
		 * @param command Command to send to the underlying shell.
		 * @param output String to store the commands output in.
		 *
		 */
		void parseCommandOutput(const char *command, std::string &output) throw(ConsoleMonitorException);
		/**
		 * Send a command to the underlying shell and retrieve the result.
		 * @param command Command to send to the underlying shell.
		 * @param output String to store the commands output in.
		 *
		 */
		void parseCommandOutput(std::string command, std::string &output) throw(ConsoleMonitorException);

		/**
		 * Quit ConsoleMonitor Thread.
		 */
		void killThread(void) throw(ConsoleMonitorException);
	
	private:	
		std::string consoleName; //!< Shell device (eg. /dev/ttyS1)

		/**
		 * Main function of the console monitor thread.
		 * @param ptr Pointer to the appropriate ConsoleMonitor instance.
		 */
		static void* readMonitor(void *ptr);
};

}

#endif /* __CONSOLEMONITOR_H_ */
