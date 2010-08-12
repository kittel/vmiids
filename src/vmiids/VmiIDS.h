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

namespace vmi {

class VmiIDS : public Module{
	private:
		std::map<std::string, vmi::DetectionModule *> detectionModules;
		pthread_mutex_t detectionModuleMutex;
		std::map<std::string, vmi::DetectionModule *> activeDetectionModules;
		pthread_mutex_t activeDetectionModuleMutex;
		std::map<std::string, vmi::NotificationModule *> notificationModules;
		pthread_mutex_t notificationModuleMutex;
		std::map<std::string, vmi::SensorModule* > sensorModules;
		pthread_mutex_t sensorModuleMutex;

		static VmiIDS *instance;

		pthread_t mainThread, rpcThread, vmiidsThread;

		libconfig::Config config;

		bool vmiRunning;

		VmiIDS();
		VmiIDS(const VmiIDS&);
		VmiIDS& operator=(const VmiIDS&);

		void loadSharedObjectsPath(std::string path);

	protected:
		virtual ~VmiIDS();
		static void killInstance(void);

	public:
		static VmiIDS *getInstance();
		int startIDS();
		void waitIDS();
		bool stopIDS(int signum = 0);

		static void dispatchRPC(struct svc_req *rqstp, register SVCXPRT *transp);
		static void * run(void * this_pointer);
		static void * runDetectionModule(void* module);

		bool loadSharedObject(std::string path);

		void enqueueDetectionModule(vmi::DetectionModule *detectionModule);
		bool enqueueDetectionModule(std::string detectionModuleName);
		bool dequeueDetectionModule(std::string detectionModuleName);


		void enqueueNotificationModule(vmi::NotificationModule *notificationModule);
		bool enqueueNotificationModule(std::string notificationModuleName);
		bool dequeueNotificationModule(std::string notificationModuleName);

		void enqueueSensorModule(vmi::SensorModule *sensorModule);

		vmi::NotificationModule *getNotificationModule(std::string notificationModuleName);
		vmi::SensorModule *getSensorModule(std::string sensorModuleName);

		libconfig::Setting *getSetting(std::string settingName);

		void collectThreadLevel();

};

}

using vmi::VmiIDS;

#endif /* VMIIDS_H_ */
