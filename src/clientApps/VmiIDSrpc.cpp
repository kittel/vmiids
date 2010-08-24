/*
 * VmiIDSrpc.cpp
 *
 *  Created on: Jul 8, 2010
 *      Author: kittel
 */

#include "VmiIDSrpc.h"

#define RPC_HOST "localhost"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

VmiIDSrpc::VmiIDSrpc() {
}

VmiIDSrpc::~VmiIDSrpc() {
}

void VmiIDSrpc::startConnection(void){
	this->clnt = clnt_create (RPC_HOST, VMIIDS_RPC, VMIIDS_RPC_VERSION, "udp");
	if (this->clnt == NULL) {
		clnt_pcreateerror (RPC_HOST);
		throw VmiIDSrpcException("Could not connect to VmiIDS");
	}
}
void VmiIDSrpc::stopConnection(void){
	clnt_destroy (this->clnt);
}

VmiIDSrpc* VmiIDSrpc::instance = NULL;

VmiIDSrpc *VmiIDSrpc::getInstance() {
	if (!instance)
		instance = new VmiIDSrpc();
	return instance;
}



bool VmiIDSrpc::enqueueDetectionModule(std::string detectionModuleName){
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

bool VmiIDSrpc::dequeueDetectionModule(std::string detectionModuleName){
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

std::string VmiIDSrpc::runSingleDetectionModule(std::string module){
	this->startConnection();
	enum clnt_stat retval;
	char *result = NULL;
	//char result[1024] = {0};
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

bool VmiIDSrpc::stopIDS(int signum){
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

bool VmiIDSrpc::loadSharedObject(std::string path){
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
