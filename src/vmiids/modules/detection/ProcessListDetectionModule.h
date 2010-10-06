/*
 * ProcessListDetectionModule.h
 *
 *  Created on: Jul 23, 2010
 *      Author: kittel
 */

#ifndef PROCESSLISTDETECTIONMODULE_H_
#define PROCESSLISTDETECTIONMODULE_H_

#include "vmiids/DetectionModule.h"

#include "vmiids/modules/sensor/QemuMonitorSensorModule.h"
#include "vmiids/modules/sensor/MemorySensorModule.h"
#include "vmiids/modules/sensor/ShellSensorModule.h"

/**
 * @class ProcessListDetectionModule ProcessListDetectionModule.h "vmiids/modules/detection/ProcessListDetectionModule.h"
 * @brief Example module checking process integrity.
 * @sa vmi::DetectionModule
 * @sa QemuMonitorSensorModule
 * @sa MemorySensorModule
 * @sa ShellSensorModule
 *
 * The ProcessListDetectionModule is used to detect hidden and virtual processes.<p>
 * Hidden processes are those, executed within the virtual machines view, but hidden in the monitored
 * machines internal view. As these processes are enlisted inside the kernel task list,
 * they can be detected by the MemorySensorModule. <p>
 * Virtual processes are those, visible within the virtual machine view, but not actually executed.
 * These processes are not enlisted within the kernels task list.
 * Both types of processes are evidence for a compromised monitored system.<p>
 *
 * This module compares both, the internal and the external view of the monitored state.<p>
 *
 * As both views are not generated at the exact same time, this module creates a message of type critical
 * if an inconsistency is detected. If the inconsistency is detected in consecutive comparisons,
 * an alert message is created.<p>
 *
 * Next to the created messages the thread level is raised to 0.5, if an inconsistency is detected
 * once. If the inconsistency is contained in consecutive comparisons, the thread level is raised
 * to one. The thread level is reset back to zero if no inconsistency is detected.<p>
 *
 * The current thread level is reduced to zero, if no mismatch is detected.
 */
class ProcessListDetectionModule : public vmi::DetectionModule{
	QemuMonitorSensorModule * qemu;
	ShellSensorModule * shell;
	MemorySensorModule * memory;

	std::map<uint32_t, MemtoolProcess> globalMemtoolProcessMap;
	std::map<uint32_t, ShellProcess> globalPsProcessMap;

public:
	ProcessListDetectionModule();
	virtual ~ProcessListDetectionModule();

	virtual void run();
};

#endif /* PROCESSLISTDETECTIONMODULE_H_ */
