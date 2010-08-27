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

class Thread {
private:
	pthread_t __thisThread;
	pthread_mutex_t __threadMutex;

	static void (*defaultExceptionHandler)(std::exception&);
	void (*exceptionHandler)(std::exception&);

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
	Thread(){
		exceptionHandler = NULL;
		pthread_mutex_init(&__threadMutex, NULL);
	}
	virtual ~Thread(){
		pthread_mutex_lock(&__threadMutex);
		pthread_mutex_unlock(&__threadMutex);
		pthread_mutex_destroy(&__threadMutex);
	}

	void join(){
		pthread_join(__thisThread, NULL);
	}
	void stop(){
		pthread_cancel(__thisThread);
	}

	virtual void run(void) = 0;

	void start(void){
		pthread_create(&__thisThread, NULL, Thread::__runThread,
					(void*) this);
	}

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

	static void setDefaultUncaughtExceptionHandler(void (*handler)(std::exception&)){
		defaultExceptionHandler = handler;
	}

	void setUncaughtExceptionHandler(void (*handler)(std::exception&)){
		exceptionHandler = handler;
	}
};

}

#endif /* THREAD_H_ */
