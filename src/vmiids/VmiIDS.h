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

#include "DetectionModule.h"
#include "SensorModule.h"

namespace vmi {

class VmiIDS : public Module, protected OutputModule{
	private:
		std::map<std::string, vmi::DetectionModule *> detectionModules;
		pthread_mutex_t detectionModuleMutex;
		std::map<std::string, vmi::DetectionModule *> activeDetectionModules;
		pthread_mutex_t activeDetectionModuleMutex;
		std::map<std::string, vmi::SensorModule* > sensorModules;
		pthread_mutex_t sensorModuleMutex;

		static VmiIDS *instance;
		RpcServer rpcServer;

		static pthread_t mainThread, vmiidsThread;

		libconfig::Config config;

		static bool vmiRunning;

		VmiIDS();
		VmiIDS(const VmiIDS&);
		VmiIDS& operator=(const VmiIDS&);

		void loadSharedObjectsPath(std::string path);

	protected:
		virtual ~VmiIDS();

	public:
		static VmiIDS *getInstance();
		int startIDS();
		void waitIDS();
		static bool stopIDS(int signum = 0);

		static void * run(void * this_pointer);
		static void * runDetectionModule(void* module);

		bool loadSharedObject(std::string path);

		void enqueueModule(vmi::DetectionModule *detectionModule);
		void enqueueModule(vmi::SensorModule *sensorModule);

		bool enqueueDetectionModule(std::string detectionModuleName);
		bool dequeueDetectionModule(std::string detectionModuleName);

		std::string runSingleDetectionModule(std::string detectionModuleName);

		vmi::SensorModule *getSensorModule(std::string sensorModuleName);

		libconfig::Setting *getSetting(std::string settingName);

		void collectThreadLevel();

};

}

using vmi::VmiIDS;

#endif /* VMIIDS_H_ */
