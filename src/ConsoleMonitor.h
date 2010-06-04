#ifndef __CONSOLEMONITOR_H_
#define __CONSOLEMONITOR_H_

#include <pthread.h>
#include <queue>
#include <string>

namespace libVMI {

class ConsoleMonitor {
	
	pthread_t thread;
	const char * consoleName;
	pthread_mutex_t queuemutex;
	std::queue <char> queuecontainer;
	bool threadRunning;

	protected:
		const char * monitorShell;
		
		int sendCommand(const char * command);
		void parseOutput(std::string &output);
	
	public:
		ConsoleMonitor(const char* consoleString, const char* shellString);
		virtual ~ConsoleMonitor();

		void parseCommandOutput(const char *command, std::string &output);
		void killThread(void);
	
	private:	

		static void signal_handler(int signum);
		static void* readMonitor(void *ptr);
};

}

#endif /* __CONSOLEMONITOR_H_ */
