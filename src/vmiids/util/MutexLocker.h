/*
 * MutexLocker.h
 *
 *  Created on: Aug 25, 2010
 *      Author: tom
 */

#ifndef MUTEXLOCKER_H_
#define MUTEXLOCKER_H_

#include <pthread.h>
#include "Mutex.h"

namespace vmi {

/**
 * @class MutexLocker MutexLocker.h "vmiids/util/MutexLocker.h"
 * @brief MutexLocker class.
 * @sa Mutex
 *
 * Convenience class for pthread mutex. Equivalent to QTs QMutexLocker.
 * When using the mutex lock directly, a developer has to unlock a mutex before he exits the function.
 * MutexLocker locks the mutex, when the constructor is run.
 * The mutex is automatically released when the MutexLocker instance is destroyed.
 * A developer hence must not care about releasing a mutex.
 *
 * The MutexLocker can operate both on an vmi::Mutex and an original pthread mutex.
 */
class MutexLocker {
private:
	pthread_mutex_t *__pthread_mutex;  //!< Pointer to Pthread mutex.
	vmi::Mutex * __vmi_mutex;          //!< Pointer to vmi::Mutex.

public:
	/**
	 * Constructor using a pthread mutex. Mutex is locked in constructor.
	 * @param mutex Pthread Mutex to lock
	 */
	MutexLocker(pthread_mutex_t *mutex){
		__pthread_mutex = mutex;
		__vmi_mutex = NULL;
		pthread_mutex_lock(__pthread_mutex);
	}
	/**
	 * Constructor using a vmi::Mutex. Mutex is locked in constructor.
	 * @param mutex vmi::Mutex to lock
	 */
	MutexLocker(vmi::Mutex *mutex){
		__pthread_mutex = NULL;
		__vmi_mutex = mutex;
		__vmi_mutex->lock();
	}
	/**
	 * Destructor. Auto releases the lock.
	 */
	virtual ~MutexLocker(){
		if(__pthread_mutex != NULL) pthread_mutex_unlock(__pthread_mutex);
		else __vmi_mutex->unlock();
	}
};

}

#endif /* MUTEXLOCKER_H_ */
