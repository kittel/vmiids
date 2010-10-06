/*
 * FileListDetectionModule.h
 *
 *  Created on: Jul 28, 2010
 *      Author: kittel
 */

#ifndef FILELISTDETECTIONMODULE_H_
#define FILELISTDETECTIONMODULE_H_

#include "vmiids/DetectionModule.h"

#include "vmiids/modules/sensor/QemuMonitorSensorModule.h"
#include "vmiids/modules/sensor/FileSystemSensorModule.h"
#include "vmiids/modules/sensor/ShellSensorModule.h"

/*!
 * \exception FileListDetectionModuleException FileListDetectionModule.h "vmiids/modules/detection/FileListDetectionModule.h"
 * \brief Exception for FileListDetectionModule.
 */
class FileListDetectionModuleException: public std::exception {
	virtual const char* what() const throw () {
		return "FileListDetectionModule abort";
	}
};

/**
 * @class FileListDetectionModule FileListDetectionModule.h "vmiids/modules/detection/FileListDetectionModule.h"
 * @brief Example module checking for hidden and virtual files.
 * @sa vmi::DetectionModule
 * @sa QemuMonitorSensorModule
 * @sa FileSystemSensorModule
 * @sa ShellSensorModule
 *
 * The FileListDetectionModule is usable to detect hidden and virtual files in the monitored machine.
 * Virtual files are files visible within the monitored systems view. These files are not physically
 * stored on the filesystem. Therefore these files are not visible in the external view.
 * Hidden files are visible within the external view, but not visible in the internal view.
 * Both types of files are evidence for a compromised monitored system.<p>
 *
 * This module compares both, the internal and the external view of the monitored filesystems state.<p>
 *
 * As both views are not generated at the exact same time, this module creates a message of type critical
 * if an inconsistency is detected. If the inconsistency is detected in consecutive comparisons,
 * an alert message is created.<p>
 *
 * Next to the created messages the thread level is raised to 0.5, if an inconsistency is detected
 * once. If the inconsistency is contained in consecutive comparisons, the thread level is raised
 * to one. The thread level is reset back to zero if no inconsistency is detected.<p>
 */
class FileListDetectionModule : public vmi::DetectionModule{

private:
	QemuMonitorSensorModule * qemu;
	ShellSensorModule * shell;
	FileSystemSensorModule * fs;

	std::string directory;

	std::set<std::string> globalFsFileList;
	std::set<std::string> globalShellFileList;

public:
	FileListDetectionModule();
	virtual ~FileListDetectionModule();

	virtual void run();
};

#endif /* FILELISTDETECTIONMODULE_H_ */
