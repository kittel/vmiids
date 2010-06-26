#ifndef _SHELL_H_
#define _SHELL_H_

#include "ConsoleMonitor.h"

#include <pthread.h>

namespace libVMI {

/*!
 * \exception ShellParserException ShellParser.h
 * \brief Exception for ShellParser.
 */
class ShellException: public std::exception {
	virtual const char* what() const throw () {
		return "Shell abort";
	}
};

class Shell : public ConsoleMonitor {
	private:
		pthread_t readThread;
		pthread_t writeThread;
		bool threadRunning;

		static void * shellRead(void * ptr);
		static void * shellWrite(void * ptr);
		static void signal_handler(int signum);

	public:
		Shell();
		virtual ~Shell();

		void startShell(void);
		void stopShell(void);
};

}

#endif /* _SHELL_H_ */
