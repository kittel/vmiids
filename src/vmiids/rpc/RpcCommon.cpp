/*
 * RpcCommon.cpp
 *
 *  Created on: Sep 24, 2010
 *      Author: kittel
 */

#include "RpcCommon.h"

bool_t
vmi::xdr_rpcArgumentStringInt (XDR *xdrs, rpcArgumentStringInt *objp)
{
	 if (!xdr_string (xdrs, &objp->string, ~0))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->integer))
		 return FALSE;
	return TRUE;
}
