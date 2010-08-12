/*
 * VmiIDS.cpp
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#include "VmiIDS.h"

#include <pthread.h>
#include <rpc/pmap_clnt.h>

#include <string>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <memory.h>

#include <dlfcn.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <signal.h>
#include <execinfo.h>
#include <ucontext.h>
#include <cxxabi.h>

// rpcthread SIGTERM
	//pthread_exit(NULL);

	// mainThread SIGTERM
	//vmi::VmiIDS::getInstance()->stopIDS(signum);

	// moduleThread SIGSEGV
	//stackTrace
	//blacklist module
	//pthread_exit()

int signal_handler_sigint = 0;

void signal_handler(int sig_num, siginfo_t * info, void * ucontext) {
	if (sig_num == SIGINT) {
		if(!signal_handler_sigint) {
			vmi::VmiIDS::getInstance()->stopIDS(sig_num);
			signal_handler_sigint++;
		}else{
			pthread_exit(NULL);
		}
	}else if (sig_num == SIGTERM) {
			pthread_exit(NULL);
	} else if (sig_num == SIGSEGV) {
		void * array[50];
		void * caller_address;
		char ** messages;
		int size, i;
		struct ucontext * uc;

		uc = (struct ucontext *) ucontext;

		/* Get the address at the time the signal was raised from the EIP (x86) */
#if __WORDSIZE == 64

		caller_address = (void *) uc->uc_mcontext.gregs[REG_RIP];

#else /* __WORDSIZE == 32 */

		caller_address = (void *) uc->uc_mcontext.gregs[REG_EIP];

#endif /* __WORDSIZE == 32 */

		fprintf(stderr, "signal %d (%s), address is %p from %p\n", sig_num,
				strsignal(sig_num), info->si_addr, (void *) caller_address);

		size = backtrace(array, 50);

		messages = backtrace_symbols(array, size);

		/* skip first stack frame (points here) */
		for (i = 2; i < size && messages != NULL; ++i) {
			std::string trace(messages[i]);

			// attempt to demangle
			{
				std::string::size_type begin, end;

				// find the beginning and the end of the useful part of the trace
				begin = trace.find_first_of('(') + 1;
				end = trace.find_last_of('+');

				// if they were found, we'll go ahead and demangle
				if (begin != std::string::npos && end != std::string::npos) {
					std::string functionName = trace.substr(begin, end - begin);

					int demangleStatus;

					char* demangledName;
					if ((demangledName = abi::__cxa_demangle(
							functionName.c_str(), 0, 0, &demangleStatus))
							&& demangleStatus == 0) {
						trace.replace(begin, end - begin, demangledName); // the demangled name is now in our trace string
					}
					free(demangledName);
				}
			}
			fprintf(stderr, "[bt]: (%d) %s\n", i - 1, trace.c_str());
		}

		free(messages);

		pthread_exit(NULL);
	}
}

void * stopIDSThreadFunction(void * nothing) {
	nothing = NULL;
	sleep(1);
	vmi::VmiIDS::getInstance()->stopIDS(SIGTERM);
	return NULL;
}

