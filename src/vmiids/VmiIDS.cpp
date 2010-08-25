/*
 * VmiIDS.cpp
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#include "VmiIDS.h"

#include <string>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

#include <dlfcn.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <set>
#include "DetectionThread.h"

vmi::VmiIDS* vmi::VmiIDS::instance = NULL;

vmi::VmiIDS::VmiIDS() :
		 vmi::Module("VmiIDS"), vmi::OutputModule("VmiIDS"),
		 detectionModules(), sensorModules(),
		 rpcServer(), config(){
	Thread::setDefaultUncaughtExceptionHandler(defaultExceptionHandler);
	this->vmiRunning = true;
	pthread_mutex_init(&detectionModuleMutex, NULL);
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
}

vmi::VmiIDS::~VmiIDS() {
	this->vmiRunning = false;
	this->join();
	pthread_mutex_lock(&detectionModuleMutex);
	pthread_mutex_lock(&sensorModuleMutex);
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
	pthread_mutex_unlock(&sensorModuleMutex);
}

vmi::VmiIDS *vmi::VmiIDS::getInstance() {
	if (!instance)
		instance = new VmiIDS();
	return instance;
}

void vmi::VmiIDS::defaultExceptionHandler(std::exception& e){
	vmi::VmiIDS::getInstance()->error << e.what() << std::endl;
}

bool vmi::VmiIDS::stopIDS(int signum) {
	signum = 0;
	vmi::VmiIDS::getInstance()->printDebug("IDS Stopping\n");
	delete instance;
	instance = NULL;
	return true;
}

void vmi::VmiIDS::run(void) {

	//
	// Load Modules by Path Name
	//
	try {
		for(int i = 0 ;  i < this->config.lookup("initialModuleByPath").getLength() ; i++){
			this->loadSharedObjectsPath(this->config.lookup("initialModuleByPath")[i]);
		}
	}catch(libconfig::SettingNotFoundException &e){
		this->printDebug("No Modules loaded by Path ...\n");
	}

	//
	// Load Modules by So Path
	//
	try {
	for(int i = 0 ;  i < this->config.lookup("initialModuleBySoPath").getLength() ; i++){
			this->loadSharedObject(this->config.lookup("initialModuleBySoPath")[i]);
		}
	}catch(libconfig::SettingNotFoundException &e){
		this->printDebug("No Modules loaded by So Path ...\n");
	}

	//
	// Start DetectionModules by Name
	//
	std::map<int, DetectionThread*> runModules;
	try {
		for(int i = 0 ;  i < this->config.lookup("runModules").getLength() ; i++){
			libconfig::Setting &modulesSetting = this->config.lookup("runModules")[i];
			int seconds = modulesSetting["secondsBetweenRun"];
			std::cout << "Module with " << seconds << " Second per Run" << std::endl;
			DetectionThread *thread = new DetectionThread(seconds);
			for(int j = 0 ;  j < modulesSetting["modules"].getLength() ; j++){
				std::string module = modulesSetting["modules"][j];
				std::cout << "enqueueing Module " << module << std::endl;
				thread->enqueueModule(modulesSetting["modules"][j]);
			}
			runModules[seconds] = thread;
			thread->start();
		}
	}catch(libconfig::SettingNotFoundException &e){
		this->printDebug("No Modules started ...\n");
	}

	while(this->vmiRunning){
		this->sleep(1000);
	}
	//Delete Threads afterwards
	while (!runModules.empty()) {
		if(runModules.begin()->second != NULL)
			delete (runModules.begin()->second);
		runModules.erase(runModules.begin());
	}
	return;
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
	detectionModuleName.c_str();
/*
	pthread_mutex_lock(&detectionModuleMutex);
	pthread_mutex_lock(&activeDetectionModuleMutex);
	if (detectionModules[detectionModuleName] != NULL) {
		activeDetectionModules[detectionModuleName] = detectionModules[detectionModuleName];
		success = true;
	}
	pthread_mutex_unlock(&activeDetectionModuleMutex);
	pthread_mutex_unlock(&detectionModuleMutex);
*/
	return success;
}

bool vmi::VmiIDS::dequeueDetectionModule(std::string detectionModuleName) {
	bool success = false;
	detectionModuleName.c_str();
/*	pthread_mutex_lock(&activeDetectionModuleMutex);
	for (std::map<std::string, DetectionModule*>::iterator it =
			this->activeDetectionModules.begin(); it != this->activeDetectionModules.end(); ++it) {
		if (it->first.compare(detectionModuleName) == 0) {
			this->activeDetectionModules.erase(it);
			success = true;
		}
	}
	pthread_mutex_unlock(&activeDetectionModuleMutex);
*/
	return success;
}

vmi::SensorModule *vmi::VmiIDS::getSensorModule(std::string sensorModuleName) {
    if(this->sensorModules.find(sensorModuleName) == this->sensorModules.end()){
    	return NULL;
    }
   	return this->sensorModules[sensorModuleName];
}

vmi::DetectionModule *vmi::VmiIDS::getDetectionModule(std::string detectionModuleName) {
    if(this->detectionModules.find(detectionModuleName) == this->detectionModules.end()){
    	return NULL;
    }
   	return this->detectionModules[detectionModuleName];
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
