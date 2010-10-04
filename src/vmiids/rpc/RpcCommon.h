/*
 * RpcCommon.h
 *
 *  Created on: Aug 24, 2010
 *      Author: kittel
 */

#ifndef RPCCOMMON_H_
#define RPCCOMMON_H_

#include <rpc/rpc.h>
#include <iostream>

namespace vmi {

typedef struct {
	char *string;
	int   integer;
} rpcArgumentStringInt;

bool_t xdr_rpcArgumentStringInt (XDR *xdrs, rpcArgumentStringInt *objp);

typedef enum {
	ENQUEUEDETECTIONMODULE = 1,
	DEQUEUEDETECTIONMODULE,
	RUNDETECTIONMODULE,
	STOPIDS,
	LOADSHAREDOBJECT,
	GETDETECTIONMODULELIST,
} eRPCFuncs;

#define VMIIDS_RPC 			555555555
#define VMIIDS_RPC_VERSION 	1

class RpcException: public std::exception {
protected:
	std::string message;
public:
	RpcException(){ this->message = ""; }
	RpcException(std::string text){ this->message = text; }
	virtual ~RpcException() throw(){};
	virtual const char* what() const throw () {
		return "VmiIDSrpc abort";
	}
	virtual void printException(){ std::cerr << what() << ": " << this->message << std::endl; }
};

};

#endif /* RPCCOMMON_H_ */
