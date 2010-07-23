/*
 * ShellSensorModule.cpp
 *
 *  Created on: Jul 2, 2010
 *      Author: kittel
 */

#include "ShellSensorModule.h"

#include <sstream>

ADDDYNAMICSENSORMODULE(ShellSensorModule, __LINE__)
;

ShellSensorModule::ShellSensorModule() :
	SensorModule("ShellSensorModule"), ConsoleMonitor() {

	//Get NotificationModule
	this->notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!this->notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	std::stringstream output;

	this->notify->info("ShellSensorModule: Constructor called\n");

	std::string optionConsoleName;
	std::string optionUsername;
	std::string optionPassword;

	libconfig::Setting *setting = VmiIDS::getInstance()->getSetting(
			this->getName());

	if (setting == NULL || !setting->lookupValue("consoleName",
			optionConsoleName) || !setting->lookupValue("monitorShell",
			optionMonitorShell) || !setting->lookupValue("loginShell",
			optionLoginShell) || !setting->lookupValue("passwordShell",
			optionPasswordShell) || !setting->lookupValue("username",
			optionUsername)
			|| !setting->lookupValue("password", optionPassword)) {
		output.str("");
		output
				<< "Could not parse Options. Please add the following section to the config file:"
				<< std::endl << "ShellSensorModule = {" << std::endl
				<< "\tconsoleName   =  \"<shell device>\";        e.g. \"/dev/ttyS2\""
				<< std::endl
				<< "\tmonitorShell  =  \"<shell identifier>\";    e.g. \"rootkitvm@rootkitvm:"
				<< std::endl
				<< "\tloginShell    =  \"<login identifier>\";    e.g. \"login:\""
				<< std::endl
				<< "\tpasswordShell =  \"<password identifier>\"; e.g. \"Password:\""
				<< std::endl
				<< "\tusername      =  \"<username>\" ;           e.g. \"rootkitvm\""
				<< std::endl
				<< "\tpassword      =  \"<password>\";            e.g. \"rootkitvm\""
				<< std::endl << "};";

		this->notify->critical(output.str());
		throw ShellParserException();
	}

	output.str("");
	output << "optionConsoleName: " << optionConsoleName << std::endl
			<< "optionMonitorShell: " << optionMonitorShell << std::endl
			<< "optionLoginShell: " << optionLoginShell << std::endl
			<< "optionPasswordShell: " << optionPasswordShell << std::endl
			<< "optionUsername: " << optionUsername << std::endl
			<< "optionPassword: " << optionPassword;
	this->notify->info(output.str());

	this->initConsoleMonitor(optionConsoleName.c_str(),
			optionMonitorShell.c_str());

	this->loggedin = false;
	try {
		this->loggedin = this->isLoggedin();

		if (!this->loggedin) {
			this->notify->info("ShellSensorModule: Trying to login\n");
			this->loggedin = this->login(optionUsername, optionPassword);
		} else {
			this->notify->info("ShellSensorModule: Already logged in\n");
			this->monitorShell = optionMonitorShell.c_str();
		}
	} catch (const char * exception) {
		std::stringstream message("ShellSensorModule: %s\n");
		message << exception;
		this->notify->info(message.str());
	}
}

ShellSensorModule::~ShellSensorModule() {
	// TODO Auto-generated destructor stub
}

void ShellSensorModule::initSensorModule() {

}

bool ShellSensorModule::isLoggedin(void) {
	std::string searchString;
	std::string replyString;
	std::string lastLine;

	this->sendCommand("");
	for (int searchCount = 1000; searchCount > 0; searchCount--) {
		usleep(1000);
		parseOutput(replyString);
		searchString.append(replyString);
		if (searchString.rfind("\n") != std::string::npos) {
			lastLine = searchString.substr(searchString.rfind("\n") + 1);
		} else {
			lastLine = searchString;
		}
		if (lastLine.find(optionLoginShell) != std::string::npos) {
			return false;
			break;
		} else if (lastLine.find(optionMonitorShell) != std::string::npos) {
			return true;
		}
	}
	throw "Unknown shell state\n";
	return false;
}

bool ShellSensorModule::login(std::string username, std::string password) {
	this->notify->info("ShellSensorModule: Login");
	std::stringstream output;
	output << "username: " << username << std::endl << "password: " << password;
	this->monitorShell = optionLoginShell.c_str();
	this->notify->info(output.str());
	std::string string;
	this->parseCommandOutput("", string);
	string.clear();
	this->monitorShell = optionPasswordShell.c_str();
	this->parseCommandOutput(username, string);
	string.clear();
	this->sendCommand(password.c_str());
	std::string buffer;
	for (int searchCount = 3000; searchCount > 0; searchCount--) {
		usleep(1000);
		parseOutput(buffer);
		string.append(buffer);
		if (string.find("Login incorrect") != std::string::npos) {
			this->monitorShell = optionLoginShell.c_str();
			return false;
		} else if (string.find(optionMonitorShell) != std::string::npos) {
			this->monitorShell = optionMonitorShell.c_str();
			return true;
		}
	}

	this->monitorShell = optionLoginShell.c_str();
	throw ShellParserException();
	return false;
}

void ShellSensorModule::logout() {
	if (this->loggedin) {
		this->sendCommand("logout");
		this->loggedin = false;
	}
}
