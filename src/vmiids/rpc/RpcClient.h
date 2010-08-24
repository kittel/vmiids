/*
 * VmiIDS_rpcClient.h
 *
 *  Created on: Jul 8, 2010
 *      Author: kittel
 */

#ifndef VMIIDSRPCCLIENT_H_
#define VMIIDSRPCCLIENT_H_

#include "vmiids/VmiIDS.h"

#include <rpc/rpc.h>
#include <string>

namespace vmi {

class VmiIDSrpcException: public std::exception {
protected:
	std::string message;
public:
	VmiIDSrpcException(){ this->message = ""; }
	VmiIDSrpcException(std::string text){ this->message = text; }
	virtual ~VmiIDSrpcException() throw(){};
	virtual const char* what() const throw () {
		return "VmiIDSrpc abort";
	}
	virtual void printException(){ std::cerr << what() << ": " << this->message << std::endl; }
};

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

	bool enqueueDetectionModule(std::string detectionModuleName);
	bool dequeueDetectionModule(std::string detectionModuleName);
	std::string runSingleDetectionModule(std::string module);
	bool stopIDS(int signum = 0);
	bool loadSharedObject(std::string path);
};

}

#endif /* VMIIDSRPCCLIENT_H_ */
