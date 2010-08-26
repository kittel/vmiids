/*
 * Mutex.h
 *
 *  Created on: Aug 26, 2010
 *      Author: kittel
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

namespace vmi {

class Mutex {
private:
	pthread_mutex_t __mutex;

public:
	Mutex(){
		pthread_mutex_init(&__mutex, NULL);
	}
	virtual ~Mutex(){
		pthread_mutex_destroy(&__mutex);;
	}
	void lock(void){
		pthread_mutex_lock(&__mutex);
	}
	void unlock(void){
		pthread_mutex_unlock(&__mutex);
	}
};

}

#endif /* MUTEX_H_ */