void * rpcThreadFunction(void * argument) {
	argument = NULL;

	register SVCXPRT *transp;

	pmap_unset (VMIIDS_RPC, VMIIDS_RPC_VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, VMIIDS_RPC, VMIIDS_RPC_VERSION, vmi::VmiIDS::dispatchRPC, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (VMIIDS_RPC_PROG, VMIIDS_RPC_VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, VMIIDS_RPC, VMIIDS_RPC_VERSION, vmi::VmiIDS::dispatchRPC, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (VMIIDS_RPC_PROG, VMIIDS_RPC_VERSION, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	/* NOTREACHED */

	pthread_exit(NULL);
}

int main() {

	struct sigaction signal_action;

	/* Set up the structure to specify the new action. */
	signal_action.sa_sigaction = signal_handler;
	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_flags = SA_RESTART | SA_SIGINFO;

	//To catch crtl c
	sigaction(SIGINT, &signal_action, NULL);
	//To kill threads
	sigaction(SIGTERM, &signal_action, NULL);
	//To catch segfaults
	sigaction(SIGSEGV, &signal_action, NULL);

	vmi::VmiIDS::getInstance()->startIDS();
	vmi::VmiIDS::getInstance()->waitIDS();

	exit(0);
}

vmi::VmiIDS* vmi::VmiIDS::instance = NULL;

vmi::VmiIDS::VmiIDS() :
		 vmi::Module("VmiIDS"), detectionModules(), notificationModules(), sensorModules(), config(){
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
		}catch(libconfig::ParseException &e){
			printf("Could not read config file\n");
		}
	}
	this->mainThread = pthread_self();
	atexit(vmi::VmiIDS::killInstance);
}

vmi::VmiIDS::~VmiIDS() {
	pthread_mutex_lock(&detectionModuleMutex);
	pthread_mutex_lock(&activeDetectionModuleMutex);
	pthread_mutex_lock(&notificationModuleMutex);
	pthread_mutex_lock(&sensorModuleMutex);

	while (!activeDetectionModules.empty()) {
		//Do not delete Module, because there is still a pointer in detectionModules map.
		activeDetectionModules.erase(activeDetectionModules.begin());
	}
	while (!detectionModules.empty()) {
		printf("Deleting %s\n", detectionModules.begin()->first.c_str());
		if(detectionModules.begin()->second != NULL)
			delete (detectionModules.begin()->second);
		detectionModules.erase(detectionModules.begin());
	}
	while (!sensorModules.empty()) {
		printf("Deleting %s\n", sensorModules.begin()->first.c_str());
		if(sensorModules.begin()->second != NULL)
			delete (sensorModules.begin()->second);
		sensorModules.erase(sensorModules.begin());
	}
	while (!notificationModules.empty()) {
		printf("Deleting %s\n", notificationModules.begin()->first.c_str());
		if(notificationModules.begin()->second != NULL)
			delete (notificationModules.begin()->second);
		notificationModules.erase(notificationModules.begin());
	}
}

vmi::VmiIDS *vmi::VmiIDS::getInstance() {
	if (!instance)
		instance = new VmiIDS();
	return instance;
}

void vmi::VmiIDS::killInstance() {
	if (instance){
		delete(instance);
		instance = NULL;
	}
}

int vmi::VmiIDS::startIDS() {
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

void * vmi::VmiIDS::run(void * this_pointer) {

	VmiIDS * this_p = (VmiIDS *) this_pointer;

	//
	// Load Modules by Path Name
	//
	try {
		for(int i = 0 ;  i < this_p->config.lookup("initialModuleByPath").getLength() ; i++){
			this_p->loadSharedObjectsPath(this_p->config.lookup("initialModuleByPath")[i]);
		}
	}catch(libconfig::SettingNotFoundException &e){
			printf("No Modules loaded by Path ...\n");
	}

	//
	// Load Modules by So Path
	//
	try {
	for(int i = 0 ;  i < this_p->config.lookup("initialModuleBySoPath").getLength() ; i++){
			this_p->loadSharedObject(this_p->config.lookup("initialModuleBySoPath")[i]);
		}
	}catch(libconfig::SettingNotFoundException &e){
		printf("No Modules loaded by So Path ...\n");
	}

	//
	// Start DetectionModules by Name
	//
	try {
	for(int i = 0 ;  i < this_p->config.lookup("startModules").getLength() ; i++){
			this_p->enqueueDetectionModule(this_p->config.lookup("startModules")[i]);
		}
	}catch(libconfig::SettingNotFoundException &e){
		printf("No Modules started ...\n");
	}

	pthread_t moduleThread;

	while (this_p->vmiRunning) {
		pthread_mutex_lock(&this_p->activeDetectionModuleMutex);

		for (std::map<std::string, DetectionModule*>::iterator it =
				this_p->activeDetectionModules.begin(); it
				!= this_p->activeDetectionModules.end(); ++it) {

			pthread_create(&moduleThread, NULL, VmiIDS::runDetectionModule,
						(void*) it->second);
			pthread_join(moduleThread, NULL);

		}
		pthread_mutex_unlock(&this_p->activeDetectionModuleMutex);
		sleep(1);
	}
	return NULL;
}

void* vmi::VmiIDS::runDetectionModule(void* module){
	DetectionModule * module_p = (DetectionModule *) module;
	try {
		module_p->run();
	} catch (vmi::ModuleException &e) {
		e.printException();
	} catch (std::exception &e) {
		std::cerr << "Failed: " << e.what() << std::endl;
	}

	pthread_exit(NULL);
}

void vmi::VmiIDS::dispatchRPC(struct svc_req *rqstp, register SVCXPRT *transp){
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

void vmi::VmiIDS::loadSharedObjectsPath(std::string path) {

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
				this->loadSharedObject(filename.c_str());
			}
		}
	}
	closedir(dp);
	return;

}

bool vmi::VmiIDS::loadSharedObject(std::string path) {
	void *dlib;
	dlib = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);
	if (dlib == NULL) {
		std::cerr << "Error while loading " << path << ": " << dlerror() << std::endl;
		return false;
	}
	return true;
}

void vmi::VmiIDS::waitIDS() {
	pthread_join(vmiidsThread, NULL);
}

bool vmi::VmiIDS::stopIDS(int signum) {
	signum = 0;
	printf("IDS Stopping\n");
	this->vmiRunning = false;
	pthread_kill(this->rpcThread, SIGTERM);
	pthread_join(this->rpcThread, NULL);
	pthread_join(this->vmiidsThread, NULL);
	return true;
}

void vmi::VmiIDS::enqueueDetectionModule(DetectionModule *detectionModule) {
	pthread_mutex_lock(&detectionModuleMutex);
	detectionModules[detectionModule->getName()] = detectionModule;
	pthread_mutex_unlock(&detectionModuleMutex);
}

bool vmi::VmiIDS::enqueueDetectionModule(std::string detectionModuleName) {
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

bool vmi::VmiIDS::dequeueDetectionModule(std::string detectionModuleName) {
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

void vmi::VmiIDS::enqueueNotificationModule(NotificationModule *notificationModule) {
	pthread_mutex_lock(&notificationModuleMutex);
	notificationModules[notificationModule->getName()] = notificationModule;
	pthread_mutex_unlock(&notificationModuleMutex);
}

bool vmi::VmiIDS::enqueueNotificationModule(std::string notificationModuleName) {
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
bool vmi::VmiIDS::dequeueNotificationModule(std::string notificationModuleName) {
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

void vmi::VmiIDS::enqueueSensorModule(SensorModule *sensorModule) {
	pthread_mutex_lock(&sensorModuleMutex);
	sensorModules[sensorModule->getName()] = sensorModule;
	pthread_mutex_unlock(&sensorModuleMutex);
}

vmi::NotificationModule *vmi::VmiIDS::getNotificationModule(
		std::string notificationModuleName) {
	return this->notificationModules[notificationModuleName];
}

vmi::SensorModule *vmi::VmiIDS::getSensorModule(std::string sensorModuleName) {
	return this->sensorModules[sensorModuleName];
}

libconfig::Setting *vmi::VmiIDS::getSetting(std::string settingName){
	try {
		return &(this->config.lookup(settingName));
	}catch(libconfig::SettingNotFoundException &e){
			return NULL;
	}
}

void vmi::VmiIDS::collectThreadLevel() {
}
