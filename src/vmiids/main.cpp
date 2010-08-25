/*
 * main.cpp
 *
 *  Created on: Aug 25, 2010
 *      Author: tom
 */

#include "vmiids/VmiIDS.h"

#include <signal.h>
#include <execinfo.h>
#include <ucontext.h>
#include <cxxabi.h>

// rpcthread SIGTERM
	//pthread_exit(NULL);

	// mainThread SIGTERM
	//vmi::VmiIDS::getInstance()->stopIDS(signum);

	// moduleThread SIGSEGV
	//stackTrace
	//blacklist module
	//pthread_exit()

int signal_handler_sigint = 0;

/**
 * Static signal handler function set in main.
 * @param sig_num
 * @param info
 * @param ucontext
 */
void signal_handler(int sig_num, siginfo_t * info, void * ucontext) {
	if (sig_num == SIGINT) {
		if(!signal_handler_sigint) {
			vmi::VmiIDS::getInstance()->stopIDS(sig_num);
			signal_handler_sigint++;
		}else{
			pthread_exit(NULL);
		}
	}else if (sig_num == SIGTERM) {
			pthread_exit(NULL);
	} else if (sig_num == SIGSEGV) {
		void * array[50];
		void * caller_address;
		char ** messages;
		int size, i;
		struct ucontext * uc;

		uc = (struct ucontext *) ucontext;

		/* Get the address at the time the signal was raised from the EIP (x86) */
#if __WORDSIZE == 64

		caller_address = (void *) uc->uc_mcontext.gregs[REG_RIP];

#else /* __WORDSIZE == 32 */

		caller_address = (void *) uc->uc_mcontext.gregs[REG_EIP];

#endif /* __WORDSIZE == 32 */

		fprintf(stderr, "signal %d (%s), address is %p from %p\n", sig_num,
				strsignal(sig_num), info->si_addr, (void *) caller_address);

		size = backtrace(array, 50);

		messages = backtrace_symbols(array, size);

		/* skip first stack frame (points here) */
		for (i = 2; i < size && messages != NULL; ++i) {
			std::string trace(messages[i]);

			// attempt to demangle
			{
				std::string::size_type begin, end;

				// find the beginning and the end of the useful part of the trace
				begin = trace.find_first_of('(') + 1;
				end = trace.find_last_of('+');

				// if they were found, we'll go ahead and demangle
				if (begin != std::string::npos && end != std::string::npos) {
					std::string functionName = trace.substr(begin, end - begin);

					int demangleStatus;

					char* demangledName;
					if ((demangledName = abi::__cxa_demangle(
							functionName.c_str(), 0, 0, &demangleStatus))
							&& demangleStatus == 0) {
						trace.replace(begin, end - begin, demangledName); // the demangled name is now in our trace string
					}
					free(demangledName);
				}
			}
			fprintf(stderr, "[bt]: (%d) %s\n", i - 1, trace.c_str());
		}

		free(messages);

		pthread_exit(NULL);
	}
}

/**
 * Main Function
 * @return
 */
int main() {

	struct sigaction signal_action;

	/* Set up the structure to specify the new action. */
	signal_action.sa_sigaction = signal_handler;
	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_flags = SA_RESTART | SA_SIGINFO;

	//To catch crtl c
	sigaction(SIGINT, &signal_action, NULL);
	//To kill threads
	sigaction(SIGTERM, &signal_action, NULL);
	//To catch segfaults
	sigaction(SIGSEGV, &signal_action, NULL);

	vmi::VmiIDS::getInstance()->start();
	vmi::VmiIDS::getInstance()->join();

	exit(0);
}
