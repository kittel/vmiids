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
	notify = VmiIDS::getInstance()->getNotificationModule(
			"ShellNotificationModule");
	if (!notify) {
		printf("Could not load NotificationModule\n");
		return;
	}

	notify->info(this, "Constructor called\n");

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
		notify->critical(this)
				<< "Could not parse Options. Please add the following section to the config file:"
				<< std::endl << this->getName() << " = {" << std::endl
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

		throw ShellParserException();
	}

	this->initConsoleMonitor(optionConsoleName.c_str(),
			optionMonitorShell.c_str());

	this->loggedin = false;
	try {
		this->loggedin = this->isLoggedin();

		if (!this->loggedin) {
			notify->info(this, "Trying to login\n");
			this->loggedin = this->login(optionUsername, optionPassword);
		} else {
			notify->info(this, "Already logged in\n");
			this->monitorShell = optionMonitorShell.c_str();
		}
	} catch (const char * exception) {
		notify->info(this) << exception << std::endl;
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
	notify->info(this, "Login");
	notify->info(this) << "username: " << username << std::endl << "password: " << password << std::endl;
	this->monitorShell = optionLoginShell.c_str();
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

void ShellSensorModule::getProcessList(std::map<uint32_t, ShellProcess> &shellProcessMap){
	std::string psResult;
	this->parseCommandOutput("ps -A --no-headers", psResult);

	while (psResult[0] == '\n' || psResult[0] == '\r')
		psResult.erase(0, 1);

	//Parse process list retured by "ps -A --no-headers"
	size_t oldNewlineSeparator = 1;
	size_t newlineSeparator = 1;
	std::string currentLine;

	size_t position1 = 0;
	size_t position2 = 0;
	size_t position3 = 0;

	newlineSeparator = psResult.find("\n", newlineSeparator);
	currentLine = psResult.substr(oldNewlineSeparator, newlineSeparator
			- oldNewlineSeparator);

	ShellProcess process;

	position1 = currentLine.find("1", 2);
	process.pid = atoi(currentLine.substr(1, position1).c_str());

	position2 = currentLine.rfind("init");
	position3 = currentLine.find(" ", position2);
	process.processName = currentLine.substr(position2, position3 - position2);

	oldNewlineSeparator = newlineSeparator + 1;
	shellProcessMap.insert(std::pair<uint32_t, ShellProcess>(process.pid, process));

	while ((newlineSeparator = psResult.find("\n", oldNewlineSeparator))
			!= std::string::npos) {
		currentLine = psResult.substr(oldNewlineSeparator, newlineSeparator
				- oldNewlineSeparator);

		process.pid = atoi(currentLine.substr(1, position1 + 1).c_str());
		position3 = currentLine.find(" ", position2 + 1);
		process.processName = currentLine.substr(position2 + 1, position3 - position2);

		oldNewlineSeparator = newlineSeparator + 1;
		shellProcessMap.insert(std::pair<uint32_t, ShellProcess>(process.pid, process));
	}
	return;
}

void ShellSensorModule::getFileList(std::string &directory, std::set<std::string> &directories){
	std::string findResult;
	std::command = directory;
	this->parseCommandOutput(command.insert(0, "find ").c_str(), findResult);

	while (findResult[0] == '\n' || findResult[0] == '\r')
		findResult.erase(0, 1);

	std::string currentLine;

	size_t newLine = 0;
	size_t oldLine = 0;

	while ((newLine = findResult.find("\r\n", oldLine + 1)) != std::string::npos) {
		currentLine = findResult.substr(oldLine, newLine - oldLine);
		directories.insert(currentLine);
		oldLine = newLine + 2;
	}
	return;
}

void getFileContent(std::string &fileName, std::vector<char> &fileContent){
	std::string hexdumpResult;
	std::stringstream command;
	command << "test -e " << fileName << " && hexdump -v -e '1/1 \"%02X\"' " << fileName;
	this->parseCommandOutput(command.str(), hexdumpResult);
	std::cout << hexdumpResult << std::endl;

	return;
}
