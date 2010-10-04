/*
 * DetectionThread.h
 *
 *  Created on: Aug 25, 2010
 *      Author: tom
 */

#ifndef DETECTIONTHREAD_H_
#define DETECTIONTHREAD_H_

#include "vmiids/util/Thread.h"

#include <set>
#include <string>

namespace vmi {

class DetectionThread : public Thread{
private:
	pthread_mutex_t threadMutex;
	bool threadActive;

	time_t m_seconds;
	std::set<std::string> m_detectionModules;

	time_t lastRun;

public:
	DetectionThread(time_t seconds);
	DetectionThread(time_t seconds, std::set<std::string> detectionModules);
	virtual ~DetectionThread();

	bool enqueueModule(std::string moduleName);
	bool dequeueModule(std::string moduleName);

	size_t getModuleCount();

	virtual void run();

	void stopThread();
};

}

#endif /* DETECTIONTHREAD_H_ */
