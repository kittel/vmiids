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

/**
 * Data structure to send a string and an integer over rpc.
 */
typedef struct {
	char *string;
	int   integer;
} rpcArgumentStringInt;

/**
 * Function to check whether the rpcArgumentStringInt data structure contains valid content.
 *
 * @param xdrs RPC internal data structure
 * @param objp rpcArgumentStringInt data structure.
 * @return True, if the struct contains valid input.
 */
bool_t xdr_rpcArgumentStringInt (XDR *xdrs, rpcArgumentStringInt *objp);

/**
 * Enum defining the function called over the rpc connection.
 */
typedef enum {
	ENQUEUEDETECTIONMODULE = 1,
	DEQUEUEDETECTIONMODULE,
	RUNDETECTIONMODULE,
	STOPIDS,
	LOADSHAREDOBJECT,
	GETDETECTIONMODULELIST,
} eRPCFuncs;

/**
 * RPC Identifier.
 */
#define VMIIDS_RPC 			555555555

/**
 * RPC API Version.
 */
#define VMIIDS_RPC_VERSION 	1

/**
 * @class RpcException RpcCommon.h "vmiids/rpc/RpcCommon.h"
 *
 * This class is the frameworks basic rpc exception class.
 *
 * Inherited from std::exception to provide stdlib compatibility.
 * It is not inherited from the vmi::Exception class, as rpc client
 * applications are not part of the VmiIDS framework.
 *
 */
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
