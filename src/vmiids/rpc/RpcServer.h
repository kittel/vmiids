/*
 * RpcServer.h
 *
 *  Created on: Aug 24, 2010
 *      Author: kittel
 */

#ifndef RCPSERVER_H_
#define RCPSERVER_H_

#include <pthread.h>

#include "vmiids/rpc/RpcCommon.h"

namespace vmi{

class RpcServer {
private:
	pthread_t rpcThread;

	static void * rpcThreadFunction(void * argument);
	static void * stopIDSThreadFunction(void * nothing);
	static void dispatchRPC(struct svc_req *rqstp, register SVCXPRT *transp);

public:
	RpcServer();
	virtual ~RpcServer();
};

};

#endif /* RCPSERVER_H_ */
