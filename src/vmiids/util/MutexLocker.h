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

class MutexLocker {
private:
	pthread_mutex_t *__pthread_mutex;
	vmi::Mutex * __vmi_mutex;

public:
	MutexLocker(pthread_mutex_t *mutex){
		__pthread_mutex = mutex;
		__vmi_mutex = NULL;
		pthread_mutex_lock(__pthread_mutex);
	}
	MutexLocker(vmi::Mutex *mutex){
		__pthread_mutex = NULL;
		__vmi_mutex = mutex;
		__vmi_mutex->lock();
	}
	virtual ~MutexLocker(){
		if(__pthread_mutex != NULL) pthread_mutex_unlock(__pthread_mutex);
		else __vmi_mutex->unlock();
	}
};

}

#endif /* MUTEXLOCKER_H_ */
