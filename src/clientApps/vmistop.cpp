/*
 * vmistop.cpp
 *
 *  Created on: Jun 28, 2010
 *      Author: kittel
 */

#include "VmiIDSrpc.h"

int
main (int argc, char *argv[])
{
	VmiIDSrpc::getInstance()->stopIDS();
}
