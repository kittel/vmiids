/*
 * VmiIDS_rpcClient.cpp
 *
 *  Created on: Jul 8, 2010
 *      Author: kittel
 */

#include "RpcClient.h"

#define RPC_HOST "localhost"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

vmi::RpcClient::RpcClient() {
}

vmi::RpcClient::~RpcClient() {
}

void vmi::RpcClient::startConnection(void){
	this->clnt = clnt_create (RPC_HOST, VMIIDS_RPC, VMIIDS_RPC_VERSION, "udp");
	if (this->clnt == NULL) {
		clnt_pcreateerror (RPC_HOST);
		throw RpcException("Could not connect to VmiIDS");
	}
}
void vmi::RpcClient::stopConnection(void){
	clnt_destroy (this->clnt);
}

vmi::RpcClient* vmi::RpcClient::instance = NULL;

vmi::RpcClient *vmi::RpcClient::getInstance() {
	if (!instance)
		instance = new RpcClient();
	return instance;
}

bool vmi::RpcClient::enqueueDetectionModule(std::string detectionModuleName){
	this->startConnection();
	enum clnt_stat retval;
	bool_t result;
	const char * arg = detectionModuleName.c_str();

	retval = clnt_call(this->clnt, ENQUEUEDETECTIONMODULE,
		(xdrproc_t) xdr_wrapstring, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) &result,
		TIMEOUT);
	if (retval != RPC_SUCCESS) {
		clnt_perror (this->clnt, "call failed");
	}
	this->stopConnection();
	return result;
}

bool vmi::RpcClient::dequeueDetectionModule(std::string detectionModuleName){
	this->startConnection();
	enum clnt_stat retval;
	bool_t result;
	const char * arg = detectionModuleName.c_str();

	retval = clnt_call(this->clnt, DEQUEUEDETECTIONMODULE,
		(xdrproc_t) xdr_wrapstring, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) &result,
		TIMEOUT);
	if (retval != RPC_SUCCESS) {
		clnt_perror (this->clnt, "call failed");
	}
	this->stopConnection();
	return result;
}

std::string vmi::RpcClient::runSingleDetectionModule(std::string module){
	this->startConnection();
	enum clnt_stat retval;
	char *result = NULL;
	const char * arg = module.c_str();

	retval = clnt_call(this->clnt, RUNDETECTIONMODULE,
		(xdrproc_t) xdr_wrapstring, (caddr_t) &arg,
		(xdrproc_t) xdr_wrapstring, (caddr_t) &result,
		TIMEOUT);
	if (retval != RPC_SUCCESS) {
		clnt_perror (this->clnt, "call failed");
	}
	std::string resultString(result);
	this->stopConnection();
	return resultString;
}

bool vmi::RpcClient::stopIDS(int signum){
	this->startConnection();
	enum clnt_stat retval;
	bool_t result;

	retval = clnt_call (this->clnt, STOPIDS, (xdrproc_t) xdr_int, (caddr_t) &signum,
		(xdrproc_t) xdr_bool, (caddr_t) &result,
		TIMEOUT);
	if (retval != RPC_SUCCESS) {
		clnt_perror (this->clnt, "call failed");
	}
	this->stopConnection();
	return result;
}

bool vmi::RpcClient::loadSharedObject(std::string path){
	this->startConnection();
	enum clnt_stat retval;
	bool_t result;
	const char * arg = path.c_str();

	retval = clnt_call(this->clnt, LOADSHAREDOBJECT,
		(xdrproc_t) xdr_wrapstring, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) &result,
		TIMEOUT);
	if (retval != RPC_SUCCESS) {
		clnt_perror (this->clnt, "call failed");
	}
	this->stopConnection();
	return result;
}
