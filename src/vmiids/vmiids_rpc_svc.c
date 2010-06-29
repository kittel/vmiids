/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "vmiids_rpc.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

int
_enqueuedetectionmodule_1 (char * *argp, void *result, struct svc_req *rqstp)
{
	return (enqueuedetectionmodule_1_svc(*argp, result, rqstp));
}

int
_dequeuedetectionmodule_1 (char * *argp, void *result, struct svc_req *rqstp)
{
	return (dequeuedetectionmodule_1_svc(*argp, result, rqstp));
}

int
_enqueuenotificationmodule_1 (char * *argp, void *result, struct svc_req *rqstp)
{
	return (enqueuenotificationmodule_1_svc(*argp, result, rqstp));
}

int
_dequeuenotificationmodule_1 (char * *argp, void *result, struct svc_req *rqstp)
{
	return (dequeuenotificationmodule_1_svc(*argp, result, rqstp));
}

int
_stopids_1 (void  *argp, void *result, struct svc_req *rqstp)
{
	return (stopids_1_svc(result, rqstp));
}

int
_loadsharedobject_1 (char * *argp, void *result, struct svc_req *rqstp)
{
	return (loadsharedobject_1_svc(*argp, result, rqstp));
}

static void
simp_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		char *enqueuedetectionmodule_1_arg;
		char *dequeuedetectionmodule_1_arg;
		char *enqueuenotificationmodule_1_arg;
		char *dequeuenotificationmodule_1_arg;
		char *loadsharedobject_1_arg;
	} argument;
	union {
		int enqueuedetectionmodule_1_res;
		int dequeuedetectionmodule_1_res;
		int enqueuenotificationmodule_1_res;
		int dequeuenotificationmodule_1_res;
		int stopids_1_res;
		int loadsharedobject_1_res;
	} result;
	bool_t retval;
	xdrproc_t _xdr_argument, _xdr_result;
	bool_t (*local)(char *, void *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case ENQUEUEDETECTIONMODULE:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_enqueuedetectionmodule_1;
		break;

	case DEQUEUEDETECTIONMODULE:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_dequeuedetectionmodule_1;
		break;

	case ENQUEUENOTIFICATIONMODULE:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_enqueuenotificationmodule_1;
		break;

	case DEQUEUENOTIFICATIONMODULE:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_dequeuenotificationmodule_1;
		break;

	case STOPIDS:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_stopids_1;
		break;

	case LOADSHAREDOBJECT:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (bool_t (*) (char *, void *,  struct svc_req *))_loadsharedobject_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	retval = (bool_t) (*local)((char *)&argument, (void *)&result, rqstp);
	if (retval > 0 && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)&result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	if (!simp_prog_1_freeresult (transp, _xdr_result, (caddr_t) &result))
		fprintf (stderr, "%s", "unable to free results");

	return;
}

void rpc_main (void)
{
	register SVCXPRT *transp;

	pmap_unset (SIMP_PROG, SIMP_VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, SIMP_PROG, SIMP_VERSION, simp_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (SIMP_PROG, SIMP_VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, SIMP_PROG, SIMP_VERSION, simp_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (SIMP_PROG, SIMP_VERSION, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
