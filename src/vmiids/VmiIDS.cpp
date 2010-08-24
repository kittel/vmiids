/*
 * VmiIDS.cpp
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#include "VmiIDS.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

#include <dlfcn.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <signal.h>
#include <execinfo.h>
#include <ucontext.h>
#include <cxxabi.h>

#include "RpcNotificationModule.h"

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
pthread_t vmi::VmiIDS::mainThread = NULL;
pthread_t vmi::VmiIDS::vmiidsThread = NULL;
bool vmi::VmiIDS::vmiRunning = false;

vmi::VmiIDS::VmiIDS() :
		 vmi::Module("VmiIDS"), vmi::OutputModule("VmiIDS"),
		 detectionModules(), sensorModules(),
		 rpcServer(), config(){
	this->vmiRunning = false;
	pthread_mutex_init(&detectionModuleMutex, NULL);
	pthread_mutex_init(&activeDetectionModuleMutex, NULL);
	pthread_mutex_init(&sensorModuleMutex, NULL);

	FILE * configFile;

	if( ((configFile = fopen ("vmiids.cfg" , "r")) != NULL) ||
		((configFile = fopen ("/etc/vmiids.cfg" , "r")) != NULL)    ){

		try {
			config.read(configFile);
			fclose (configFile);
		}catch(libconfig::ParseException &e){
			this->printError("Could not read config file\n");
		}
	}
	this->mainThread = pthread_self();
}

vmi::VmiIDS::~VmiIDS() {
	pthread_mutex_lock(&detectionModuleMutex);
	pthread_mutex_lock(&activeDetectionModuleMutex);
	pthread_mutex_lock(&sensorModuleMutex);
	while (!activeDetectionModules.empty()) {
		//Do not delete Module, because there is still a pointer in detectionModules map.
		activeDetectionModules.erase(activeDetectionModules.begin());
	}
	while (!detectionModules.empty()) {
		this->printDebug("Deleting %s\n", detectionModules.begin()->first.c_str());
		if(detectionModules.begin()->second != NULL)
			delete (detectionModules.begin()->second);
		detectionModules.erase(detectionModules.begin());
	}
	while (!sensorModules.empty()) {
		this->printDebug("Deleting %s\n", sensorModules.begin()->first.c_str());
		if(sensorModules.begin()->second != NULL)
			delete (sensorModules.begin()->second);
		sensorModules.erase(sensorModules.begin());
	}
	pthread_mutex_unlock(&detectionModuleMutex);
	pthread_mutex_unlock(&activeDetectionModuleMutex);
	pthread_mutex_unlock(&sensorModuleMutex);
}

vmi::VmiIDS *vmi::VmiIDS::getInstance() {
	if (!instance)
		instance = new VmiIDS();
	return instance;
}

int vmi::VmiIDS::startIDS() {
	if (this->vmiRunning == true) {
		this->printError("IDS already running");
		return 0;
	}
	this->printDebug("IDS Starting\n");
	this->vmiRunning = true;
	pthread_create(&vmiidsThread, NULL, VmiIDS::run,
			(void*) this);
	return 0;
}

void vmi::VmiIDS::waitIDS() {
	pthread_join(vmiidsThread, NULL);
	while(instance != NULL){
		sched_yield();
	}
}

bool vmi::VmiIDS::stopIDS(int signum) {
	signum = 0;
	vmi::VmiIDS::getInstance()->printDebug("IDS Stopping\n");
	vmi::VmiIDS::getInstance()->vmiRunning = false;
	pthread_join(vmiidsThread, NULL);
	delete instance;
	instance = NULL;
	return true;
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
		this_p->printDebug("No Modules loaded by Path ...\n");
	}

	//
	// Load Modules by So Path
	//
	try {
	for(int i = 0 ;  i < this_p->config.lookup("initialModuleBySoPath").getLength() ; i++){
			this_p->loadSharedObject(this_p->config.lookup("initialModuleBySoPath")[i]);
		}
	}catch(libconfig::SettingNotFoundException &e){
		this_p->printDebug("No Modules loaded by So Path ...\n");
	}

	//
	// Start DetectionModules by Name
	//
	try {
	for(int i = 0 ;  i < this_p->config.lookup("startModules").getLength() ; i++){
			this_p->enqueueDetectionModule(this_p->config.lookup("startModules")[i]);
		}
	}catch(libconfig::SettingNotFoundException &e){
		this_p->printDebug("No Modules started ...\n");
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

std::string vmi::VmiIDS::runSingleDetectionModule(std::string detectionModuleName){
	RpcNotificationModule rpc;
	pthread_t moduleThread;
	pthread_mutex_lock(&this->detectionModuleMutex);
	pthread_mutex_lock(&activeDetectionModuleMutex);
	std::map<std::string, DetectionModule*>::iterator it;
	if((it = this->detectionModules.find(detectionModuleName)) != this->detectionModules.end()){
		pthread_create(&moduleThread, NULL, VmiIDS::runDetectionModule,
					(void*) it->second);
		pthread_join(moduleThread, NULL);
	}else {
		pthread_mutex_unlock(&this->detectionModuleMutex);
		pthread_mutex_unlock(&activeDetectionModuleMutex);
		return "Detection Module not found\n";
	}
	pthread_mutex_unlock(&this->detectionModuleMutex);
	pthread_mutex_unlock(&activeDetectionModuleMutex);
	return rpc.getRpcResult();
}

void vmi::VmiIDS::loadSharedObjectsPath(std::string path) {

	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(path.c_str())) == NULL) {
		error << "Error opening " << path << std::endl;
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
		error << "Error while loading " << path << ": " << dlerror() << std::endl;
		return false;
	}
	return true;
}

void vmi::VmiIDS::enqueueModule(DetectionModule *module) {
	if(module == NULL) return;
	pthread_mutex_lock(&detectionModuleMutex);
	detectionModules[module->getName()] = module;
	pthread_mutex_unlock(&detectionModuleMutex);
}

void vmi::VmiIDS::enqueueModule(SensorModule *module) {
	if(module == NULL) return;
	pthread_mutex_lock(&sensorModuleMutex);
	sensorModules[module->getName()] = module;
	pthread_mutex_unlock(&sensorModuleMutex);
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

vmi::SensorModule *vmi::VmiIDS::getSensorModule(std::string sensorModuleName) {
    if(this->sensorModules.find(sensorModuleName) == this->sensorModules.end()){
    	return NULL;
    }
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
