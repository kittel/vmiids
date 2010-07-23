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

#include <map>
#include <string>
#include <rpc/rpc.h>
#include <libconfig.h++>

typedef enum {
	ENQUEUEDETECTIONMODULE = 1,
	DEQUEUEDETECTIONMODULE,
	ENQUEUENOTIFICATIONMODULE,
	DEQUEUENOTIFICATIONMODULE,
	STOPIDS,
	LOADSHAREDOBJECT,
} eRPCFuncs;

#define VMIIDS_RPC 			555555555
#define VMIIDS_RPC_VERSION 	1


#define CONCAT(a, b) a ## b

class VmiIDS {
	private:

		std::map<std::string, DetectionModule *> detectionModules;
		pthread_mutex_t detectionModuleMutex;
		std::map<std::string, DetectionModule *> activeDetectionModules;
		pthread_mutex_t activeDetectionModuleMutex;
		std::map<std::string, NotificationModule *> notificationModules;
		pthread_mutex_t notificationModuleMutex;
		std::map<std::string, SensorModule* > sensorModules;
		pthread_mutex_t sensorModuleMutex;

		static VmiIDS *instance;
		pthread_t rpcThread, vmiidsThread;

		libconfig::Config config;

		bool vmiRunning;

		VmiIDS();

		void loadSharedObjectsPath(std::string path);

	public:
		virtual ~VmiIDS();

		static VmiIDS *getInstance();
		int startIDS();
		void waitIDS();
		bool stopIDS(int signum = 0);

		static void dispatchRPC(struct svc_req *rqstp, register SVCXPRT *transp);
		static void * run(void * this_pointer);

		bool loadSharedObject(std::string path);

		void enqueueDetectionModule(DetectionModule *detectionModule);
		bool enqueueDetectionModule(std::string detectionModuleName);
		bool dequeueDetectionModule(std::string detectionModuleName);


		void enqueueNotificationModule(NotificationModule *notificationModule);
		bool enqueueNotificationModule(std::string notificationModuleName);
		bool dequeueNotificationModule(std::string notificationModuleName);

		void enqueueSensorModule(SensorModule *sensorModule);

		NotificationModule *getNotificationModule(std::string notificationModuleName);
		SensorModule *getSensorModule(std::string sensorModuleName);

		libconfig::Setting *getSetting(std::string settingName);

		void collectThreadLevel();

};

#endif /* VMIIDS_H_ */
