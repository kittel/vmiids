/*
 * vmistop.cpp
 *
 *  Created on: Jun 28, 2010
 *      Author: kittel
 */

#include "vmiids_rpc.h"

int
main (int argc, char *argv[])
{
	const char *host;
	char *module = argv[2];

	if (argc < 3) {
		printf ("usage: %s server_host [a|d] <Module>\n", argv[0]);
		exit (1);
	}
	host = "localhost"; //argv[1];
	CLIENT *clnt;
	enum clnt_stat retval;
	int result;

	clnt = clnt_create (host, SIMP_PROG, SIMP_VERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	if( argv[1][0] == 'a'){
		printf("Adding module %s\n", module);
		retval = enqueuedetectionmodule_1(module, &result, clnt);
	} else if(argv[1][0] == 'd'){
		printf("Deleting module %s\n", module);
		retval = dequeuedetectionmodule_1(module, &result, clnt);
	} else printf("Unknown task\n");

	if (retval != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}

	clnt_destroy (clnt);
exit (0);
}
