/*
 * RkHunterDetectionModule.h
 *
 *  Created on: Jul 2, 2010
 *      Author: kittel
 */

#ifndef RKHUNTERDETECTIONMODULE_H_
#define RKHUNTERDETECTIONMODULE_H_

#include "vmiids/DetectionModule.h"

#include "vmiids/modules/sensor/QemuMonitorSensorModule.h"
#include "vmiids/modules/sensor/FileSystemSensorModule.h"
#include "vmiids/modules/sensor/ShellSensorModule.h"

#include <map>
#include <string>

class RkHunterDetectionModule : public vmi::DetectionModule {
private:
	QemuMonitorSensorModule * qemu;
	FileSystemSensorModule * fs;
	ShellSensorModule * shell;

	std::multimap<std::string,std::string> rkvars;

	void initializeVariables();

	void performStringCommandCheck();
	void performSharedLibrariesCheck();
	void performFilePropertiesCheck();
	void performKnownRootkitCheck();
	void performAdditionalRootkitCheck();
	void performMalwareCheck();
	void performTrojanSpecificCheck();
	void performLinuxSpecificCheck();
	void performBackdoorCheck();
	void performNetworkInterfacesCheck();
	void performSystemBootCheck();
	void performGroupAndAccountCheck();
	void performSystemConfigurationCheck();
	void performFileSystemCheck();
	void performApplicationVersionsCheck();

public:
	RkHunterDetectionModule();
	virtual ~RkHunterDetectionModule();

	virtual void run();
};

#endif /* RKHUNTERDETECTIONMODULE_H_ */
