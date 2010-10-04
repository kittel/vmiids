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

#include "vmiids/util/MutexLocker.h"

#include "NotificationModule.h"

vmi::VmiIDS* vmi::VmiIDS::instance = NULL;

vmi::VmiIDS::VmiIDS() :
		 vmi::Module("VmiIDS"), vmi::OutputModule("VmiIDS"),
		 rpcServer(){

	Thread::setDefaultUncaughtExceptionHandler(defaultExceptionHandler);

	this->vmiRunning = true;
}

vmi::VmiIDS::~VmiIDS() {
	this->vmiRunning = false;
	this->join();

	DetectionModule::killInstances();
	SensorModule::killInstances();
	NotificationModule::killInstances();
}

vmi::VmiIDS *vmi::VmiIDS::getInstance() {
	if (!instance)
		instance = new VmiIDS();
	return instance;
}

void vmi::VmiIDS::defaultExceptionHandler(std::exception& e){
	vmi::VmiIDS::getInstance()->error << e.what() << std::endl;
}

void vmi::VmiIDS::loadModules(){

	//
	// Load Modules by Path Name
	//
	try {
		libconfig::Setting &setting = Settings::getInstance()->getSetting("initialModuleByPath");
		for (int i = 0; i < setting.getLength(); i++) {
			this->loadSharedObjectsPath(setting[i]);
		}
	} catch (OptionNotFoundException &e) {
		this->printDebug("No Modules loaded by Path ...\n");
	}

	//
	// Load Modules by Filename
	//
	try {
		libconfig::Setting &setting = Settings::getInstance()->getSetting("initialModuleByFilename");
		for (int i = 0; i < setting.getLength(); i++) {
			this->loadSharedObjectsPath(setting[i]);
		}
	} catch (OptionNotFoundException &e) {
		this->printDebug("No Modules loaded by Filename ...\n");
	}

	//
	// Start DetectionModules by Name
	//
	try {
		libconfig::Setting &setting = Settings::getInstance()->getSetting("runModules");
		for (int i = 0; i < setting.getLength(); i++) {
			libconfig::Setting &modulesSetting = setting[i];
			int seconds = modulesSetting["secondsBetweenRun"];
			DetectionThread *thread = new DetectionThread(seconds);
			for (int j = 0; j < modulesSetting["modules"].getLength(); j++) {
				std::string module = modulesSetting["modules"][j];
				thread->enqueueModule(modulesSetting["modules"][j]);
			}
			runModules[seconds] = thread;
			thread->start();
		}
	} catch (libconfig::SettingNotFoundException &e) {
		this->printDebug("No DetectionModules started ...\n");
	} catch (OptionNotFoundException &e) {
		this->printDebug("No DetectionModules started ...\n");
	}

}

void vmi::VmiIDS::initVmiIDS(){

	this->loadModules();
}

bool vmi::VmiIDS::stopIDS(int signum) {
	signum = 0;
	vmi::VmiIDS::getInstance()->printDebug("IDS Stopping\n");
	delete instance;
	instance = NULL;
	return true;
}

void vmi::VmiIDS::run(void) {

	this->initVmiIDS();

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

bool vmi::VmiIDS::enqueueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds) {

	if (runModules.find(timeInSeconds) == runModules.end()){
		runModules[timeInSeconds] = new DetectionThread(timeInSeconds);
	}
	return runModules[timeInSeconds]->enqueueModule(detectionModuleName);
}

bool vmi::VmiIDS::dequeueDetectionModule(std::string detectionModuleName, uint32_t timeInSeconds) {
	bool success = false;

	if (runModules.find(timeInSeconds) == runModules.end()){
		return success;
	}

	success = runModules[timeInSeconds]->dequeueModule(detectionModuleName);
	if(runModules[timeInSeconds]->getModuleCount() == 0){
		delete (runModules[timeInSeconds]);
		runModules.erase(runModules.find(timeInSeconds));
	}
	return success;
}

void vmi::VmiIDS::collectThreadLevel() {
}
