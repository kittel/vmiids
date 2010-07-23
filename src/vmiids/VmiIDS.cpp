/*
 * VmiIDS.cpp
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#include "VmiIDS.h"

#include <pthread.h>
#include <signal.h>
#include <rpc/pmap_clnt.h>

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>

#include <dlfcn.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include "SimpleDetectionModule.h"

#define DEBUG

#ifdef DEBUG
#define VERBOSE "VmiIDS"
#endif /* DEBUG */
#include "../libvmi/Debug.h"

void terminate_handler(int signum) {
	VmiIDS::getInstance()->stopIDS(signum);
}

void terminate_rpcListener(int signum) {
	signum = 0;
	pthread_exit(NULL);
}

void * stopIDSThreadFunction(void * nothing) {
	nothing = NULL;
	sleep(1);
	VmiIDS::getInstance()->stopIDS(SIGTERM);
	return NULL;
}

void * rpcThreadFunction(void * argument) {
	argument = NULL;
	struct sigaction terminate_action;

	/* Set up the structure to specify the new action. */
	terminate_action.sa_handler = terminate_rpcListener;
	sigemptyset(&terminate_action.sa_mask);
	terminate_action.sa_flags = 0;

	sigaction(SIGINT, &terminate_action, NULL);
	sigaction(SIGHUP, &terminate_action, NULL);
	sigaction(SIGTERM, &terminate_action, NULL);

	register SVCXPRT *transp;

	pmap_unset (VMIIDS_RPC, VMIIDS_RPC_VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, VMIIDS_RPC, VMIIDS_RPC_VERSION, VmiIDS::dispatchRPC, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (VMIIDS_RPC_PROG, VMIIDS_RPC_VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, VMIIDS_RPC, VMIIDS_RPC_VERSION, VmiIDS::dispatchRPC, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (VMIIDS_RPC_PROG, VMIIDS_RPC_VERSION, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	/* NOTREACHED */

	pthread_exit(NULL);
}

int main() {

	struct sigaction terminate_action;

	/* Set up the structure to specify the new action. */
	terminate_action.sa_handler = terminate_handler;
	sigemptyset(&terminate_action.sa_mask);
	terminate_action.sa_flags = 0;

	sigaction(SIGINT, &terminate_action, NULL);
	sigaction(SIGHUP, &terminate_action, NULL);
	sigaction(SIGTERM, &terminate_action, NULL);

	VmiIDS::getInstance()->startIDS();

	VmiIDS::getInstance()->waitIDS();

	exit(0);
}

VmiIDS* VmiIDS::instance = NULL;

VmiIDS::VmiIDS() :
	detectionModules(), notificationModules(), sensorModules(), config() {
	this->vmiRunning = false;
	pthread_mutex_init(&detectionModuleMutex, NULL);
	pthread_mutex_init(&activeDetectionModuleMutex, NULL);
	pthread_mutex_init(&notificationModuleMutex, NULL);
	pthread_mutex_init(&sensorModuleMutex, NULL);

	FILE * configFile;

	if( ((configFile = fopen ("vmiids.cfg" , "r")) != NULL) ||
		((configFile = fopen ("/etc/vmiids.cfg" , "r")) != NULL)    ){

		try {
			config.read(configFile);
			fclose (configFile);
		}catch(libconfig::ParseException){
			printf("Could not read config file\n");
		}
	}
}

VmiIDS::~VmiIDS() {
	pthread_mutex_lock(&detectionModuleMutex);
	pthread_mutex_lock(&activeDetectionModuleMutex);
	pthread_mutex_lock(&notificationModuleMutex);
	pthread_mutex_lock(&sensorModuleMutex);

	while (!activeDetectionModules.empty()) {
		//Do not delete Module, because there is still a pointer in detectionModules map.
		activeDetectionModules.erase(activeDetectionModules.begin());
	}
	while (!detectionModules.empty()) {
		delete (detectionModules.begin()->second);
		detectionModules.erase(detectionModules.begin());
	}
	while (!notificationModules.empty()) {
		delete (notificationModules.begin()->second);
		notificationModules.erase(notificationModules.begin());
	}
	while (!sensorModules.empty()) {
		delete (sensorModules.begin()->second);
		sensorModules.erase(sensorModules.begin());
	}
}

VmiIDS *VmiIDS::getInstance() {
	if (!instance)
		instance = new VmiIDS();
	return instance;
}

int VmiIDS::startIDS() {
	if (this->vmiRunning == true) {
		printf("IDS already running");
		return 0;
	}
	printf("IDS Starting\n");
	this->vmiRunning = true;
	pthread_create(&rpcThread, NULL, rpcThreadFunction, NULL);
	pthread_create(&vmiidsThread, NULL, VmiIDS::run,
			(void*) this);
	return 0;
}

void * VmiIDS::run(void * this_pointer) {
	VmiIDS * this_p = (VmiIDS *) this_pointer;

	//
	// Load Modules by Path Name
	//
	try {
		for(int i = 0 ;  i < this_p->config.lookup("initialModuleByPath").getLength() ; i++){
			this_p->loadSharedObjectsPath(this_p->config.lookup("initialModuleByPath")[i]);
		}
	}catch(libconfig::SettingNotFoundException e){
			printf("No Modules loaded by Path ...\n");
	}

	//
	// Load Modules by So Path
	//
	try {
	for(int i = 0 ;  i < this_p->config.lookup("initialModuleBySoPath").getLength() ; i++){
			this_p->loadSharedObject(this_p->config.lookup("initialModuleBySoPath")[i]);
		}
	}catch(libconfig::SettingNotFoundException e){
		printf("No Modules loaded by So Path ...\n");
	}

	//
	// Start DetectionModules by Name
	//
	try {
	for(int i = 0 ;  i < this_p->config.lookup("startModules").getLength() ; i++){
			this_p->enqueueDetectionModule(this_p->config.lookup("startModules")[i]);
		}
	}catch(libconfig::SettingNotFoundException e){
		printf("No Modules started ...\n");
	}


	while (this_p->vmiRunning) {
		pthread_mutex_lock(&this_p->activeDetectionModuleMutex);

		for (std::map<std::string, DetectionModule*>::iterator it =
				this_p->activeDetectionModules.begin(); it
				!= this_p->activeDetectionModules.end(); ++it) {
			it->second->run();
		}
		pthread_mutex_unlock(&this_p->activeDetectionModuleMutex);
		sched_yield();
	}
	return NULL;
}

void VmiIDS::dispatchRPC(struct svc_req *rqstp, register SVCXPRT *transp){
	union {
		char *char_arg;
	} argument;
	union {
		bool_t bool_res;
	} result;
	bool_t retval;
	xdrproc_t _xdr_argument, _xdr_result;

	memset ((char *)&argument, 0, sizeof (argument));

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case ENQUEUEDETECTIONMODULE:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
			svcerr_decode (transp);
			return;
		}
		retval = 1;
		VmiIDS::getInstance()->enqueueDetectionModule(argument.char_arg);
		break;

	case DEQUEUEDETECTIONMODULE:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
			svcerr_decode (transp);
			return;
		}
		retval = 1;
		VmiIDS::getInstance()->dequeueDetectionModule(argument.char_arg);
		break;

	case ENQUEUENOTIFICATIONMODULE:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
			svcerr_decode (transp);
			return;
		}
		retval = 1;
		VmiIDS::getInstance()->enqueueNotificationModule(argument.char_arg);
		break;

	case DEQUEUENOTIFICATIONMODULE:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
			svcerr_decode (transp);
			return;
		}
		retval = 1;
		VmiIDS::getInstance()->dequeueNotificationModule(argument.char_arg);
		break;

	case STOPIDS:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_int;
		if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
			svcerr_decode (transp);
			return;
		}
		retval = 1;
		pthread_t killThread;
		pthread_create(&killThread, NULL, &stopIDSThreadFunction, NULL);
		break;

	case LOADSHAREDOBJECT:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
			svcerr_decode (transp);
			return;
		}
		retval = 1;
		VmiIDS::getInstance()->loadSharedObject(argument.char_arg);
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	if (retval > 0 && !svc_sendreply(transp, (xdrproc_t) _xdr_result, (char *)&result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	xdr_free(_xdr_result, (caddr_t) &result);
	//if (!simp_prog_1_freeresult (transp, _xdr_result, (caddr_t) &result))
	//	fprintf (stderr, "%s", "unable to free results");

	return;
}

void VmiIDS::loadSharedObjectsPath(std::string path) {

	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(path.c_str())) == NULL) {
		std::cout << "Error opening " << path << std::endl;
		return;
	}

	while ((dirp = readdir(dp)) != NULL) {
		if (strstr(dirp->d_name, ".so") != NULL) {
			std::string filename = path;
			filename.append("/");
			filename.append(dirp->d_name);
			struct stat fileStat;
			lstat(filename.c_str(), &fileStat);
			if (!S_ISLNK(fileStat.st_mode)) {
				void *dlib;
				dlib = dlopen(filename.c_str(), RTLD_NOW | RTLD_GLOBAL);
				if (dlib == NULL) {
					std::cerr << dlerror() << std::endl;
					continue;
				}
			}
		}
	}
	closedir(dp);
	return;

}

