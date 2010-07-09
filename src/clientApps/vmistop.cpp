/*
 * vmistop.cpp
 *
 *  Created on: Jun 28, 2010
 *      Author: kittel
 */

#include "VmiIDSrpc.h"

int
main ()
{
	VmiIDSrpc::getInstance()->stopIDS();
}
