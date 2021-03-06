/*
 * FileContentDetectionModule.h
 *
 *  Created on: Jul 30, 2010
 *      Author: kittel
 */

#ifndef FILECONTENTDETECTIONMODULE_H_
#define FILECONTENTDETECTIONMODULE_H_

#include "vmiids/DetectionModule.h"

#include "vmiids/modules/sensor/QemuMonitorSensorModule.h"
#include "vmiids/modules/sensor/FileSystemSensorModule.h"
#include "vmiids/modules/sensor/ShellSensorModule.h"

/**
 * @class FileContentDetectionModule FileContentDetectionModule.h "vmiids/modules/detection/FileContentDetectionModule.h"
 * @brief Example module checking file integrity.
 * @sa vmi::DetectionModule
 * @sa QemuMonitorSensorModule
 * @sa FileSystemSensorModule
 * @sa ShellSensorModule
 *
 * The FileContentDetectionModule checks the integrity of files contained within the monitored systems
 * file system.
 *
 * Therefore this detection module compares an hash value generated by the FileSystemSensorModule with
 * an generated with the ShellSensorModule. The calculated hash value is a sha1 hash.<p>
 *
 * If the compared hash values do not match, it is an evidence for different views of the same physical
 * state. Hence an alert message is raised and the thread level is raised to one.<p>
 *
 * The current thread level is reduced to zero, if no mismatch is detected.
 */
class FileContentDetectionModule : public vmi::DetectionModule{
	QemuMonitorSensorModule * qemu;
	ShellSensorModule * shell;
	FileSystemSensorModule * fs;

	std::string directory;

public:
	FileContentDetectionModule();
	virtual ~FileContentDetectionModule();

	virtual void run();
};

#endif /* FILECONTENTDETECTIONMODULE_H_ */
