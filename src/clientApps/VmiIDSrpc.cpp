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
	this->clnt = clnt_create (RPC_HOST, VMIIDS_RPC, VMIIDS_RPC_VERSION, "udp");
	if (this->clnt == NULL) {
		clnt_pcreateerror (RPC_HOST);
		exit (1);
	}
}

VmiIDSrpc::~VmiIDSrpc() {
	clnt_destroy (this->clnt);
}

VmiIDSrpc* VmiIDSrpc::instance = NULL;

VmiIDSrpc *VmiIDSrpc::getInstance() {
	if (!instance)
		instance = new VmiIDSrpc();
	return instance;
}



bool VmiIDSrpc::enqueueDetectionModule(std::string detectionModuleName){
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
	return result;
}

bool VmiIDSrpc::dequeueDetectionModule(std::string detectionModuleName){
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
	return result;
}

bool VmiIDSrpc::stopIDS(int signum){
	enum clnt_stat retval;
	bool_t result;

	retval = clnt_call (this->clnt, STOPIDS, (xdrproc_t) xdr_int, (caddr_t) &signum,
		(xdrproc_t) xdr_bool, (caddr_t) &result,
		TIMEOUT);
	if (retval != RPC_SUCCESS) {
		clnt_perror (this->clnt, "call failed");
	}
	return result;
}

bool VmiIDSrpc::loadSharedObject(std::string path){
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
	return result;
}
