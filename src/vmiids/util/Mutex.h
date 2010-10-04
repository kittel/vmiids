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
/**
 * @class Mutex Mutex.h "vmiids/util/Mutex.h"
 * @brief Mutex class.
 * @sa MutexLocker
 *
 * Convenience class for pthread mutex.
 */
class Mutex {
private:
	pthread_mutex_t __mutex;  //!< Pthread mutex to operate on.

public:
	/**
	 * Constructor. Initialize mutex.
	 */
	Mutex(){
		pthread_mutex_init(&__mutex, NULL);
	}
	/**
	 * Destructor. Destroy mutex.
	 */
	virtual ~Mutex(){
		pthread_mutex_destroy(&__mutex);;
	}
	/**
	 * Lock mutex.
	 */
	void lock(void){
		pthread_mutex_lock(&__mutex);
	}
	/**
	 * Unlock mutex.
	 */
	void unlock(void){
		pthread_mutex_unlock(&__mutex);
	}
};

}

#endif /* MUTEX_H_ */
