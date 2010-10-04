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

/**
 * @class RpcServer RpcServer.h "vmiids/rpc/RpcServer.h"
 *
 * This class provides rpc server functionality.
 *
 * It is a independent thread handling all rpc requests.
 *
 * Requests are processed in the dispatchRPC() function.
 */
class RpcServer{
private:
	static RpcServer* this_p; //!< Instance of the rpc server class (Singleton)
	pthread_t rpcThread;      //!< Mutex to exeute one request at a time.

	void run(void);   //!< This function containes the main function created by the "rpcgen" tool.
	static void* __runThread(void* ptr);  //!< This function starts the thread (as pthread threads need a C function to start)

	/**
	 * Execute a DetectionModule once and return its output.
	 *
	 * @param detectionModuleName Name of the DetectionModule to execute.
	 * @return Output of the DetectionModule run.
	 */
	std::string runDetectionModule(std::string detectionModuleName);
	/**
	 * Stop the framework.

	 * @param nothing Unused parameter.
	 */
	static void * stopIDSThreadFunction(void * nothing);

	/**
	 * Dispatch rpc requests to appropriate functions within the VmiIDS framework.
	 *
	 * @param rqstp rpc internal data.
	 * @param transp rpc internal data.
	 */
	static void dispatchRPC(struct svc_req *rqstp, register SVCXPRT *transp);

public:
	/**
	 * Constructor
	 */
	RpcServer();
	/**
	 * Destructor
	 */
	virtual ~RpcServer();
};

};

#endif /* RCPSERVER_H_ */