bool VmiIDS::loadSharedObject(std::string path) {
	printf("Trying to load shared object at: %s\n", path.c_str());

	void *dlib;
	dlib = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);
	if (dlib == NULL) {
		std::cerr << dlerror() << std::endl;
		return false;
	}
	return true;
}

void VmiIDS::waitIDS() {
	pthread_join(vmiidsThread, NULL);
}

bool VmiIDS::stopIDS(int signum) {
	signum = 0;
	printf("IDS Stopping\n");
	this->vmiRunning = false;
	pthread_kill(this->rpcThread, SIGTERM);
	pthread_join(this->rpcThread, NULL);
	pthread_join(this->vmiidsThread, NULL);
	return true;
}

void VmiIDS::enqueueDetectionModule(DetectionModule *detectionModule) {
	pthread_mutex_lock(&detectionModuleMutex);
	detectionModules[detectionModule->getName()] = detectionModule;
	pthread_mutex_unlock(&detectionModuleMutex);
}

bool VmiIDS::enqueueDetectionModule(std::string detectionModuleName) {
	bool success = false;
	pthread_mutex_lock(&detectionModuleMutex);
	pthread_mutex_lock(&activeDetectionModuleMutex);
	if (detectionModules[detectionModuleName] != NULL) {
		activeDetectionModules[detectionModuleName] = detectionModules[detectionModuleName];
		success = true;
	}
	pthread_mutex_unlock(&activeDetectionModuleMutex);
	pthread_mutex_unlock(&detectionModuleMutex);
	return success;
}

