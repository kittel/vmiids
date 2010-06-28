/*
 * VmiIDS.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef VMIIDS_H_
#define VMIIDS_H_

#include "DetectionModule.h"
#include "NotificationModule.h"
#include "SensorModule.h"

#include <list>
#include <string>

class VmiIDS {
	private:
		std::list<DetectionModule *> detectionModules;
		pthread_mutex_t detectionModuleMutex;
		std::list<NotificationModule *> notificationModules;
		pthread_mutex_t notificationModuleMutex;
		std::list<SensorModule* > sensorModules;
		pthread_mutex_t sensorModuleMutex;

		static VmiIDS *instance;
		pthread_t rpcThread, vmiidsThread;

		bool vmiRunning;

		VmiIDS();

	public:
		virtual ~VmiIDS();

		static VmiIDS *getInstance();
		int startIDS();
		void waitIDS();
		void stopIDS(int signum = 0);

		static void * run(void * this_pointer);

		void enqueueDetectionModule(DetectionModule *detectionModule);
		bool enqueueDetectionModule(std::string detectionModuleName);
		bool dequeueDetectionModule(std::string detectionModuleName);


		void enqueueNotificationModule(NotificationModule *notificationModule);
		bool enqueueNotificationModule(std::string notificationModule);
		bool dequeueNotificationModule(std::string notificationModule);

		void enqueueSensorModule(SensorModule *sensorModule);

		NotificationModule *getNotificationModule();
		SensorModule *getSensorModule();

		void collectThreadLevel();

};

#endif /* VMIIDS_H_ */
