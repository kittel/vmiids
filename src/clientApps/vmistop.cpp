/*
 * vmistop.cpp
 *
 *  Created on: Jun 28, 2010
 *      Author: kittel
 */

#include "vmiids/rpc/RpcClient.h"

int
main ()
{
	vmi::RpcClient::getInstance()->stopIDS();
}
