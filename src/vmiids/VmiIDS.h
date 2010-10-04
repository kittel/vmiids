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
#include <set>

#include "vmiids/rpc/RpcServer.h"
#include "vmiids/util/Thread.h"
#include "vmiids/util/Mutex.h"

#include "DetectionThread.h"
#include "DetectionModule.h"
#include "SensorModule.h"

namespace vmi {

class VmiIDS : public Module, protected OutputModule, public Thread{
	private:
		std::map<int, DetectionThread*> runModules;

		static VmiIDS *instance;
		RpcServer rpcServer;

		bool vmiRunning;

		VmiIDS();
		VmiIDS(const VmiIDS&);
		VmiIDS& operator=(const VmiIDS&);

		void initVmiIDS();
		void loadModules();

		void loadSharedObjectsPath(std::string path);

	protected:
		virtual ~VmiIDS();

	public:
		static VmiIDS *getInstance();
		static void defaultExceptionHandler(std::exception& e);

		static bool stopIDS(int signum = 0);

		virtual void run(void);

		bool loadSharedObject(std::string path);

		bool enqueueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds = 0);
		bool dequeueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds = 0);

		void collectThreadLevel();
};

}

using vmi::VmiIDS;

#endif /* VMIIDS_H_ */
