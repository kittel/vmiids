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
	if (argc < 2) {
		printf ("usage: %s [a|d|l] <Module>\n", argv[0]);
		exit (1);
	}
	char *module = argv[2];

	if( argv[1][0] == 'a'){
		printf("Adding module %s\n", module);
		VmiIDSrpc::getInstance()->enqueueDetectionModule(module);
	} else if(argv[1][0] == 'd'){
		printf("Deleting module %s\n", module);
		VmiIDSrpc::getInstance()->dequeueDetectionModule(module);
	} else if(argv[1][0] == 'l'){
		printf("Loading shared object %s\n", module);
		if(VmiIDSrpc::getInstance()->loadSharedObject(module)){
			printf("Loading shared object successful\n");
		}else {
			printf("Loading shared object failed\n");
		}
	} else printf("Unknown task\n");
}
