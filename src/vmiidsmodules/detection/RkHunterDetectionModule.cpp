/*
 * RkHunterDetectionModule.cpp
 *
 *  Created on: Jul 2, 2010
 *      Author: kittel
 */

#include "RkHunterDetectionModule.h"

#include <fstream>
#include <regex.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <sstream>

#define RKHUNTERSCRIPT "/home/idsvm/workspace/libvmi/src/vmiidsmodules/detection/rkhunterfiles/rkhunter"


#define TEXTNORMAL = 	"\033[0m"
#define TEXTBLACK = 	"\033[0;30m"
#define TEXTRED = 		"\033[0;31m"
#define TEXTGREEN = 	"\033[0;32m"
#define TEXTYELLOW = 	"\033[0;33m"
#define TEXTBLUE = 		"\033[0;34m"
#define TEXTMARGENTA = 	"\033[0;35m"
#define TEXTCYAN =		"\033[0;36m"
#define TEXTWHITE = 	"\033[0;37m"

ADDDYNAMICDETECTIONMODULE(RkHunterDetectionModule, __LINE__)
;

RkHunterDetectionModule::RkHunterDetectionModule() :
	DetectionModule("RkHunterDetectionModule") {
	GETNOTIFICATIONMODULE(notify, ShellNotificationModule);

	GETSENSORMODULE(this->qemu, QemuMonitorSensorModule);
	GETSENSORMODULE(this->shell, ShellSensorModule);
	GETSENSORMODULE(this->fs, FileSystemSensorModule);

	this->initializeVariables();
}

RkHunterDetectionModule::~RkHunterDetectionModule() {

}
void RkHunterDetectionModule::initializeVariables() {

	std::ifstream fileHandle(RKHUNTERSCRIPT, std::ifstream::in);
	std::string currentLine;

	std::string currentVariableName;
	std::string currentVariableContent;

	bool lineInteresting = false;

	size_t result;
	regex_t rxReturn;
	regex_t rxDoSystemCheck;
	regex_t rxEmptyLine;
	regex_t rxCommentLine;
	regex_t rxFirstLine;
	regex_t rxVariables;
	regmatch_t matches[100];

	result = regcomp(&rxReturn, "[:space:]*return", REG_EXTENDED );
	result = regcomp(&rxDoSystemCheck, "^do_system_check_initialisation().*$",
			REG_EXTENDED );
	result = regcomp(&rxEmptyLine, "^[:space:]*$", REG_EXTENDED );
	result = regcomp(&rxCommentLine, "([:space:]|\t)+#", REG_EXTENDED );
	result = regcomp(&rxFirstLine, "\\s*(\\w*)=(.*)", REG_EXTENDED );
	result = regcomp(&rxVariables,
			"\\$\\{(\\w*)\\}\\s*\\$\\{(\\w*)\\}\\s*\\$\\{(\\w*)\\}\\s*",
			REG_EXTENDED );

	while (std::getline(fileHandle, currentLine)) {

		memset(matches, 0, sizeof(matches));
		if (lineInteresting) {
			if (regexec(&rxReturn, currentLine.c_str(), 0, 0, 0) == 0) {
				lineInteresting = false;
				continue;
			}

			if (regexec(&rxEmptyLine, currentLine.c_str(), 0, 0, 0) == 0
					|| regexec(&rxCommentLine, currentLine.c_str(), 0, 0, 0)
							== 0) {
				if (!currentVariableName.empty()) {
					currentVariableName.clear();
				}
				continue;
			}

			result = currentLine.find("${RKHROOTDIR}");
			if (result != std::string::npos) {
				currentLine.replace(result, 13, "");
			}

			if (regexec(&rxFirstLine, currentLine.c_str(), 5, matches, 0) == 0) {
				currentVariableName = currentLine.substr(matches[1].rm_so,
						matches[1].rm_eo - matches[1].rm_so);
				currentVariableContent = currentLine.substr(matches[2].rm_so,
						matches[2].rm_eo - matches[2].rm_so);
				memset(matches, 0, sizeof(matches));
				if (currentVariableContent[0] == '"')
					currentVariableContent.replace(0, 1, "");
				if (currentVariableContent[currentVariableContent.size() - 1]
						== '"')
					currentVariableContent.replace(
							currentVariableContent.size() - 1, 1, "");
				while ((result = currentVariableContent.find("\n"))
						!= std::string::npos) {
					currentVariableContent.replace(result, 1, "");
				}
				if (currentVariableContent.empty()) {
					currentVariableName.clear();
					continue;
				}
				if (regexec(&rxVariables, currentLine.c_str(), 10, matches, 0)
						== 0) {
					for (size_t i = 0; i <= rxVariables.re_nsub; i++) {
						if (matches[i].rm_so != -1) {
							std::multimap<std::string, std::string>::iterator
									it;
							std::pair<
									std::multimap<std::string, std::string>::iterator,
									std::multimap<std::string, std::string>::iterator>
									ret;
							std::string currentVar = currentLine.substr(
									matches[i].rm_so, matches[i].rm_eo
											- matches[i].rm_so);
							ret = this->rkvars.equal_range(currentVar);
							for (it = ret.first; it != ret.second; ++it)
								this->rkvars.insert(std::pair<std::string,
										std::string>(currentVariableName,
										(*it).second));
						}
					}
				} else {
					this->rkvars.insert(std::pair<std::string, std::string>(
							currentVariableName, currentVariableContent));
				}
			} else if (!currentVariableName.empty()) {
				currentVariableContent = currentLine;
				while (currentVariableContent[0] == '\t'
						|| currentVariableContent[0] == ' ')
					currentVariableContent.replace(0, 1, "");
				while (currentVariableContent[currentVariableContent.size() - 1]
						== ' ')
					currentVariableContent.replace(
							currentVariableContent.size() - 1, 1, "");
				for (size_t i = 0; i < currentVariableContent.size(); i++) {
					if (currentVariableContent[i] == '\\') {
						currentVariableContent.replace(i, 1, "\\\\");
						i++;
					}
				}
				if (currentVariableContent[currentVariableContent.size() - 1]
						== '"')
					currentVariableContent.replace(
							currentVariableContent.size() - 1, 1, "");
				if (regexec(&rxVariables, currentLine.c_str(), 10, matches, 0)
						== 0) {
					for (size_t i = 0; i <= rxVariables.re_nsub; i++) {
						if (matches[i].rm_so != -1) {
							std::multimap<std::string, std::string>::iterator
									it;
							std::pair<
									std::multimap<std::string, std::string>::iterator,
									std::multimap<std::string, std::string>::iterator>
									ret;
							std::string currentVar = currentLine.substr(
									matches[i].rm_so, matches[i].rm_eo
											- matches[i].rm_so);
							ret = this->rkvars.equal_range(currentVar);
							for (it = ret.first; it != ret.second; ++it)
								this->rkvars.insert(std::pair<std::string,
										std::string>(currentVariableName,
										(*it).second));
						}
					}
				} else {
					this->rkvars.insert(std::pair<std::string, std::string>(
							currentVariableName, currentVariableContent));
				}
			} else {
				exit(0);
			}
		} else {
			if (regexec(&rxDoSystemCheck, currentLine.c_str(), 0, 0, 0) == 0) {
				lineInteresting = true;
			}
		}
	}

	regfree(&rxReturn);
	regfree(&rxDoSystemCheck);
	regfree(&rxEmptyLine);
	regfree(&rxCommentLine);
	regfree(&rxFirstLine);
	regfree(&rxVariables);

	fileHandle.close();

	return;
}

void RkHunterDetectionModule::run() {

	bool isRunning;
	try {
		isRunning = this->qemu->isRunning();
	} catch (vmi::ModuleException e) {
		notify->critical(this, "Could not use QemuMonitorSensorModule");
		return;
	}

	if (!isRunning) {
		this->qemu->resumeVM();
	}

	notify->info(this, "[ VMIIDS Rootkit Hunter version 0.0.foo ]");
	notify->info(this, "");

	notify->info(this, "Checking system commands...");
	this->performStringCommandCheck();
	this->performSharedLibrariesCheck();
	this->performFilePropertiesCheck();
	notify->info(this, "Checking for rootkits...");
	this->performKnownRootkitCheck();
	this->performAdditionalRootkitCheck();
	this->performMalwareCheck();
	this->performTrojanSpecificCheck();
	this->performLinuxSpecificCheck();
	notify->info(this, "Checking the network...");
	this->performBackdoorCheck();
	this->performNetworkInterfacesCheck();
	notify->info(this, "Checking the local host...");
	this->performSystemBootCheck();
	this->performGroupAndAccountCheck();
	this->performSystemConfigurationCheck();
	this->performFileSystemCheck();
	notify->info(this, "Checking application versions...");
	this->performApplicationVersionsCheck();

	/*
	 System checks summary
	 =====================

	 File properties checks...
	 Files checked: 135
	 Suspect files: 4

	 Rootkit checks...
	 Rootkits checked : 248
	 Possible rootkits: 5
	 Rootkit names    : Xzibit Rootkit, Xzibit Rootkit, Xzibit Rootkit, Xzibit Rootkit, Xzibit Rootkit

	 Applications checks...
	 Applications checked: 5
	 Suspect applications: 0

	 The system checks took: 57 seconds

	 All results have been written to the log file (/home/kittel/Download/rkhunter-1.3.6/files/rkhunter.log)

	 One or more warnings have been found while checking the system.
	 Please check the log file (/home/kittel/Download/rkhunter-1.3.6/files/rkhunter.log)
	 */

}

void RkHunterDetectionModule::runTime() {

}

void RkHunterDetectionModule::runEvent() {

}

void RkHunterDetectionModule::getThreadLevel() {

}

