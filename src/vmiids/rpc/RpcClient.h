/*
 * VmiIDS_rpcClient.h
 *
 *  Created on: Jul 8, 2010
 *      Author: kittel
 */

#ifndef VMIIDSRPCCLIENT_H_
#define VMIIDSRPCCLIENT_H_

#include "vmiids/rpc/RpcCommon.h"

#include <string>
#include <list>

namespace vmi {

/**
 * @class RpcClient RpcClient.h "vmiids/rpc/RpcClient.h"
 *
 * This class provides rpc client functionality.
 *
 * Every function is mapped to the appropriate rpc request.
 * Currently this function only supports queries on localhost.
 */
class RpcClient {
private:
	CLIENT *clnt; //!< RPC internal data structure.

	static RpcClient *instance; //!< Instance of the RpcClient class (Singleton)

	/**
	 * Internal function to start the rpc connection.
	 */
	void startConnection(void);

	/**
	 * Internal function to quit the rpc connection.
	 */
	void stopConnection(void);

	/**
	 * Constructor
	 */
	RpcClient();

public:
	/**
	 * Destructor
	 */
	virtual ~RpcClient();

	/**
	 * Get the RpcClient instance.
	 */
	static RpcClient *getInstance();

	/**
	 * Enqueue DetectionModule to a list of DetectionModules scheduled all timeInSeconds seconds.
	 *
	 * Function calls vmi::VmiIDS::enqueueDetectionModule().
	 * Note: The DetectionModule must be loaded in advance. Use the loadSharedObject() method to load a module.
	 *
	 * @param detectionModuleName Name of the DetectionModule.
	 * @param timeInSeconds Time between two runs of the module.
	 * @return True, if the DetectionModule was successfully enqueued.
	 */
	bool enqueueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds = 0);

	/**
	 * Dequeue DetectionModule from a list of DetectionModules scheduled all timeInSeconds seconds.
	 *
	 * Function calls vmi::VmiIDS::dequeueDetectionModule().
	 * Note: The DetectionModule must be enqueued in advance.
	 *
	 * @param detectionModuleName Name of the DetectionModule.
	 * @param timeInSeconds Time between two runs of the module.
	 * @return True, if the DetectionModule was successfully dequeued.
	 */
	bool dequeueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds = 0);

	/**
	 * Run single DetectionModule.
	 *
	 * @param module Name of the DetectionModule to run.
	 * @return Output the DetectionModule produced while running.
	 */
	std::string runSingleDetectionModule(std::string module);

	/**
	 * Stop the entire framework. It is not able to restart the framework with rpc.
	 * @param signum Signal to stop the framework with.
	 * @return True, if framework was stopped.
	 */
	bool stopIDS(int signum = 0);

	/**
	 * Load a module from an object file (*.so).
	 * @param path Path of the module to load.
	 * @return True, if the object file was found, and loadable.
	 */
	bool loadSharedObject(std::string path);

	/**
	 * Query a list of loaded DetectionModules.
	 * @return List of loaded DetectionModules.
	 */
	std::list<std::string> getListOfDetectionModules(void);
};

}

#endif /* VMIIDSRPCCLIENT_H_ */
