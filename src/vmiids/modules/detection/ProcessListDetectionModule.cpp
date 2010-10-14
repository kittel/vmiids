/*
 * ProcessListDetectionModule.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#include "ProcessListDetectionModule.h"

LOADMODULE(ProcessListDetectionModule);

ProcessListDetectionModule::ProcessListDetectionModule() :
			DetectionModule("ProcessListDetectionModule") {
	GETSENSORMODULE(this->qemu, QemuMonitorSensorModule);
	GETSENSORMODULE(this->shell, ShellSensorModule);
	GETSENSORMODULE(this->memory, MemorySensorModule);
}

ProcessListDetectionModule::~ProcessListDetectionModule() {
}

void ProcessListDetectionModule::run() {

	bool isRunning;
	try {
		isRunning = this->qemu->isRunning();
	} catch (vmi::ModuleException &e) {
		critical << "Could not use QemuMonitorSensorModule";
		return;
	}

	//Get processlist from memtool
	std::map<uint32_t, MemtoolProcess> memtoolProcessMap;
	this->memory->getProcessList(memtoolProcessMap);

	//Erase swapper process shown in memtool
	memtoolProcessMap.erase((uint32_t) 0);

	if (!isRunning) {
		this->qemu->resumeVM();
	}

	//Get processlist from ps
	std::map<uint32_t, ShellProcess> psProcessMap;
	this->shell->getProcessList(psProcessMap);

	if (!isRunning) {
		this->qemu->pauseVM();
	}

	//Compare Process Lists
	std::map<uint32_t, ShellProcess>::iterator p_it;
	std::map<uint32_t, MemtoolProcess>::iterator m_it;
	float intrusion = 0;

	//Find process in Memtool not listed in ps
	for ( m_it=memtoolProcessMap.begin() ; m_it != memtoolProcessMap.end(); m_it++ ){
		if(psProcessMap.find((*m_it).first) == psProcessMap.end() ||
			psProcessMap.find((*m_it).first)->second.processName.compare(0, (*m_it).second.processName.length(),
					(*m_it).second.processName) != 0){
			critical << "Process not found in ps: PID: " << (*m_it).first << " Proccess: " << (*m_it).second.processName << std::endl;
			intrusion = 0.5;
		}else{
			psProcessMap.erase((*m_it).first);
			memtoolProcessMap.erase(m_it);
		}
	}

	//Find process in ps not listed in Memtool
	bool seenps = false;
	for ( p_it=psProcessMap.begin() ; p_it != psProcessMap.end(); p_it++ ){
		if(!seenps && (*p_it).second.processName.compare(0,2,"ps") != 0){
	    	seenps = true;
	    	critical << "Process not found in memtool: PID: " << (*p_it).first
	    			<< " Proccess: " << (*p_it).second.processName << std::endl;
	    	intrusion = 0.5;
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
			alert << "Virtual process detected: PID: " << (*p_it).first
					<< " Proccess: " << (*p_it).second.processName << std::endl;
			intrusion = 1;
		}
	}
	this->globalPsProcessMap = psProcessMap;

	//Memtool results
	for (m_it = memtoolProcessMap.begin(); m_it != memtoolProcessMap.end(); m_it++) {
		if (this->globalMemtoolProcessMap.find((*m_it).first) != globalMemtoolProcessMap.end()
				&& globalMemtoolProcessMap.find((*m_it).first)->second.processName.compare(
						0, (*m_it).second.processName.length(),
						(*m_it).second.processName) == 0) {
			alert << "Hidden process detected: PID: " << (*m_it).first
					<< " Proccess: " << (*m_it).second.processName << std::endl;
			intrusion = 1;
		}
	}
	this->globalMemtoolProcessMap = memtoolProcessMap;
	this->threatLevel = intrusion;

}
