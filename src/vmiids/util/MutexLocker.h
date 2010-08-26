/*
 * MutexLocker.h
 *
 *  Created on: Aug 25, 2010
 *      Author: tom
 */

#ifndef MUTEXLOCKER_H_
#define MUTEXLOCKER_H_

#include <pthread.h>

class MutexLocker {
private:
	pthread_mutex_t *__mutex;

public:
	MutexLocker(pthread_mutex_t *mutex){
		__mutex == mutex;
		pthread_mutex_lock(__mutex);
	}
	virtual ~MutexLocker(){
		pthread_mutex_unlock(__mutex);;
	}
};

#endif /* MUTEXLOCKER_H_ */
