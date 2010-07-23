/*
 * MemorySensorModule.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#include "MemorySensorModule.h"

#include <string>
#include <sstream>
#include <iostream>

ADDDYNAMICSENSORMODULE(MemorySensorModule, __LINE__)
;

MemorySensorModule::MemorySensorModule() :
			SensorModule("MemorySensorModule") {

	//Get NotificationModule
	this->notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!this->notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	libconfig::Setting *setting = VmiIDS::getInstance()->getSetting(
			this->getName());

	std::stringstream output;

	if (setting == NULL ||
			!setting->lookupValue("memtoolPath", this->memtoolPath) ||
			!setting->lookupValue("memtoolScriptPath", this->memtoolScriptPath) ||
			!setting->lookupValue("savedDebugingSymbols", this->savedDebugingSymbols) ||
			!setting->lookupValue("memdumpFile", this->memdumpFile))	{

		output.str("");
		output
				<< "Could not parse Options. Please add the following section to the config file:"
				<< std::endl << this->getName() << " = {" << std::endl
				<< "\tmemtoolPath           =  \"<path to memtool executable>\"; e.g. \"/usr/bin/memtool\""
				<< std::endl
				<< "\tmemtoolScriptPath     =  \"<path to memtool scripts>\";    e.g. \"/home/idsvm/memtool/scripts\""
				<< std::endl
				<< "\tsavedDebugingSymbols  =  \"<path to saved debuging symbols>\";    e.g. \"/home/idsvm/symbols.dump\""
				<< std::endl
				<< "\tmemdumpFile           =  \"<path to memdump file>\";    e.g. \"/dev/vda\""
				<< std::endl<< "};";

		this->notify->critical(output.str());
		throw MemorySensorModuleException();
	}
}

MemorySensorModule::~MemorySensorModule() {
	// TODO Auto-generated destructor stub
}


void MemorySensorModule::initSensorModule(){

}

void MemorySensorModule::runScript(std::string &scriptResult, std::string scriptName){
	std::stringstream command;

	std::string data;
	FILE *stream;
	char buffer[1024];

	command << "echo \"sc " << this->memtoolScriptPath << "/" << scriptName << "\" | "
			<< this->memtoolPath << " -l " << this->savedDebugingSymbols
			<< " -m " << this->memdumpFile << " 2>&1";

	stream = popen(command.str().c_str(), "r");
	while (fgets(buffer, 1024, stream) != NULL)
		data.append(buffer);
	pclose(stream);

	int firstChar;
	int lastChar;

	lastChar = data.rfind(">>>");

	firstChar = data.find(">>>");
	firstChar = data.find("\n", firstChar);
	firstChar++;

	scriptResult.append(data, firstChar, lastChar - firstChar);
}

void MemorySensorModule::getProcessList(std::string &processList){
	std::string scriptResult;

	this->runScript(scriptResult, "tasklist.js");

	int firstChar = scriptResult.find("\n");
	firstChar = scriptResult.find("\n", firstChar);
	firstChar = scriptResult.find("\n", firstChar); //Find the third line ...
	firstChar++;
	processList.append(scriptResult, firstChar, scriptResult.size()-firstChar);
}
