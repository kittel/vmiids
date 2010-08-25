/*
 * VmiIDS.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef VMIIDS_H_
#define VMIIDS_H_

#include <map>
#include <string>
#include <libconfig.h++>
#include "vmiids/rpc/RpcServer.h"
#include "vmiids/util/Thread.h"

#include "DetectionModule.h"
#include "SensorModule.h"

namespace vmi {

class VmiIDS : public Module, protected OutputModule, public Thread{
	private:
		std::map<std::string, vmi::DetectionModule *> detectionModules;
		pthread_mutex_t detectionModuleMutex;
		std::map<std::string, vmi::SensorModule* > sensorModules;
		pthread_mutex_t sensorModuleMutex;

		static VmiIDS *instance;
		RpcServer rpcServer;

		libconfig::Config config;

		bool vmiRunning;

		VmiIDS();
		VmiIDS(const VmiIDS&);
		VmiIDS& operator=(const VmiIDS&);

		void loadSharedObjectsPath(std::string path);

	protected:
		virtual ~VmiIDS();

	public:
		static VmiIDS *getInstance();
		static void defaultExceptionHandler(std::exception& e);

		static bool stopIDS(int signum = 0);

		virtual void run(void);

		bool loadSharedObject(std::string path);

		void enqueueModule(vmi::DetectionModule *detectionModule);
		void enqueueModule(vmi::SensorModule *sensorModule);

		bool enqueueDetectionModule(std::string detectionModuleName);
		bool dequeueDetectionModule(std::string detectionModuleName);

		vmi::DetectionModule *getDetectionModule(std::string detectionModuleName);
		vmi::SensorModule *getSensorModule(std::string sensorModuleName);

		libconfig::Setting *getSetting(std::string settingName);

		void collectThreadLevel();
};

}

using vmi::VmiIDS;

#endif /* VMIIDS_H_ */
