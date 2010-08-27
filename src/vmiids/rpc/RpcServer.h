/*
 * RpcServer.h
 *
 *  Created on: Aug 24, 2010
 *      Author: kittel
 */

#ifndef RCPSERVER_H_
#define RCPSERVER_H_

#include "vmiids/util/Thread.h"

#include "vmiids/rpc/RpcCommon.h"

namespace vmi{

class RpcServer{
private:
	static RpcServer* this_p;
	pthread_t rpcThread;

	void run(void);
	static void* __runThread(void* ptr);

	std::string runDetectionModule(std::string detectionModuleName);
	static void * stopIDSThreadFunction(void * nothing);
	static void dispatchRPC(struct svc_req *rqstp, register SVCXPRT *transp);

public:
	RpcServer();
	virtual ~RpcServer();
};

};

#endif /* RCPSERVER_H_ */