void RkHunterDetectionModule::performStringCommandCheck() {
	notify->info(this, "\t Performing 'strings' command checks");

	bool stringsFailed = false;
	std::string commandOutput;
	std::stringstream command;

	std::multimap<std::string, std::string>::iterator
			it;
	std::pair<
			std::multimap<std::string, std::string>::iterator,
			std::multimap<std::string, std::string>::iterator>
			ret;
	ret = this->rkvars.equal_range(std::string("STRINGS_INTEGRITY"));
	for (it = ret.first; it != ret.second; ++it){
		command.str("");
		commandOutput.clear();
		command << "echo " << (*it).second << " | strings | grep " << (*it).second << " | tr -d ' '";

		this->shell->parseCommandOutput(command.str(), commandOutput);

		if(commandOutput.find((*it).second) == std::string::npos) stringsFailed = true;
	}
	if(!stringsFailed){
		notify->info(this, "\t\tChecking 'strings' command [ OK ]");
	}else{
		notify->warn(this, "\t\tChecking 'strings' command [ Warning ]");
	}
}
void RkHunterDetectionModule::performSharedLibrariesCheck() {
	notify->info(this, "\t Performing 'shared libraries' checks");

	//
	// First check for preloading exported variables.
	//

	bool varFound = false;
	std::string commandOutput;
	std::stringstream command;
	std::list<std::string> variablesToCheck;

	variablesToCheck.push_back("LD_PRELOAD");
	variablesToCheck.push_back("LD_AOUT_PRELOAD");
	variablesToCheck.push_back("LD_ELF_PRELOAD");

	size_t crString;
	while (!variablesToCheck.empty()) {
		command.str("");
		commandOutput.clear();
		command << "eval echo \"\\$" << variablesToCheck.front() << "\"";

		this->shell->parseCommandOutput(command.str(), commandOutput);
		while((crString = commandOutput.rfind("\n")) != std::string::npos) commandOutput.replace(crString, 1, "");
		if(commandOutput.size() > 2) {
			notify->warn(this, commandOutput.c_str());
			varFound = true;
		}
		variablesToCheck.pop_front();
	}
	if(!varFound){
		notify->info(this, "\t\tChecking for preloading variables [ None Found ]");
	}else{
		notify->warn(this, "\t\tChecking for preloading variables [ Warning ]");
	}

	//
	// Next check for a preload file.
	//


	if(this->fs->fileExists("/etc/ld.so.preload"), NULL){

		notify->info(this, "\t\tFound library preload file: /etc/ld.so.preload");

		//TODO Add shared libraries whitelist

		std::ifstream fileHandle;
		this->fs->openFileRO("/etc/ld.so.preload", &fileHandle);
		std::string line;
		while (std::getline(fileHandle, line)){
			notify->warn(this, line.insert(0, "\t\t Found preloaded shared library"));
			//TODO check if shared library is whitelisted!
			notify->info(this, "\t\t TODO check if it is whitelisted!");
		}
		fileHandle.close();
	} else {
		notify->info(this, "\t\tChecking for preloaded libraries [ None Found ]");
	}

	//
	// Finally we check the LD_LIBRARY_PATH. This check may be
	// disabled by the user if the 'ldd' command is not available.
	//

	/*
	 Checking LD_LIBRARY_PATH variable[24C[ [0;32mNot found[0;39m ]
	 */

	notify->info(this, "\t\tChecking LD_LIBRARY_PATH variable [ Not Implemented ]");

	/*
	if `check_test shared_libs_path`; then
		display --to LOG --type INFO STARTING_TEST shared_libs_path

		if [ -n "${LDD_CMD}" ]; then
			if [ -n "${LD_LIBRARY_PATH}" ]; then
				LD_LIBR_FAILED=0
				RKHTMPVAR_BIN=""
				LD_LIBRARY_PATH_SAVED="${LD_LIBRARY_PATH}"

				if [ -z "${MD5_CMD}" ]; then
					MD5_CMD=`find_cmd md5sum`
					test -z "${MD5_CMD}" && MD5_CMD=`find_cmd md5`
				fi

				LS_CMD=`find_cmd ls`

				for RKHTMPVAR in FIND PS STRINGS MD5 LS STAT; do
					RKHTMPVAR=`eval echo "\\$${RKHTMPVAR}_CMD"`
					RKHTMPVAR=`echo "${RKHTMPVAR}" | cut -d' ' -f1`

					RKHTMPVAR_BIN="${RKHTMPVAR_BIN} ${RKHTMPVAR}"
				done

				for RKHTMPVAR in ${RKHTMPVAR_BIN}; do
					LD_LIBRARY_PATH="${LD_LIBRARY_PATH_SAVED}"
					export LD_LIBRARY_PATH
					RKHTMPVAR_WITH=`${LDD_CMD} ${RKHTMPVAR} | sed -e 's/(0x[0-9a-f]*)/0xHEX/' 2>&1`

					unset LD_LIBRARY_PATH
					RKHTMPVAR_WITHOUT=`${LDD_CMD} ${RKHTMPVAR} | sed -e 's/(0x[0-9a-f]*)/0xHEX/' 2>&1`

					if [ "${RKHTMPVAR_WITH}" != "${RKHTMPVAR_WITHOUT}" ]; then
						#
						# Testing one command should be "evidence" enough.
						#

						LD_LIBR_FAILED=1
						break
					fi
				done


				#
				# Reset things to the way they were before.
				#

				LD_LIBRARY_PATH="${LD_LIBRARY_PATH_SAVED}"
				export LD_LIBRARY_PATH


				if [ $LD_LIBR_FAILED -eq 0 ]; then
					display --to SCREEN+LOG --type PLAIN --result OK --color GREEN --screen-indent 4 SHARED_LIBS_PATH
				else
					display --to SCREEN+LOG --type PLAIN --result WARNING --color RED --screen-indent 4 SHARED_LIBS_PATH
					display --to LOG --type WARNING SHARED_LIBS_PATH_BAD "${LD_LIBRARY_PATH}"
				fi
			else
				display --to SCREEN+LOG --type PLAIN --result NOT_FOUND --color GREEN --screen-indent 4 SHARED_LIBS_PATH
			fi
		else
			display --to SCREEN+LOG --type PLAIN --result SKIPPED --color YELLOW --screen-indent 4 SHARED_LIBS_PATH
			display --to LOG --type INFO NOT_FOUND_CMD "ldd"
		fi
	else
		display --to LOG --type INFO USER_DISABLED_TEST shared_libs_path
	fi

	return
	 */
}
void RkHunterDetectionModule::performFilePropertiesCheck() {
	notify->info(this, "\t Performing file properties checks");

	//
	// This function carries out a check of system command property
	// values checked against their previous value, which is stored
	// in the rkhunter.dat file. Other checks work on the current
	// file, and do not use any previously stored value (for example,
	// the immutable-bit check).
	//

	//
	// Each test will set the variable TEST_RESULT, and use it to
	// display the actual result. Typically a null string indicates
	// 'OK', and anything else is a 'Warning'.
	//

	/*
	 Performing file properties checks
	 Checking for prerequisites[31C[ [0;32mOK[0;39m ]
	 /bin/bash[48C[ [0;32mOK[0;39m ]
	 /bin/cat[49C[ [0;32mOK[0;39m ]
	 /bin/chmod[47C[ [0;32mOK[0;39m ]
	 /bin/chown[47C[ [0;32mOK[0;39m ]
	 /bin/cp[50C[ [0;32mOK[0;39m ]
	 /bin/date[48C[ [0;32mOK[0;39m ]
	 /bin/df[50C[ [0;32mOK[0;39m ]
	 /bin/dmesg[47C[ [0;32mOK[0;39m ]
	 /bin/echo[48C[ [0;32mOK[0;39m ]
	 /bin/ed[50C[ [0;32mOK[0;39m ]
	 /bin/egrep[47C[ [0;32mOK[0;39m ]
	 /bin/fgrep[47C[ [0;32mOK[0;39m ]
	 /bin/fuser[47C[ [0;32mOK[0;39m ]
	 /bin/grep[48C[ [0;32mOK[0;39m ]
	 /bin/ip[50C[ [0;32mOK[0;39m ]
	 /bin/kill[48C[ [0;32mOK[0;39m ]
	 /bin/less[48C[ [0;32mOK[0;39m ]
	 /bin/login[47C[ [0;32mOK[0;39m ]
	 /bin/ls[50C[ [0;32mOK[0;39m ]
	 /bin/lsmod[47C[ [0;32mOK[0;39m ]
	 /bin/mktemp[46C[ [0;32mOK[0;39m ]
	 /bin/more[48C[ [0;32mOK[0;39m ]
	 /bin/mount[47C[ [0;32mOK[0;39m ]
	 /bin/mv[50C[ [0;32mOK[0;39m ]
	 /bin/netstat[45C[ [0;32mOK[0;39m ]
	 /bin/ps[50C[ [0;32mOK[0;39m ]
	 /bin/pwd[49C[ [0;32mOK[0;39m ]
	 /bin/readlink[44C[ [0;32mOK[0;39m ]
	 /bin/sed[49C[ [0;32mOK[0;39m ]
	 /bin/sh[50C[ [0;32mOK[0;39m ]
	 /bin/su[50C[ [0;32mOK[0;39m ]
	 /bin/touch[47C[ [0;32mOK[0;39m ]
	 /bin/uname[47C[ [0;32mOK[0;39m ]
	 /bin/which[47C[ [1;31mWarning[0;39m ]
	 /bin/dash[48C[ [0;32mOK[0;39m ]
	 /usr/bin/awk[45C[ [0;32mOK[0;39m ]
	 /usr/bin/basename[40C[ [0;32mOK[0;39m ]
	 /usr/bin/chattr[42C[ [0;32mOK[0;39m ]
	 /usr/bin/cut[45C[ [0;32mOK[0;39m ]
	 /usr/bin/diff[44C[ [0;32mOK[0;39m ]
	 /usr/bin/dirname[41C[ [0;32mOK[0;39m ]
	 /usr/bin/dpkg[44C[ [0;32mOK[0;39m ]
	 /usr/bin/dpkg-query[38C[ [0;32mOK[0;39m ]
	 /usr/bin/du[46C[ [0;32mOK[0;39m ]
	 /usr/bin/env[45C[ [0;32mOK[0;39m ]
	 /usr/bin/file[44C[ [0;32mOK[0;39m ]
	 /usr/bin/find[44C[ [0;32mOK[0;39m ]
	 /usr/bin/GET[45C[ [0;32mOK[0;39m ]
	 /usr/bin/groups[42C[ [0;32mOK[0;39m ]
	 /usr/bin/head[44C[ [0;32mOK[0;39m ]
	 /usr/bin/id[46C[ [0;32mOK[0;39m ]
	 /usr/bin/killall[41C[ [0;32mOK[0;39m ]
	 /usr/bin/last[44C[ [0;32mOK[0;39m ]
	 /usr/bin/lastlog[41C[ [0;32mOK[0;39m ]
	 /usr/bin/ldd[45C[ [1;31mWarning[0;39m ]
	 /usr/bin/less[44C[ [0;32mOK[0;39m ]
	 /usr/bin/locate[42C[ [0;32mOK[0;39m ]
	 /usr/bin/logger[42C[ [0;32mOK[0;39m ]
	 /usr/bin/lsattr[42C[ [0;32mOK[0;39m ]
	 /usr/bin/lsof[44C[ [0;32mOK[0;39m ]
	 /usr/bin/mail[44C[ [0;32mOK[0;39m ]
	 /usr/bin/md5sum[42C[ [0;32mOK[0;39m ]
	 /usr/bin/mlocate[41C[ [0;32mOK[0;39m ]
	 /usr/bin/newgrp[42C[ [0;32mOK[0;39m ]
	 /usr/bin/passwd[42C[ [0;32mOK[0;39m ]
	 /usr/bin/perl[44C[ [0;32mOK[0;39m ]
	 /usr/bin/pgrep[43C[ [0;32mOK[0;39m ]
	 /usr/bin/pstree[42C[ [0;32mOK[0;39m ]
	 /usr/bin/rkhunter[40C[ [0;32mOK[0;39m ]
	 /usr/bin/runcon[42C[ [0;32mOK[0;39m ]
	 /usr/bin/sha1sum[41C[ [0;32mOK[0;39m ]
	 /usr/bin/sha224sum[39C[ [0;32mOK[0;39m ]
	 /usr/bin/sha256sum[39C[ [0;32mOK[0;39m ]
	 /usr/bin/sha384sum[39C[ [0;32mOK[0;39m ]
	 /usr/bin/sha512sum[39C[ [0;32mOK[0;39m ]
	 /usr/bin/size[44C[ [0;32mOK[0;39m ]
	 /usr/bin/sort[44C[ [0;32mOK[0;39m ]
	 /usr/bin/stat[44C[ [0;32mOK[0;39m ]
	 /usr/bin/strace[42C[ [0;32mOK[0;39m ]
	 /usr/bin/strings[41C[ [0;32mOK[0;39m ]
	 /usr/bin/sudo[44C[ [0;32mOK[0;39m ]
	 /usr/bin/tail[44C[ [0;32mOK[0;39m ]
	 /usr/bin/test[44C[ [0;32mOK[0;39m ]
	 /usr/bin/top[45C[ [0;32mOK[0;39m ]
	 /usr/bin/touch[43C[ [0;32mOK[0;39m ]
	 /usr/bin/tr[46C[ [0;32mOK[0;39m ]
	 /usr/bin/uniq[44C[ [0;32mOK[0;39m ]
	 /usr/bin/users[43C[ [0;32mOK[0;39m ]
	 /usr/bin/vmstat[42C[ [0;32mOK[0;39m ]
	 /usr/bin/w[47C[ [0;32mOK[0;39m ]
	 /usr/bin/watch[43C[ [0;32mOK[0;39m ]
	 /usr/bin/wc[46C[ [0;32mOK[0;39m ]
	 /usr/bin/wget[44C[ [0;32mOK[0;39m ]
	 /usr/bin/whatis[42C[ [0;32mOK[0;39m ]
	 /usr/bin/whereis[41C[ [0;32mOK[0;39m ]
	 /usr/bin/which[43C[ [0;32mOK[0;39m ]
	 /usr/bin/who[45C[ [0;32mOK[0;39m ]
	 /usr/bin/whoami[42C[ [0;32mOK[0;39m ]
	 /usr/bin/mawk[44C[ [0;32mOK[0;39m ]
	 /usr/bin/lwp-request[37C[ [1;31mWarning[0;39m ]
	 /usr/bin/bsd-mailx[39C[ [0;32mOK[0;39m ]
	 /usr/bin/w.procps[40C[ [0;32mOK[0;39m ]
	 /sbin/depmod[45C[ [0;32mOK[0;39m ]
	 /sbin/ifconfig[43C[ [0;32mOK[0;39m ]
	 /sbin/ifdown[45C[ [0;32mOK[0;39m ]
	 /sbin/ifup[47C[ [0;32mOK[0;39m ]
	 /sbin/init[47C[ [0;32mOK[0;39m ]
	 /sbin/insmod[45C[ [0;32mOK[0;39m ]
	 /sbin/ip[49C[ [0;32mOK[0;39m ]
	 /sbin/lsmod[46C[ [0;32mOK[0;39m ]
	 /sbin/modinfo[44C[ [0;32mOK[0;39m ]
	 /sbin/modprobe[43C[ [0;32mOK[0;39m ]
	 /sbin/rmmod[46C[ [0;32mOK[0;39m ]
	 /sbin/runlevel[43C[ [0;32mOK[0;39m ]
	 /sbin/sulogin[44C[ [0;32mOK[0;39m ]
	 /sbin/sysctl[45C[ [0;32mOK[0;39m ]
	 /usr/sbin/adduser[40C[ [1;31mWarning[0;39m ]
	 /usr/sbin/chroot[41C[ [0;32mOK[0;39m ]
	 /usr/sbin/cron[43C[ [0;32mOK[0;39m ]
	 /usr/sbin/groupadd[39C[ [0;32mOK[0;39m ]
	 /usr/sbin/groupdel[39C[ [0;32mOK[0;39m ]
	 /usr/sbin/groupmod[39C[ [0;32mOK[0;39m ]
	 /usr/sbin/grpck[42C[ [0;32mOK[0;39m ]
	 /usr/sbin/inetd[42C[ [0;32mOK[0;39m ]
	 /usr/sbin/nologin[40C[ [0;32mOK[0;39m ]
	 /usr/sbin/pwck[43C[ [0;32mOK[0;39m ]
	 /usr/sbin/rsyslogd[39C[ [0;32mOK[0;39m ]
	 /usr/sbin/tcpd[43C[ [0;32mOK[0;39m ]
	 /usr/sbin/useradd[40C[ [0;32mOK[0;39m ]
	 /usr/sbin/userdel[40C[ [0;32mOK[0;39m ]
	 /usr/sbin/usermod[40C[ [0;32mOK[0;39m ]
	 /usr/sbin/vipw[43C[ [0;32mOK[0;39m ]
	 /usr/sbin/unhide-linux26[33C[ [0;32mOK[0;39m ]
	 /home/kittel/Download/rkhunter-1.3.6/files/rkhunter[6C[ [0;32mOK[0;39m ]
	 /home/kittel/Download/rkhunter-1.3.6/files/rkhunter.conf[1C[ [0;32mOK[0;39m ]
	 */

/*	bool testResult;
	bool whitelistResult;
	bool skipAttr, skipHash, skipImmut, skipScript;
	bool useDatFile = true;
	bool skiptImmutOS = false;
	int propFileListCount = 0;
*/
	/*

	#
	# The first test we do is on the commands needed to
	# perform all the file checks. If the user has not
	# disabled any test, and a command is missing, then
	# we must let them know that without marking each file
	# test as a 'Warning' (because that could hide a real
	# problem). We include checks on the rkhunter.dat file
	# as well.
	#

	RKHTMPVAR=""

	if [ $SKIP_HASH -eq 0 ]; then
		# Not sure about this one...!
		if [ -z "${OLD_PKGMGR}" -a -s ${RKHDAT_FILE} -a "${HASH_FUNC}" != "NONE" -a \( "${OLD_HASH_FUNC}" = "NONE" -o "${OLD_HASH_FUNC}" = "Disabled" -o -z "${OLD_HASH_FUNC}" \) ]; then
			SKIP_HASH=1
			RKHTMPVAR="${RKHTMPVAR} hash"

			if [ -n "${PRELINK_HASH}" ]; then
				HASH_FUNC_ERR="prelink with ${PRELINK_HASH}"
			else
				HASH_FUNC_ERR="${HASH_FUNC}"
			fi

			if [ -z "${OLD_HASH_FUNC}" ]; then
				OLD_HASH_FUNC_ERR="Unset"
			else
				if [ "${OLD_HASH_FUNC}" = "MD5" -o "${OLD_HASH_FUNC}" = "SHA1" ]; then
					OLD_HASH_FUNC_ERR="prelink with ${OLD_HASH_FUNC}"
				else
					OLD_HASH_FUNC_ERR="${OLD_HASH_FUNC}"
				fi
			fi

			if [ -z "${PKGMGR}" ]; then
				PKGMGR_ERR="Unset"
			else
				PKGMGR_ERR="${PKGMGR}"
			fi

			if [ -z "${OLD_PKGMGR}" ]; then
				OLD_PKGMGR_ERR="Unset"
			else
				OLD_PKGMGR_ERR="${OLD_PKGMGR}"
			fi
		fi

		if [ $PRELINKED -eq 1 ]; then
			case $SKIP_HASH_MSG in
			1)
				SKIP_HASH=1
				RKHTMPVAR="${RKHTMPVAR} prelink"
				;;
			2)
				SKIP_HASH=1
				RKHTMPVAR="${RKHTMPVAR} sha1"
				;;
			3)
				SKIP_HASH=1
				RKHTMPVAR="${RKHTMPVAR} libsafe"
				;;
			esac
		fi
	fi

	if [ $SKIP_IMMUT -eq 0 ]; then
		if [ $BSDOS -eq 1 ]; then
			if [ -z "`ls -lno ${CONFIGFILE} 2>/dev/null`" ]; then
				SKIP_IMMUT=1
				RKHTMPVAR="${RKHTMPVAR} immutable-bsd"
			fi
		else
			if [ -z "${LSATTR_CMD}" ]; then
				SKIP_IMMUT=1
				RKHTMPVAR="${RKHTMPVAR} immutable"
			elif [ -z "`${LSATTR_CMD} ${CONFIGFILE} 2>/dev/null`" ]; then
				SKIP_IMMUT=1
				RKHTMPVAR="${RKHTMPVAR} immutable-cmd"
			fi
		fi
	fi

	if [ $SKIP_SCRIPT -eq 0 ]; then
		if [ -z "${FILE_CMD}" ]; then
			SKIP_SCRIPT=1
			RKHTMPVAR="${RKHTMPVAR} script"
		elif [ -z "`${FILE_CMD} ${CONFIGFILE} 2>/dev/null`" ]; then
			SKIP_SCRIPT=1
			RKHTMPVAR="${RKHTMPVAR} script-cmd"
		fi
	fi

	if [ $SKIP_ATTR -eq 0 -o $SKIP_HASH -eq 0 ]; then
		if [ ! -f ${RKHDAT_FILE} ]; then
			SKIP_HASH=1
			SKIP_ATTR=1
			USE_DAT_FILE=0
			RKHTMPVAR="${RKHTMPVAR} missing"
		fi

		if [ $USE_DAT_FILE -eq 1 -a ! -s ${RKHDAT_FILE} ]; then
			SKIP_HASH=1
			SKIP_ATTR=1
			USE_DAT_FILE=0
			RKHTMPVAR="${RKHTMPVAR} empty"
		fi
	else
		#
		# If we are not checking the file attributes or
		# the hash value, then we don't need to look at
		# the rkhunter.dat file. The other tests can be
		# done without the file.
		#

		USE_DAT_FILE=0
	fi

	#
	# If the O/S has changed in some way, and we are not just reporting warnings,
	# and O/S warnings are enabled, then show a warning in the prerequisites test.
	#

	if [ $OS_CHANGED -eq 1 -a $SHOWWARNINGSONLY -eq 0 -a $WARN_ON_OS_CHANGE -eq 1 ]; then
		RKHTMPVAR="${RKHTMPVAR} os_changed"
	fi

	#
	# If all the previous checks have disabled all the tests,
	# then we tell the user and then return.
	#

	if [ $SKIP_ATTR -eq 1 -a $SKIP_HASH -eq 1 -a $SKIP_IMMUT -eq 1 -a $SKIP_SCRIPT -eq 1 ]; then
		RKHTMPVAR="${RKHTMPVAR} notests"
	fi


	#
	# Display the results.
	#

	if [ $SKIP_IMMUT_OS -eq 1 ]; then
		display --to LOG --type INFO FILE_PROP_IMMUT_OS
	fi

	if [ -z "${RKHTMPVAR}" ]; then
		display --to SCREEN+LOG --type PLAIN --screen-indent 4 --result OK --color GREEN FILE_PROP_CMDS
	else
		SUMMARY_PROP_REQCMDS=1

		display --to SCREEN+LOG --type WARNING --screen-indent 4 --result WARNING --color RED FILE_PROP_CMDS


		RKHTMPVAR2=0
		for TEST_RESULT in ${RKHTMPVAR}; do
			case "${TEST_RESULT}" in
			attr)
				display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SKIP_ATTR
				;;
			hash|prelink|sha1|libsafe)
				if [ $RKHTMPVAR2 -eq 0 ]; then
					RKHTMPVAR2=1
					display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SKIP_HASH
				fi

				case "${TEST_RESULT}" in
				hash)
					display --to LOG --type PLAIN --log-indent 13 FILE_PROP_SKIP_HASH_FUNC "${HASH_FUNC_ERR}" "${PKGMGR_ERR}" "${OLD_HASH_FUNC_ERR}" "${OLD_PKGMGR_ERR}"
					;;
				prelink)
					display --to LOG --type PLAIN --log-indent 13 FILE_PROP_SKIP_HASH_PRELINK
					;;
				sha1)
					display --to LOG --type PLAIN --log-indent 13 FILE_PROP_SKIP_HASH_SHA1
					;;
				libsafe)
					display --to LOG --type PLAIN --log-indent 13 FILE_PROP_SKIP_HASH_LIBSAFE
					;;
				esac
				;;
			immutable)
				display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SKIP_IMMUT
				;;
			immutable-bsd)
				display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SKIP_IMMUT_CMD "ls -lno"
				;;
			immutable-cmd)
				display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SKIP_IMMUT_CMD "lsattr"
				;;
			script)
				display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SKIP_SCRIPT
				;;
			script-cmd)
				display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SKIP_FILE_CMD
				;;
			os_changed)
				display --to LOG --type PLAIN --log-indent 9 FILE_PROP_OS_CHANGED
				;;
			missing)
				display --to LOG --type PLAIN --log-indent 9 FILE_PROP_DAT_MISSING
				display --to LOG --type INFO FILE_PROP_DAT_MISSING_INFO
				;;
			empty)
				display --to LOG --type PLAIN --log-indent 9 FILE_PROP_DAT_EMPTY
				display --to LOG --type INFO FILE_PROP_DAT_MISSING_INFO
				;;
			esac
		done


		if [ -n "`echo \"${RKHTMPVAR}\" | egrep 'libsafe|missing|empty'`" ]; then
			display --to LOG --type WARNING --nl PROPUPD_WARN
		fi

		if [ -n "`echo \"${RKHTMPVAR}\" | grep 'notests'`" ]; then
			display --to LOG --type WARNING --nl FILE_PROP_SKIP_ALL
			return
		fi
	fi


	#
	# Set up some local variables depending on what
	# commands we have available.
	#

	if [ $SKIP_ATTR -eq 1 ]; then
		SCMD=""
		INODECMD=""
	else
		if [ -n "`echo \"${STAT_CMD}\" | grep '\.pl$'`" ]; then
			SCMD="${STAT_CMD} --modeoct --raw --ino --mode --uid --gid --size --Mtime"
			INODECMD="${STAT_CMD} --modeoct --raw --ino"
		elif [ $BSDOS -eq 1 ]; then
			SCMD="${STAT_CMD} -f '%i %Mp%Lp %u %g %z %m:'"
			INODECMD="${STAT_CMD} -f '%i'"
		else
			SCMD="${STAT_CMD} -c '%i 0%a %u %g %s %Y:'"
			INODECMD="${STAT_CMD} -c '%i'"
		fi
	fi

	if [ $SKIP_HASH -eq 1 ]; then
		HCMD=""
		SYSHASH=""
	else
		HCMD="${HASH_FUNC}"
	fi

	RDIR=`echo "${RKHROOTDIR}" | sed -e 's/\//\\\\\//g'`


	#
	# Set up some whitelist variables. There is no point
	# recalculating the (static) whitelist as we look at
	# each file. We may as well just do it the once here.
	#

	if [ $SKIP_ATTR -eq 0 ]; then
		ATTRWHITELIST=`get_option 1 multi ATTRWHITELIST` || exit 1
		WRITEWHITELIST=`get_option 1 multi WRITEWHITELIST` || exit 1
	fi

	if [ $SKIP_IMMUT -eq 0 ]; then
		IMMUTWHITELIST=`get_option 1 multi IMMUTWHITELIST` || exit 1
	fi

	if [ $SKIP_SCRIPT -eq 0 ]; then
		SCRIPTWHITELIST=`get_option 1 multi SCRIPTWHITELIST` || exit 1
	fi


	#
	# Next we have to recreate the list of pathnames for the
	# file properties checks. We need to recreate it because
	# the root PATH may have changed, and so there may be more
	# directories to be checked. However, if we have just run
	# the '--propupd' option, then we can skip this.
	#

	test $PROP_UPDATE -eq 0 && create_rkh_file_prop_list


	#
	# Now loop through each of the files and
	# perform the tests on each one.
	#

	VERIFIED_PKG_LIST=""

	for FNAME in `cat ${RKH_FILEPROP_LIST}`; do
		FNAMEGREP=""
		TEST_RESULT=""
		WHITELIST_RESULT=""

		NOVRFYFILE=0
		FILE_IS_PKGD=0
		DEPENDENCY_ERR=0
		HASH_TEST_PASSED=0
		SIZE_TEST_PASSED=0


		#
		# We first need to test if the file exists or not,
		# and if the file is listed in the rkhunter.dat
		# file or not. This can indicate files that have
		# appeared on or disappeared from the system.
		#

		if [ -f "${FNAME}" ]; then
			FILE_EXISTS=1
			PROP_FILE_LIST_COUNT=`expr ${PROP_FILE_LIST_COUNT} + 1`
		else
			FILE_EXISTS=0
		fi

		if [ $USE_DAT_FILE -eq 1 ]; then
			#
			# When checking the filename against the rkhunter.dat
			# file, we must use the real filename and not one with
			# the root directory.
			#

			FILENAME=`echo "${FNAME}" | sed -e "s:^${RDIR}::"`

			FNAMEGREP=`echo "${FILENAME}" | sed -e 's/\([.[]\)/\\\\\1/g'`

			RKHLINE=`grep "^File:${FNAMEGREP}:" ${RKHDAT_FILE}`

			if [ $FILE_EXISTS -eq 1 -a -z "${RKHLINE}" ]; then
				TEST_RESULT="${TEST_RESULT} norkhline"
			elif [ $FILE_EXISTS -eq 0 ]; then
				if [ -n "${RKHLINE}" ]; then
					PROP_FAILED_COUNT=`expr ${PROP_FAILED_COUNT} + 1`

					display --to SCREEN+LOG --type PLAIN --screen-indent 4 --result WARNING --color RED NAME "${FNAME}"
					display --to LOG --type WARNING FILE_PROP_FILE_NOT_EXIST "${FNAME}"
				fi

				continue
			fi
		elif [ $FILE_EXISTS -eq 1 ]; then
			RKHLINE=""
			FNAMEGREP=`echo "${FNAME}" | sed -e 's/\([.[]\)/\\\\\1/g'`
		else
			continue
		fi


		#
		# Start the tests.
		#

		if [ $USE_DAT_FILE -eq 1 -a -n "${RKHLINE}" ]; then
			FDATA=""
			RPM_QUERY_RESULT=""
			PKGMGR_VERIFY_RESULT=""

			#
			# See if the file is to be exempt from any package manager verification.
			#

			if [ -n "`echo \"${PKGMGRNOVRFY}\" | grep \" ${FNAMEGREP} \"`" ]; then
				NOVRFYFILE=1
			fi


			#
			# Because the RPM package manager can verify most
			# of the tests we are doing, we obtain the verified
			# data now. The other package managers, at present,
			# only provide the MD5 checksum. As such we simply
			# handle them within the hash test.
			#

			if [ "${PKGMGR}" = "RPM" ]; then
				#
				# First we see if the file is exempt or part of a package.
				#

				if [ $NOVRFYFILE -eq 1 ]; then
					ERRCODE=1
				else
					PKGNAME_ARCH=`${RPM_CMD} -qf ${FILENAME} --queryformat '%{N}-%{V}-%{R}.%{ARCH}\n' 2>/dev/null`
					ERRCODE=$?
				fi

				if [ $ERRCODE -eq 0 ]; then
					#
					# Okay we have a package name. Is it in the list
					# of packages we have already tested as verified?
					#
					# If multiple packages claim the same file, we use
					# 64-bit over 32-bit, or simply the last one.
					#

					FILE_IS_PKGD=1

					PKGNAME=`echo "${PKGNAME_ARCH}" | egrep '\.(x86_64|ia64)$' | tail -1`

					test -z "${PKGNAME}" && PKGNAME=`echo "${PKGNAME_ARCH}" | tail -1`

					RKHTMPVAR=`echo "${PKGNAME}" | sed -e 's/\./\\\./g'`

					if [ -z "`echo \"${VERIFIED_PKG_LIST}\" | grep \" ${RKHTMPVAR} \"`" ]; then
						#
						# No, it isn't in the list. So we verify the package
						# and either add it to the list if it verifies okay,
						# or get the verification result for the file.
						#

						PKGMGR_VERIFY_RESULT=`${RPM_CMD} -V "${PKGNAME}" 2>&1`

						if [ -z "${PKGMGR_VERIFY_RESULT}" ]; then
							VERIFIED_PKG_LIST="${VERIFIED_PKG_LIST} ${PKGNAME} "
						else
							if [ -n "`echo \"${PKGMGR_VERIFY_RESULT}\" | grep \"prelink.* ${FILENAME}.* dependenc\"`" ]; then
								DEPENDENCY_ERR=1
							fi

							PKGMGR_VERIFY_RESULT=`echo "${PKGMGR_VERIFY_RESULT}" | grep " ${FNAMEGREP}\$" | cut -d' ' -f1`
						fi
					fi


					#
					# The package manager check does not verify all the items
					# we check. So we still need to dig out the rest of the
					# information about this file from the package manager database.
					#

					RPM_QUERY_RESULT=`${RPM_CMD} -q --queryformat '[%{FILEMODES:octal}:%{FILEUSERNAME}:%{FILEGROUPNAME}:%{FILESIZES}:%{FILEMTIMES}:%{FILEMD5S}:%{FILENAMES}\n]' "${PKGNAME}" 2>/dev/null | grep ":${FNAMEGREP}\$"`
					ERRCODE=$?

					if [ $ERRCODE -eq 0 ]; then
						RPM_QUERY_RESULT=`echo "${RPM_QUERY_RESULT}" | tail -1`

						FPERM="0`echo \"${RPM_QUERY_RESULT}\" | cut -d: -f1 | cut -c 3-`"
						FPERM=`echo "${FPERM}" | sed -e 's/^00/0/'`

						RKHUID=`echo "${RPM_QUERY_RESULT}" | cut -d: -f2`
						RKHUID=`grep "^${RKHUID}:" /etc/passwd 2>/dev/null | cut -d: -f3`

						RKHGID=`echo "${RPM_QUERY_RESULT}" | cut -d: -f3`
						RKHGID=`grep "^${RKHGID}:" /etc/group 2>/dev/null | cut -d: -f3`

						RKHSIZE=`echo "${RPM_QUERY_RESULT}" | cut -d: -f4`

						RKHDTM=`echo "${RPM_QUERY_RESULT}" | cut -d: -f5`

						FDATA="${FPERM}:${RKHUID}:${RKHGID}:${RKHSIZE}:${RKHDTM}:"
					else
						#
						# If, for some reason, we cannot get the package information,
						# then treat it as if it returned all null values.
						#

						FDATA=":::::"
						display --to LOG --type INFO CMD_ERROR "rpm -qf --queryformat... ${FILENAME}" $ERRCODE
					fi

					#
					# Now get the inode value directly from the disk,
					# but only if prelinking is not being used.
					#

					RKHTMPVAR=""

					test $PRELINKED -eq 0 && RKHTMPVAR=`eval ${INODECMD} ${FNAME} 2>/dev/null | tr -d ' '`

					FDATA="${RKHTMPVAR}:${FDATA}"
				fi
			fi


			#
			# Do the file hash value check.
			#

			if [ $SKIP_HASH -eq 0 ]; then
				#
				# First we get all the package manager results.
				#

				case "${PKGMGR}" in
				RPM)
					;;
				DPKG)
					#
					# First see if the file is exempt or part of a known package.
					#

					if [ $NOVRFYFILE -eq 1 ]; then
						PKGNAME=""
					else
						PKGNAME=`${DPKG_CMD} --search ${FILENAME} 2>/dev/null | cut -d: -f1`
					fi

					if [ -n "${PKGNAME}" -a -f "/var/lib/dpkg/info/${PKGNAME}.md5sums" ]; then
						FNAMEGREP=`echo "${FNAMEGREP}" | sed -e 's:^/::'`

						SYSHASH=`egrep "( |\./)${FNAMEGREP}\$" /var/lib/dpkg/info/${PKGNAME}.md5sums | cut -d' ' -f1`

						if [ -n "${SYSHASH}" ]; then
							FILE_IS_PKGD=1
							RKHTMPVAR=`${PKGMGR_MD5_HASH} ${FNAME} 2>/dev/null | cut -d' ' -f $HASH_FLD_IDX`

							if [ "${RKHTMPVAR}" != "${SYSHASH}" ]; then
								PKGMGR_VERIFY_RESULT="5"

								if [ -n "`${PKGMGR_MD5_HASH} ${FNAME} 2>&1 | egrep 'prelink.* (dependenc|adjusting unfinished)'`" ]; then
									DEPENDENCY_ERR=1
								fi
							fi
						fi
					fi
					;;
				BSD)
					#
					# First see if the file is exempt or part of a known package.
					#

					if [ $NOVRFYFILE -eq 1 ]; then
						PKGNAME=""
					else
						PKGNAME=`${PKG_CMD} -F -e ${FILENAME} 2>/dev/null`
					fi

					if [ -n "${PKGNAME}" ]; then
						#
						# Next strip of the '/usr/pkg' from the
						# pathname, and then get the hash value.
						#

						FNAMEGREP=`echo "${FNAMEGREP}" | sed -e 's:^/usr/pkg/::'`

						SYSHASH=`${PKG_CMD} -v -L ${PKGNAME} 2>/dev/null | grep -A 1 "File: ${FNAMEGREP}\$" | tail -1 | cut -d: -f3`

						if [ -n "${SYSHASH}" ]; then
							FILE_IS_PKGD=1
							RKHTMPVAR=`${PKGMGR_MD5_HASH} ${FNAME} 2>/dev/null | cut -d' ' -f $HASH_FLD_IDX`

							if [ "${RKHTMPVAR}" != "${SYSHASH}" ]; then
								PKGMGR_VERIFY_RESULT="5"

								if [ -n "`${PKGMGR_MD5_HASH} ${FNAME} 2>&1 | egrep 'prelink.* (dependenc|adjusting unfinished)'`" ]; then
									DEPENDENCY_ERR=1
								fi
							fi
						fi
					fi
					;;
				esac


				#
				# Now see if we need to work out the hash value or not.
				#

				RKHHASH=`echo ${RKHLINE} | cut -d: -f3`

				if [ $FILE_IS_PKGD -eq 1 ]; then
					if [ "${RKHHASH}" = "ignore-prelink-dep-err" ]; then
						if [ $DEPENDENCY_ERR -eq 1 ]; then
							DEPENDENCY_ERR=0
							PKGMGR_VERIFY_RESULT=""
							display --to LOG --type INFO FILE_PROP_IGNORE_PRELINK_DEP_ERR "${FNAME}"
						else
							PKGMGR_VERIFY_RESULT="5"
						fi
					fi

					if [ -z "`echo \"${PKGMGR_VERIFY_RESULT}\" | egrep '5|(^..\?)'`" ]; then
						HASH_TEST_PASSED=1
					else
						TEST_RESULT="${TEST_RESULT} verify:hashchanged"
					fi
				else
					#
					# The file is not part of a package. So we need
					# to compare the on-disk hash value against the
					# value in the rkhunter.dat file.
					#
					# First see if we have a stored hash value.
					#

					test -z "${RKHHASH}" && TEST_RESULT="${TEST_RESULT} norkhhash"

					if [ -z "${TEST_RESULT}" ]; then
						if [ "${HCMD}" = "NONE" ]; then
							SYSHASH=""
						else
							SYSHASH=`${HCMD} ${FNAME} 2>/dev/null | cut -d' ' -f $HASH_FLD_IDX`

							if [ -z "${SYSHASH}" ]; then
								if [ -n "`${HCMD} ${FNAME} 2>&1 | egrep 'prelink.* (dependenc|adjusting unfinished)'`" ]; then
									if [ "${RKHHASH}" = "ignore-prelink-dep-err" ]; then
										SYSHASH="${RKHHASH}"
										display --to LOG --type INFO FILE_PROP_IGNORE_PRELINK_DEP_ERR "${FNAME}"
									else
										DEPENDENCY_ERR=1
									fi
								fi
							fi
						fi

						test "${RKHHASH}" != "${SYSHASH}" && TEST_RESULT="${TEST_RESULT} hashchanged"
					fi
				fi


				#
				# Because the BSD and DPKG package managers only provide the
				# MD5 checksum, we can assume that any file which is part of
				# a package after this test must be an RPM file.
				#

				test "${PKGMGR}" != "RPM" && FILE_IS_PKGD=0
			fi


			#
			# Do the file attributes checks.
			#
			# This checks the files permissions, and the uid/gid.
			# The file permissions are also checked to see if 'w'
			# has been allowed for all users. If prelinking is not
			# in use then the inode, file size, and modification
			# date-time are checked as well.
			#

			if [ $SKIP_ATTR -eq 0 ]; then
				#
				# First check to see if the file is whitelisted here,
				# just the once. It is better than checking after
				# each individual attribute test.
				#

				WL_FILE=""

				for WHITELISTFILE in ${ATTRWHITELIST}; do
					if [ "${RKHROOTDIR}${WHITELISTFILE}" = "${FNAME}" ]; then
						WL_FILE="whitelisted"
						WHITELIST_RESULT="${WHITELIST_RESULT} attr"
						break
					fi
				done

				test -z "${FDATA}" && FDATA=`eval ${SCMD} ${FNAME} 2>/dev/null | tr ' ' ':'`

				if [ -z "${WL_FILE}" -a -n "${FDATA}" ]; then
					#
					# Check the file permissions.
					#

					if [ $FILE_IS_PKGD -eq 1 ]; then
						echo "${PKGMGR_VERIFY_RESULT}" | egrep 'M|(^.\?)' >/dev/null && TEST_RESULT="${TEST_RESULT} verify:permchanged"
					else
						RKHPERM=`echo ${RKHLINE} | cut -d: -f5`
						SYSPERM=`echo ${FDATA} | cut -d: -f2`

						if [ -n "${RKHPERM}" ]; then
							test "${RKHPERM}" != "${SYSPERM}" && TEST_RESULT="${TEST_RESULT} permchanged"
						else
							TEST_RESULT="${TEST_RESULT} norkhperm"
						fi
					fi


					#
					# Check the file user-id.
					#

					if [ $FILE_IS_PKGD -eq 1 ]; then
						echo "${PKGMGR_VERIFY_RESULT}" | egrep 'U|(^.....\?)' >/dev/null && TEST_RESULT="${TEST_RESULT} verify:uidchanged"
					else
						RKHUID=`echo ${RKHLINE} | cut -d: -f6`
						SYSUID=`echo ${FDATA} | cut -d: -f3`

						if [ -n "${RKHUID}" ]; then
							test "${RKHUID}" != "${SYSUID}" && TEST_RESULT="${TEST_RESULT} uidchanged"
						else
							TEST_RESULT="${TEST_RESULT} norkhuid"
						fi
					fi


					#
					# Check the file group-id.
					#

					if [ $FILE_IS_PKGD -eq 1 ]; then
						echo "${PKGMGR_VERIFY_RESULT}" | egrep 'G|(^......\?)' >/dev/null && TEST_RESULT="${TEST_RESULT} verify:gidchanged"
					else
						RKHGID=`echo ${RKHLINE} | cut -d: -f7`
						SYSGID=`echo ${FDATA} | cut -d: -f4`

						if [ -n "${RKHGID}" ]; then
							test "${RKHGID}" != "${SYSGID}" && TEST_RESULT="${TEST_RESULT} gidchanged"
						else
							TEST_RESULT="${TEST_RESULT} norkhgid"
						fi
					fi


					#
					# Check the file inode number.
					#

					if [ $PRELINKED -eq 0 ]; then
						RKHINODE=`echo ${RKHLINE} | cut -d: -f4`
						SYSINODE=`echo ${FDATA} | cut -d: -f1`

						if [ -n "${RKHINODE}" ]; then
							test "${RKHINODE}" != "${SYSINODE}" && TEST_RESULT="${TEST_RESULT} inodechanged"
						else
							TEST_RESULT="${TEST_RESULT} norkhinode"
						fi
					fi


					#
					# Check the file size.
					#

					if [ $FILE_IS_PKGD -eq 1 ]; then
						if [ -z "`echo \"${PKGMGR_VERIFY_RESULT}\" | egrep 'S|(^\?)'`" ]; then
							SIZE_TEST_PASSED=1
						else
							TEST_RESULT="${TEST_RESULT} verify:sizechanged"
						fi
					elif [ $PRELINKED -eq 0 -o $FILE_IS_PKGD -eq 0 ]; then
						RKHSIZE=`echo ${RKHLINE} | cut -d: -f8`
						SYSSIZE=`echo ${FDATA} | cut -d: -f5`

						if [ -n "${RKHSIZE}" ]; then
							if [ "${RKHSIZE}" = "${SYSSIZE}" ]; then
								SIZE_TEST_PASSED=1
							else
								TEST_RESULT="${TEST_RESULT} sizechanged"
							fi
						else
							TEST_RESULT="${TEST_RESULT} norkhsize"
						fi
					fi


					#
					# Check the file modification date-time.
					#

					if [ $FILE_IS_PKGD -eq 1 ]; then
						echo "${PKGMGR_VERIFY_RESULT}" | egrep 'T|(^.......\?)' >/dev/null && TEST_RESULT="${TEST_RESULT} verify:dtmchanged"
					elif [ $PRELINKED -eq 0 -o $FILE_IS_PKGD -eq 0 ]; then
						RKHDTM=`echo ${RKHLINE} | cut -d: -f9`
						SYSDTM=`echo ${FDATA} | cut -d: -f6`

						if [ -n "${RKHDTM}" ]; then
							test "${RKHDTM}" != "${SYSDTM}" && TEST_RESULT="${TEST_RESULT} dtmchanged"
						else
							TEST_RESULT="${TEST_RESULT} norkhdtm"
						fi
					fi
				elif [ -z "${WL_FILE}" ]; then
					TEST_RESULT="${TEST_RESULT} sysattrunavail"
				fi


				#
				# Check the file permissions here to see if the 'other' permission
				# contains a 'w'. The check is against the octal value. Symbolic
				# links are ignored.
				#

				if [ ! -h "${FNAME}" -a $FILE_IS_PKGD -eq 0 ]; then
					WL_FILE=""

					for WHITELISTFILE in ${WRITEWHITELIST}; do
						if [ "${RKHROOTDIR}${WHITELISTFILE}" = "${FNAME}" ]; then
							WL_FILE="whitelisted"
							WHITELIST_RESULT="${WHITELIST_RESULT} write"
							break
						fi
					done

					if [ -z "${WL_FILE}" ]; then
						SYSPERM=`echo ${FDATA} | cut -d: -f2`

						if [ -n "`echo ${SYSPERM} | grep '[2367]\$'`" ]; then
							TEST_RESULT="${TEST_RESULT} write"
						elif [ -z "${SYSPERM}" ]; then
							TEST_RESULT="${TEST_RESULT} syspermunavail"
						fi
					fi
				fi
			fi
		fi


		#
		# We can now carry out the tests which do not
		# require the rkhunter.dat file.
		#

		#
		# Do the file immutable-bit check.
		#

		if [ $SKIP_IMMUT -eq 0 ]; then
			#
			# Test if the file is whitelisted.
			#

			WL_FILE=""
			RKHTMPVAR=""

			for WHITELISTFILE in ${IMMUTWHITELIST}; do
				if [ "${RKHROOTDIR}${WHITELISTFILE}" = "${FNAME}" ]; then
					WL_FILE="whitelisted"
					WHITELIST_RESULT="${WHITELIST_RESULT} immutable"
					break
				fi
			done

			if [ -z "${WL_FILE}" ]; then
				if [ $BSDOS -eq 0 ]; then
					if [ ! -h "${FNAME}" ]; then
						RKHTMPVAR=`${LSATTR_CMD} ${FNAME} 2>&1 | cut -d' ' -f1 | grep 'i'`
					fi
				else
					RKHTMPVAR=`ls -lno ${FNAME} 2>&1 | awk '{ print $5 }' | egrep 'uchg|schg|sappnd|uappnd|sunlnk|sunlink|schange|simmutable|sappend|uappend|uchange|uimmutable'`
				fi

				test -n "${RKHTMPVAR}" && TEST_RESULT="${TEST_RESULT} immutable"
			fi
		fi


		#
		# Do the file script replacement check.
		#

		if [ $SKIP_SCRIPT -eq 0 ]; then
			#
			# If we are using a package manager, and both the hash test
			# and the file size test have passed, then we skip the script
			# replacement check. The assumption is that to change a file
			# with one value remaining the same is possible, but to change
			# it such that both are the same is improbable. It would also
			# require the package manager database having being corrupted
			# as well.
			#

			if [ $HASH_TEST_PASSED -eq 0 -o $SIZE_TEST_PASSED -eq 0 ]; then
				#
				# See if the file is whitelisted.
				#

				WL_FILE=""
				SYSSCRIPT=""

				for WHITELISTFILE in ${SCRIPTWHITELIST}; do
					if [ "${RKHROOTDIR}${WHITELISTFILE}" = "${FNAME}" ]; then
						WL_FILE="whitelisted"
						WHITELIST_RESULT="${WHITELIST_RESULT} script"
						break
					fi
				done

				if [ -z "${WL_FILE}" ]; then
					test -n "${BASENAME_CMD}" && RKHTMPVAR=`${BASENAME_CMD} ${FNAME}` || RKHTMPVAR=`echo "${FNAME}" | sed -e 's:^.*\/::'`

					if [ "${RKHTMPVAR}" = "rkhunter" ]; then
						SYSSCRIPT=`${FILE_CMD} ${FNAME} 2>&1 | cat -v | egrep -i -v 'shell script( |$)'`
					else
						SYSSCRIPT=`${FILE_CMD} ${FNAME} 2>&1 | cat -v | egrep -i ' script( |$)'`
					fi

					test -n "${SYSSCRIPT}" && TEST_RESULT="${TEST_RESULT} script"
				fi
			fi
		fi


		#
		# Now output the results.
		#

		if [ -z "${TEST_RESULT}" ]; then
			display --to SCREEN+LOG --type PLAIN --screen-indent 4 --result OK --color GREEN NAME "${FNAME}"
		else
			display --to SCREEN+LOG --type PLAIN --screen-indent 4 --result WARNING --color RED NAME "${FNAME}"

			PROP_FAILED_COUNT=`expr ${PROP_FAILED_COUNT} + 1`

			RKHTMPVAR2=0
			RKHTMPVAR3=0
			for RKHTMPVAR in ${TEST_RESULT}; do
				case "${RKHTMPVAR}" in
				hashchanged|permchanged|uidchanged|gidchanged|inodechanged|sizechanged|dtmchanged)
					if [ $RKHTMPVAR2 -eq 0 ]; then
						RKHTMPVAR2=1
						display --to LOG --type WARNING FILE_PROP_CHANGED
						display --to LOG --type PLAIN --log-indent 9 FILE_PROP_CHANGED2 "${FNAME}"
					fi

					case "${RKHTMPVAR}" in
					hashchanged)
						if [ -z "${SYSHASH}" ]; then
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SYSHASH_UNAVAIL
						else
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SYSHASH "${SYSHASH}"
						fi

						display --to LOG --type PLAIN --log-indent 9 FILE_PROP_RKHHASH "${RKHHASH}"

						test $DEPENDENCY_ERR -eq 1 && display --to LOG --type PLAIN --log-indent 9 FILE_PROP_NO_SYSHASH_DEPENDENCY "${FNAME}"
						;;
					permchanged)
						if [ -z "${SYSPERM}" ]; then
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_PERM_UNAVAIL "${RKHPERM}"
						else
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_PERM "${SYSPERM}" "${RKHPERM}"
						fi
						;;
					uidchanged)
						if [ -z "${SYSUID}" ]; then
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_UID_UNAVAIL "${RKHUID}"
						else
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_UID "${SYSUID}" "${RKHUID}"
						fi
						;;
					gidchanged)
						if [ -z "${SYSGID}" ]; then
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_GID_UNAVAIL "${RKHGID}"
						else
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_GID "${SYSGID}" "${RKHGID}"
						fi
						;;
					inodechanged)
						if [ -z "${SYSINODE}" ]; then
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_INODE_UNAVAIL "${RKHINODE}"
						else
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_INODE "${SYSINODE}" "${RKHINODE}"
						fi
						;;
					sizechanged)
						if [ -z "${SYSSIZE}" ]; then
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SIZE_UNAVAIL "${RKHSIZE}"
						else
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SIZE "${SYSSIZE}" "${RKHSIZE}"
						fi
						;;
					dtmchanged)
						if [ -z "${SYSDTM}" ]; then
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SYSDTM_UNAVAIL
						else
							get_readable_date ${SYSDTM}

							if [ -n "${READABLE_DATE}" ]; then
								display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SYSDTM "${SYSDTM} (${READABLE_DATE})"
							else
								display --to LOG --type PLAIN --log-indent 9 FILE_PROP_SYSDTM "${SYSDTM}"
							fi
						fi

						get_readable_date ${RKHDTM}

						if [ -n "${READABLE_DATE}" ]; then
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_RKHDTM "${RKHDTM} (${READABLE_DATE})"
						else
							display --to LOG --type PLAIN --log-indent 9 FILE_PROP_RKHDTM "${RKHDTM}"
						fi
						;;
					esac
					;;
				verify:hashchanged|verify:permchanged|verify:uidchanged|verify:gidchanged|verify:sizechanged|verify:dtmchanged)
					if [ $RKHTMPVAR3 -eq 0 ]; then
						RKHTMPVAR3=1
						display --to LOG --type WARNING FILE_PROP_VRFY
						display --to LOG --type PLAIN --log-indent 9 FILE_PROP_CHANGED2 "${FNAME}"

						test $DEPENDENCY_ERR -eq 1 && display --to LOG --type PLAIN --log-indent 9 FILE_PROP_NO_SYSHASH_DEPENDENCY "${FNAME}"
					fi

					case "${RKHTMPVAR}" in
					verify:hashchanged)
						display --to LOG --type PLAIN --log-indent 9 FILE_PROP_VRFY_HASH

						if [ "${RKHHASH}" = "ignore-prelink-dep-err" ]; then
							display --to LOG --type INFO --log-indent 9 FILE_PROP_IGNORE_PRELINK_DEP_ERR "${FNAME}"
						fi
						;;
					verify:permchanged)
						display --to LOG --type PLAIN --log-indent 9 FILE_PROP_VRFY_PERM
						;;
					verify:uidchanged)
						display --to LOG --type PLAIN --log-indent 9 FILE_PROP_VRFY_UID
						;;
					verify:gidchanged)
						display --to LOG --type PLAIN --log-indent 9 FILE_PROP_VRFY_GID
						;;
					verify:sizechanged)
						display --to LOG --type PLAIN --log-indent 9 FILE_PROP_VRFY_SIZE
						;;
					verify:dtmchanged)
						display --to LOG --type PLAIN --log-indent 9 FILE_PROP_VRFY_DTM
						;;
					esac
					;;
				norkhline)
					display --to LOG --type WARNING FILE_PROP_NO_RKH_REC "${FNAME}"
					;;
				norkhhash)
					display --to LOG --type WARNING FILE_PROP_NO_RKHHASH "${FNAME}"
					;;
				norkhperm)
					display --to LOG --type WARNING FILE_PROP_NO_RKHPERM "${FNAME}"
					;;
				norkhuid)
					display --to LOG --type WARNING FILE_PROP_NO_RKHUID "${FNAME}"
					;;
				norkhgid)
					display --to LOG --type WARNING FILE_PROP_NO_RKHGID "${FNAME}"
					;;
				norkhinode)
					display --to LOG --type WARNING FILE_PROP_NO_RKHINODE "${FNAME}"
					;;
				norkhsize)
					display --to LOG --type WARNING FILE_PROP_NO_RKHSIZE "${FNAME}"
					;;
				norkhdtm)
					display --to LOG --type WARNING FILE_PROP_NO_RKHDTM "${FNAME}"
					;;
				sysattrunavail)
					display --to LOG --type WARNING FILE_PROP_NO_SYSATTR "${FNAME}"
					;;
				write)
					display --to LOG --type WARNING FILE_PROP_WRITE "${FNAME}"
					;;
				syspermunavail)
					display --to LOG --type WARNING FILE_PROP_SYSPERM_UNAVAIL "${FNAME}"
					;;
				immutable)
					display --to LOG --type WARNING FILE_PROP_IMMUT "${FNAME}"
					;;
				script)
					test -n "${BASENAME_CMD}" && RKHTMPVAR4=`${BASENAME_CMD} ${FNAME}` || RKHTMPVAR4=`echo "${FNAME}" | sed -e 's:^.*\/::'`

					if [ "${RKHTMPVAR4}" = "rkhunter" ]; then
						display --to LOG --type WARNING FILE_PROP_SCRIPT_RKH "${FNAME}" "${SYSSCRIPT}"
					else
						display --to LOG --type WARNING FILE_PROP_SCRIPT "${FNAME}" "${SYSSCRIPT}"
					fi
					;;
				esac
			done
		fi

		if [ -n "${WHITELIST_RESULT}" ]; then
			for WL_FILE in ${WHITELIST_RESULT}; do
				case "${WL_FILE}" in
				hash)
					RKHTMPVAR="file hash"
					;;
				attr)
					RKHTMPVAR="file attributes"
					;;
				write)
					RKHTMPVAR="file write permission"
					;;
				immutable)
					RKHTMPVAR="file immutable-bit"
					;;
				script)
					RKHTMPVAR="script replacement"
					;;
				esac

				display --to LOG --type INFO FILE_PROP_WL "${FNAME}" "${RKHTMPVAR}"
			done
		fi
	done

	return
	 */
}
void RkHunterDetectionModule::performKnownRootkitCheck() {
	notify->info(this,
			"\t Performing check of known rootkit files and directories");
	/*
	 Performing check of known rootkit files and directories
	 55808 Trojan - Variant A[33C[ [0;32mNot found[0;39m ]
	 ADM Worm[49C[ [0;32mNot found[0;39m ]
	 AjaKit Rootkit[43C[ [0;32mNot found[0;39m ]
	 Adore Rootkit[44C[ [0;32mNot found[0;39m ]
	 aPa Kit[50C[ [0;32mNot found[0;39m ]
	 Apache Worm[46C[ [0;32mNot found[0;39m ]
	 Ambient (ark) Rootkit[36C[ [0;32mNot found[0;39m ]
	 Balaur Rootkit[43C[ [0;32mNot found[0;39m ]
	 BeastKit Rootkit[41C[ [0;32mNot found[0;39m ]
	 beX2 Rootkit[45C[ [0;32mNot found[0;39m ]
	 BOBKit Rootkit[43C[ [0;32mNot found[0;39m ]
	 cb Rootkit[47C[ [0;32mNot found[0;39m ]
	 CiNIK Worm (Slapper.B variant)[27C[ [0;32mNot found[0;39m ]
	 Danny-Boy's Abuse Kit[36C[ [0;32mNot found[0;39m ]
	 Devil RootKit[44C[ [0;32mNot found[0;39m ]
	 Dica-Kit Rootkit[41C[ [0;32mNot found[0;39m ]
	 Dreams Rootkit[43C[ [0;32mNot found[0;39m ]
	 Duarawkz Rootkit[41C[ [0;32mNot found[0;39m ]
	 Enye LKM[49C[ [0;32mNot found[0;39m ]
	 Flea Linux Rootkit[39C[ [0;32mNot found[0;39m ]
	 FreeBSD Rootkit[42C[ [0;32mNot found[0;39m ]
	 Fu Rootkit[47C[ [0;32mNot found[0;39m ]
	 Fuck`it Rootkit[42C[ [0;32mNot found[0;39m ]
	 GasKit Rootkit[43C[ [0;32mNot found[0;39m ]
	 Heroin LKM[47C[ [0;32mNot found[0;39m ]
	 HjC Kit[50C[ [0;32mNot found[0;39m ]
	 ignoKit Rootkit[42C[ [0;32mNot found[0;39m ]
	 iLLogiC Rootkit[42C[ [0;32mNot found[0;39m ]
	 IntoXonia-NG Rootkit[37C[ [0;32mNot found[0;39m ]
	 Irix Rootkit[45C[ [0;32mNot found[0;39m ]
	 Kitko Rootkit[44C[ [0;32mNot found[0;39m ]
	 Knark Rootkit[44C[ [0;32mNot found[0;39m ]
	 ld-linuxv.so Rootkit[37C[ [0;32mNot found[0;39m ]
	 Li0n Worm[48C[ [0;32mNot found[0;39m ]
	 Lockit / LJK2 Rootkit[36C[ [0;32mNot found[0;39m ]
	 Mood-NT Rootkit[42C[ [0;32mNot found[0;39m ]
	 MRK Rootkit[46C[ [0;32mNot found[0;39m ]
	 Ni0 Rootkit[46C[ [0;32mNot found[0;39m ]
	 Ohhara Rootkit[43C[ [0;32mNot found[0;39m ]
	 Optic Kit (Tux) Worm[37C[ [0;32mNot found[0;39m ]
	 Oz Rootkit[47C[ [0;32mNot found[0;39m ]
	 Phalanx Rootkit[42C[ [0;32mNot found[0;39m ]
	 Phalanx2 Rootkit[41C[ [0;32mNot found[0;39m ]
	 Phalanx2 Rootkit (extended tests)[24C[ [0;32mNot found[0;39m ]
	 Portacelo Rootkit[40C[ [0;32mNot found[0;39m ]
	 R3dstorm Toolkit[41C[ [0;32mNot found[0;39m ]
	 RH-Sharpe's Rootkit[38C[ [0;32mNot found[0;39m ]
	 RSHA's Rootkit[43C[ [0;32mNot found[0;39m ]
	 Scalper Worm[45C[ [0;32mNot found[0;39m ]
	 Sebek LKM[48C[ [0;32mNot found[0;39m ]
	 Shutdown Rootkit[41C[ [0;32mNot found[0;39m ]
	 SHV4 Rootkit[45C[ [0;32mNot found[0;39m ]
	 SHV5 Rootkit[45C[ [0;32mNot found[0;39m ]
	 Sin Rootkit[46C[ [0;32mNot found[0;39m ]
	 Slapper Worm[45C[ [0;32mNot found[0;39m ]
	 Sneakin Rootkit[42C[ [0;32mNot found[0;39m ]
	 'Spanish' Rootkit[40C[ [0;32mNot found[0;39m ]
	 Suckit Rootkit[43C[ [0;32mNot found[0;39m ]
	 SunOS Rootkit[44C[ [0;32mNot found[0;39m ]
	 SunOS / NSDAP Rootkit[36C[ [0;32mNot found[0;39m ]
	 Superkit Rootkit[41C[ [0;32mNot found[0;39m ]
	 TBD (Telnet BackDoor)[36C[ [0;32mNot found[0;39m ]
	 TeLeKiT Rootkit[42C[ [0;32mNot found[0;39m ]
	 T0rn Rootkit[45C[ [0;32mNot found[0;39m ]
	 trNkit Rootkit[43C[ [0;32mNot found[0;39m ]
	 Trojanit Kit[45C[ [0;32mNot found[0;39m ]
	 Tuxtendo Rootkit[41C[ [0;32mNot found[0;39m ]
	 URK Rootkit[46C[ [0;32mNot found[0;39m ]
	 Vampire Rootkit[42C[ [0;32mNot found[0;39m ]
	 VcKit Rootkit[44C[ [0;32mNot found[0;39m ]
	 Volc Rootkit[45C[ [0;32mNot found[0;39m ]
	 Xzibit Rootkit[43C[ [0;32mNot found[0;39m ]
	 X-Org SunOS Rootkit[38C[ [0;32mNot found[0;39m ]
	 zaRwT.KiT Rootkit[40C[ [0;32mNot found[0;39m ]
	 ZK Rootkit[47C[ [0;32mNot found[0;39m ]
	 */
}
void RkHunterDetectionModule::performAdditionalRootkitCheck() {
	notify->info(this, "\t Performing additional rootkit checks");
	/*
	 Performing additional rootkit checks
	 Suckit Rookit additional checks[26C[ [0;32mOK[0;39m ]
	 Checking for possible rootkit files and directories[6C[ [0;32mNone found[0;39m ]
	 Checking for possible rootkit strings[20C[ [1;31mWarning[0;39m ]
	 */
}
void RkHunterDetectionModule::performMalwareCheck() {
	notify->info(this, "\t Performing malware checks");
	/*
	 Performing malware checks
	 Checking running processes for suspicious files[10C[ [0;32mNone found[0;39m ]
	 Checking for login backdoors[29C[ [0;32mNone found[0;39m ]
	 Checking for suspicious directories[22C[ [0;32mNone found[0;39m ]
	 Checking for sniffer log files[27C[ [0;32mNone found[0;39m ]
	 */
}
void RkHunterDetectionModule::performTrojanSpecificCheck() {
	notify->info(this, "\t Performing trojan specific checks");
	/*
	 Performing trojan specific checks
	 Checking for enabled inetd services[22C[ [0;32mOK[0;39m ]
	 */
}
void RkHunterDetectionModule::performLinuxSpecificCheck() {
	notify->info(this, "\t Performing Linux specific checks");
	/*
	 Performing Linux specific checks
	 Checking loaded kernel modules[27C[ [0;32mOK[0;39m ]
	 Checking kernel module names[29C[ [0;32mOK[0;39m ]
	 */
}
void RkHunterDetectionModule::performBackdoorCheck() {
	notify->info(this, "\t Performing check for backdoor ports");
	/*
	 Performing check for backdoor ports
	 Checking for TCP port 1524[31C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 1984[31C[ [0;32mNot found[0;39m ]
	 Checking for UDP port 2001[31C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 2006[31C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 2128[31C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 6666[31C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 6667[31C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 6668[31C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 6669[31C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 7000[31C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 13000[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 14856[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 25000[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 29812[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 31337[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 33369[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 47107[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 47018[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 60922[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 62883[30C[ [0;32mNot found[0;39m ]
	 Checking for TCP port 65535[30C[ [0;32mNot found[0;39m ]
	 */
}
void RkHunterDetectionModule::performNetworkInterfacesCheck() {
	notify->info(this, "\t Performing checks on the network interfaces");
	/*
	 Performing checks on the network interfaces
	 Checking for promiscuous interfaces[22C[ [0;32mNone found[0;39m ]
	 */
}
void RkHunterDetectionModule::performSystemBootCheck() {
	notify->info(this, "\t Performing system boot checks");
	/*
	 Performing system boot checks
	 Checking for local host name[29C[ [0;32mFound[0;39m ]
	 Checking for system startup files[24C[ [0;32mFound[0;39m ]
	 Checking system startup files for malware[16C[ [0;32mNone found[0;39m ]
	 */
}
void RkHunterDetectionModule::performGroupAndAccountCheck() {
	notify->info(this, "\t Performing group and account checks");
	/*
	 Performing group and account checks
	 Checking for passwd file[33C[ [0;32mFound[0;39m ]
	 Checking for root equivalent (UID 0) accounts[12C[ [0;32mNone found[0;39m ]
	 Checking for passwordless accounts[23C[ [0;32mNone found[0;39m ]
	 Checking for passwd file changes[25C[ [0;32mNone found[0;39m ]
	 Checking for group file changes[26C[ [0;32mNone found[0;39m ]
	 Checking root account shell history files[16C[ [0;32mOK[0;39m ]
	 */
}
void RkHunterDetectionModule::performSystemConfigurationCheck() {
	notify->info(this, "\t Performing system configuration file checks");
	/*
	 Performing system configuration file checks
	 Checking for SSH configuration file[22C[ [0;32mFound[0;39m ]
	 Checking if SSH root access is allowed[19C[ [1;31mWarning[0;39m ]
	 Checking if SSH protocol v1 is allowed[19C[ [0;32mNot allowed[0;39m ]
	 Checking for running syslog daemon[23C[ [0;32mFound[0;39m ]
	 Checking for syslog configuration file[19C[ [0;32mFound[0;39m ]
	 Checking if syslog remote logging is allowed[13C[ [0;32mNot allowed[0;39m ]
	 */
}
void RkHunterDetectionModule::performFileSystemCheck() {
	notify->info(this, "\t Performing filesystem checks");
	/*
	 Performing filesystem checks
	 Checking /dev for suspicious file types[18C[ [1;31mWarning[0;39m ]
	 Checking for hidden files and directories[16C[ [1;31mWarning[0;39m ]
	 */
}
void RkHunterDetectionModule::performApplicationVersionsCheck() {
	notify->info(this, "\t Performing Application Version checks");
	/*
	 Checking version of Exim MTA[29C[ [0;32mOK[0;39m ]
	 Checking version of GnuPG[32C[ [0;32mOK[0;39m ]
	 Checking version of OpenSSL[30C[ [0;32mOK[0;39m ]
	 Checking version of Procmail MTA[25C[ [0;32mOK[0;39m ]
	 Checking version of OpenSSH[30C[ [0;32mOK[0;39m ]
	 */
}
