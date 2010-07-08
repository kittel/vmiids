#include "ShellParser.h"

#include <iostream>
#include <stdio.h>

#define SHELLDEVICE "/dev/ttyS2"
#define LOGINSHELL  "login:"
#define PASSWORDSHELL  "Password:"
#define COMMANDSHELL  "rootkitvm@rootkitvm:"

//#define DEBUG

#ifdef DEBUG
#define VERBOSE "ShellParser"
#endif /* DEBUG */
#include "Debug.h"

namespace libVMI {

ShellParser::ShellParser() :
	ConsoleMonitor(SHELLDEVICE, LOGINSHELL) {

	LIBVMI_DEBUG_MSG("Constructor called\n");
	this->loggedin = false;
	try {
		this->loggedin = this->isLoggedin();

		if (!this->loggedin) {
			LIBVMI_DEBUG_MSG("Trying to login\n");
			this->loggedin = this->login("rootkitvm", "rootkitvm");
		} else {
			LIBVMI_DEBUG_MSG("Already logged in\n");
			this->monitorShell = COMMANDSHELL;
		}
	} catch (const char * exception) {
		LIBVMI_DEBUG_MSG("%s\n", exception);
	}
}

ShellParser::~ShellParser() {
}

bool ShellParser::isLoggedin(void) {
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
		if (lastLine.find(" " LOGINSHELL " ") != std::string::npos) {
			return false;
			break;
		} else if (lastLine.find(COMMANDSHELL) != std::string::npos) {
			return true;
		}
	}
	throw "Unknown shell state\n";
	return false;
}

bool ShellParser::login(const char* username, const char * password) {
	LIBVMI_DEBUG_MSG("Login");
	std::string string;
	this->parseCommandOutput("", string);
	string.clear();
	this->monitorShell = PASSWORDSHELL;
	this->parseCommandOutput(username, string);
	string.clear();
	this->sendCommand(password);
	std::string buffer;
	for (int searchCount = 3000; searchCount > 0; searchCount--) {
		usleep(1000);
		parseOutput(buffer);
		string.append(buffer);
		if (string.find("Login incorrect") != std::string::npos) {
			this->monitorShell = LOGINSHELL;
			return false;
		} else if (string.find(COMMANDSHELL) != std::string::npos) {
			this->monitorShell = COMMANDSHELL;
			return true;
		}
	}

	this->monitorShell = LOGINSHELL;
	throw ConsoleMonitorException();
	return false;
}

void ShellParser::logout() {
	if (this->loggedin) {
		this->sendCommand("logout");
		this->loggedin = false;
	}
}

}
