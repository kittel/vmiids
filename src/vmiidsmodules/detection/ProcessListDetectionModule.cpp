/*
 * ProcessListDetectionModule.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#include "ProcessListDetectionModule.h"

#include <sstream>

ADDDYNAMICDETECTIONMODULE(ProcessListDetectionModule, __LINE__)
;

ProcessListDetectionModule::ProcessListDetectionModule() :
			DetectionModule("ProcessListDetectionModule") {

	this->notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!this->notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	this->qemu
			= dynamic_cast<QemuMonitorSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"QemuMonitorSensorModule"));
	if (!this->qemu) {
		this->notify->critical("Could not load QemuMonitorSensorModule");
		return;
	}

	this->shell
			= dynamic_cast<ShellSensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"ShellSensorModule"));
	if (!this->shell) {
		this->notify->critical("Could not load ShellSensorModule");
		return;
	}

	this->memory
			= dynamic_cast<MemorySensorModule *> (VmiIDS::getInstance()->getSensorModule(
					"MemorySensorModule"));
	if (!this->memory) {
		this->notify->critical("Could not load MemorySensorModule");
		return;
	}
}

ProcessListDetectionModule::~ProcessListDetectionModule() {

}

void ProcessListDetectionModule::run() {

	bool isRunning;
	try {
		isRunning = this->qemu->isRunning();
	} catch (libVMI::QemuMonitorException e) {
		this->notify->critical("Could not use QemuMonitorSensorModule");
		return;
	}

	//Get processlist from memtool
	std::map<uint32_t, MemtoolProcess> memtoolProcessMap;
	memtoolProcessMap = this->memory->getProcessList();

	if (!isRunning) {
		this->qemu->resumeVM();
	}

	//Get processlist from ps
	std::map<uint32_t, ShellProcess> psProcessMap;
	psProcessMap = this->shell->getProcessList();

	if (!isRunning) {
		this->qemu->pauseVM();
	}

	//Compare Process Lists
	std::map<uint32_t, ShellProcess>::iterator p_it;
	std::map<uint32_t, MemtoolProcess>::iterator m_it;


	//Find process in ps not listed in Memtool
	for ( m_it=memtoolProcessMap.begin() ; m_it != memtoolProcessMap.end(); m_it++ ){
		if(psProcessMap.find((*m_it).first) == psProcessMap.end() ||
			psProcessMap.find((*m_it).first)->second.processName.compare(0, (*m_it).second.processName.length(),
					(*m_it).second.processName) != 0){
			std::stringstream output;
			output << "Process not found in ps: PID: " << (*m_it).first << " Proccess: " << (*m_it).second.processName << std::endl;
			this->notify->critical(output.str());
		}else{
			psProcessMap.erase((*m_it).first);
			memtoolProcessMap.erase(m_it);
		}
	}

	//Find process in memtool not listed in ps
	for ( p_it=psProcessMap.begin() ; p_it != psProcessMap.end(); p_it++ ){
	    bool seenps = false;
		if(!seenps && (*p_it).second.processName.compare(0,2,"ps") != 0){
	    	seenps = true;
			std::stringstream output;
	    	output << "Process not found in memtool: PID: " << (*p_it).first
	    			<< " Proccess: " << (*p_it).second.processName << std::endl;
	    	this->notify->critical(output.str());
	    }else{
	    	psProcessMap.erase(p_it);
	    }
	}

	//Compare with results of last run

	//ps results
	for (p_it = psProcessMap.begin(); p_it != psProcessMap.end(); p_it++) {
		if (this->globalPsProcessMap.find((*p_it).first) != globalPsProcessMap.end()
				&& globalPsProcessMap.find((*p_it).first)->second.processName.compare(
						0, (*p_it).second.processName.length(),
						(*p_it).second.processName) == 0) {
			std::stringstream output;
			output << "Virtual process detected: PID: " << (*p_it).first
					<< " Proccess: " << (*p_it).second.processName << std::endl;
			this->notify->alert(output.str());
		}
	}
	this->globalPsProcessMap = psProcessMap;

	//Memtool results
	for (m_it = memtoolProcessMap.begin(); m_it != memtoolProcessMap.end(); m_it++) {
		if (this->globalMemtoolProcessMap.find((*m_it).first) != globalMemtoolProcessMap.end()
				&& globalMemtoolProcessMap.find((*m_it).first)->second.processName.compare(
						0, (*m_it).second.processName.length(),
						(*m_it).second.processName) == 0) {
			std::stringstream output;
			output << "Hidden process detected: PID: " << (*m_it).first
					<< " Proccess: " << (*m_it).second.processName << std::endl;
			this->notify->alert(output.str());
		}
	}
	this->globalMemtoolProcessMap = memtoolProcessMap;
}

void ProcessListDetectionModule::runTime() {

}

void ProcessListDetectionModule::runEvent() {

}

void ProcessListDetectionModule::getThreadLevel() {

}
