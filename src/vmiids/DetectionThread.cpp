/*
 * DetectionThread.cpp
 *
 *  Created on: Aug 25, 2010
 *      Author: tom
 */

#include "DetectionThread.h"

#include "vmiids/VmiIDS.h"

namespace vmi {

DetectionThread::DetectionThread(time_t seconds)
		: m_seconds(seconds){
	pthread_mutex_init(&threadMutex, NULL);
	this->threadActive = true;
}

DetectionThread::DetectionThread(time_t seconds, std::set<std::string> detectionModules)
		: m_seconds(seconds), m_detectionModules(detectionModules){
	pthread_mutex_init(&threadMutex, NULL);
	this->threadActive = true;
}

DetectionThread::~DetectionThread() {
	this->threadActive = false;
	this->join();
	pthread_mutex_lock(&threadMutex);
	pthread_mutex_unlock(&threadMutex);
	pthread_mutex_destroy(&threadMutex);
}

bool DetectionThread::enqueueModule(std::string moduleName){
	pthread_mutex_lock(&threadMutex);
	this->m_detectionModules.insert(moduleName);
	pthread_mutex_unlock(&threadMutex);
	return true;
}

bool DetectionThread::dequeueModule(std::string moduleName){
	pthread_mutex_lock(&threadMutex);
	this->m_detectionModules.erase(moduleName);
	pthread_mutex_unlock(&threadMutex);
	return true;
}

void DetectionThread::run(){

	this->lastRun = time (NULL);

	std::set<std::string> detectionModules;

	while (this->threadActive) {

		pthread_mutex_lock(&threadMutex);
		detectionModules = this->m_detectionModules;
		pthread_mutex_unlock(&threadMutex);

		DetectionModule * module;

		for ( std::set<std::string>::iterator it=detectionModules.begin() ;
				it != detectionModules.end(); it++ ){
		    if(!this->threadActive){
		    	return;
		    }
		    module = VmiIDS::getInstance()->getDetectionModule(*it);
		    if(module == NULL){
				pthread_mutex_lock(&threadMutex);
				this->m_detectionModules.erase(*it);
				pthread_mutex_unlock(&threadMutex);
		    }else{
		    	module->start();
		    	module->join();
		    }
		}
		if(time(NULL) > this->lastRun + m_seconds){
			std::cout << "Execution took longer than estimated" << std::endl;
			this->lastRun = time (NULL);
			continue;
		}
	    while(time(NULL) < this->lastRun + m_seconds){
			if (!this->threadActive) {
				return;
			}
			this->sleep(1000);
	    }
		this->lastRun += m_seconds;
	}
	return;
}

void DetectionThread::stopThread(){
	this->threadActive = false;
}

}
