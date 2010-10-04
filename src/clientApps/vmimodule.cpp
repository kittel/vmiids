/*
 * vmistop.cpp
 *
 *  Created on: Jun 28, 2010
 *      Author: kittel
 */

#include "vmiids/rpc/RpcClient.h"
#include <iostream>

int
main (int argc, char *argv[])
{
	if (argc < 2) {
		printf ("usage: %s [a|d|l|s] <Module>\n", argv[0]);
		exit (1);
	}
	char *module = argv[2];

	if( argv[1][0] == 'a'){
		printf("Adding module %s\n", module);
		vmi::RpcClient::getInstance()->enqueueDetectionModule(module);
	} else if(argv[1][0] == 'd'){
		printf("Deleting module %s\n", module);
		vmi::RpcClient::getInstance()->dequeueDetectionModule(module);
	} else if(argv[1][0] == 'r'){
		printf("Run module %s\n", module);
		std::cout << vmi::RpcClient::getInstance()->runSingleDetectionModule(module);
	} else if(argv[1][0] == 'l'){
		printf("Loading shared object %s\n", module);
		if(vmi::RpcClient::getInstance()->loadSharedObject(module)){
			printf("Loading shared object successful\n");
		}else {
			printf("Loading shared object failed\n");
		}
	} else if(argv[1][0] == 's'){
		printf("Get List of DetectionModules\n");
		std::list<std::string> detectionModules =
				vmi::RpcClient::getInstance()->getListOfDetectionModules();
		while(!detectionModules.empty()){
			std::cout << detectionModules.front();
			detectionModules.pop_front();
		}
		printf("Done\n");
	} else printf("Unknown task\n");

	return 0;
}
