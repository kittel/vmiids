/*
 * Thread.h
 *
 *  Created on: Aug 25, 2010
 *      Author: tom
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <time.h>
#include <exception>

namespace vmi {

/**
 * @class Thread Thread.h "vmiids/util/Thread.h"
 * @brief Thread class.
 * @sa Mutex
 *
 * Convenience class for pthreads.
 *
 * To generate a new thread a class has to extend the Thread class.
 * A subclass has to implement an own run() function. The thread is
 * started by calling the start() function.
 *
 * Equivalent to QTs QThread.
 */
class Thread {
private:
	pthread_t __thisThread; //!< Underlying pthread
	pthread_mutex_t __threadMutex; //!< Mutex, used that a thread can only be run once.

	static void (*defaultExceptionHandler)(std::exception&);  //!< Default function called, when an exception within the thread is not caught.
	void (*exceptionHandler)(std::exception&);        //!< Function called, when an exception within the thread is not caught.

	/**
	 * Start the thread and catch any exceptions thrown.
	 * If set, call an exception handler.
	 *
	 * @param ptr Pointer to instance of the Thread to start.
	 */
	static void* __runThread(void* ptr){
		Thread *this_p = (Thread *) ptr;
		pthread_mutex_lock(&this_p->__threadMutex);
		try {
			this_p->run();
		} catch (std::exception &e) {
			if(this_p->exceptionHandler != NULL){
				this_p->exceptionHandler(e);
			}else{
				if(defaultExceptionHandler != NULL){
					defaultExceptionHandler(e);
				}
			}
		}
		pthread_mutex_unlock(&this_p->__threadMutex);
		return NULL;
	}

public:
	/**
	 * Constructor
	 *
	 * Initializes internal mutex.
	 */
	Thread(){
		exceptionHandler = NULL;
		pthread_mutex_init(&__threadMutex, NULL);
	}
	/**
	 * Destructor
	 *
	 * Destroys internal mutex.
	 */
	virtual ~Thread(){
		pthread_mutex_lock(&__threadMutex);
		pthread_mutex_unlock(&__threadMutex);
		pthread_mutex_destroy(&__threadMutex);
	}

	/**
	 * Waits for this thread to die.
	 */
	void join(){
		pthread_join(__thisThread, NULL);
	}

	/**
	 * Kill the thread.
	 */
	void stop(){
		pthread_cancel(__thisThread);
	}

	/**
	 * Threads main function. Reimplement to create own Thread.
	 */
	virtual void run(void) = 0;

	/**
	 * Causes this thread to begin execution; the Thread class calls the run method of this thread.
	 */
	void start(void){
		pthread_create(&__thisThread, NULL, Thread::__runThread,
					(void*) this);
	}

	/**
	 * Sleep millis milli seconds.
	 *
	 * @param millis Time to sleep (in ms).
	 */
	static void sleep(unsigned long millis){
		struct timespec req = { 0, 0};
		time_t sec = (int) (millis / 1000);
		millis = millis - (sec * 1000);
		req.tv_sec = sec;
		req.tv_nsec = millis * 1000000L;
		while (nanosleep(&req, &req) == -1)
			continue;
		return;
	}

	/**
	 * Set the default handler for uncaught exceptions.
	 * The function is called if a thread does not catch a thrown exception and no thread specific handler was set.
	 *
	 * @param handler Handler function.
	 */
	static void setDefaultUncaughtExceptionHandler(void (*handler)(std::exception&)){
		defaultExceptionHandler = handler;
	}

	/**
	 * Set the handler for uncaught exceptions. The function is called if the thread does not catch a thrown exception.
	 *
	 * @param handler Handler function.
	 */
	void setUncaughtExceptionHandler(void (*handler)(std::exception&)){
		exceptionHandler = handler;
	}
};

}

#endif /* THREAD_H_ */
