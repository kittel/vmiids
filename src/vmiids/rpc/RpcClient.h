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

class RpcClient {
private:
	CLIENT *clnt;

	static RpcClient *instance;

	void startConnection(void);
	void stopConnection(void);

public:
	RpcClient();
	virtual ~RpcClient();

	static RpcClient *getInstance();

	bool enqueueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds = 0);
	bool dequeueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds = 0);
	std::string runSingleDetectionModule(std::string module);
	bool stopIDS(int signum = 0);
	bool loadSharedObject(std::string path);
	std::list<std::string> getListOfDetectionModules(void);
};

}

#endif /* VMIIDSRPCCLIENT_H_ */