bool VmiIDS::dequeueDetectionModule(std::string detectionModuleName) {
	bool success = false;
	pthread_mutex_lock(&activeDetectionModuleMutex);
	for (std::map<std::string, DetectionModule*>::iterator it =
			this->activeDetectionModules.begin(); it != this->activeDetectionModules.end(); ++it) {
		if (it->first.compare(detectionModuleName) == 0) {
			this->activeDetectionModules.erase(it);
			success = true;
		}
	}
	pthread_mutex_unlock(&activeDetectionModuleMutex);
	return success;
}

void VmiIDS::enqueueNotificationModule(NotificationModule *notificationModule) {
	pthread_mutex_lock(&notificationModuleMutex);
	notificationModules[notificationModule->getName()] = notificationModule;
	pthread_mutex_unlock(&notificationModuleMutex);
}

bool VmiIDS::enqueueNotificationModule(std::string notificationModuleName) {
	bool success = false;
	if (notificationModuleName.find("") != std::string::npos) {
		pthread_mutex_lock(&notificationModuleMutex);
		//notificationModules[notificationModuleName] = new SimpleDetectionModule();
		pthread_mutex_unlock(&notificationModuleMutex);
	}
	return success;
}

/**
 * @deprecated
 * @param notificationModuleName
 * @return
 */
bool VmiIDS::dequeueNotificationModule(std::string notificationModuleName) {
	bool success = false;
	pthread_mutex_lock(&notificationModuleMutex);
	for (std::map<std::string, NotificationModule*>::iterator it =
			this->notificationModules.begin(); it
			!= this->notificationModules.end(); ++it) {
		if (it->first.compare(notificationModuleName) == 0) {
			this->notificationModules.erase(it);
			success = true;
		}
	}
	pthread_mutex_unlock(&notificationModuleMutex);
	return success;
}

void VmiIDS::enqueueSensorModule(SensorModule *sensorModule) {
	pthread_mutex_lock(&sensorModuleMutex);
	sensorModules[sensorModule->getName()] = sensorModule;
	pthread_mutex_unlock(&sensorModuleMutex);
}

NotificationModule *VmiIDS::getNotificationModule(
		std::string notificationModuleName) {
	return this->notificationModules[notificationModuleName];
}

SensorModule *VmiIDS::getSensorModule(std::string sensorModuleName) {
	return this->sensorModules[sensorModuleName];
}

libconfig::Setting *VmiIDS::getSetting(std::string settingName){
	try {
		return &(this->config.lookup(settingName));
	}catch(libconfig::SettingNotFoundException e){
			return NULL;
	}
}

void VmiIDS::collectThreadLevel() {
}
