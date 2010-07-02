/*
 * ShellSensorModule.h
 *
 *  Created on: Jul 2, 2010
 *      Author: kittel
 */

#ifndef SHELLSENSORMODULE_H_
#define SHELLSENSORMODULE_H_

#include "SensorModule.h"
#include "libvmi.h"

class ShellSensorModule : public SensorModule , public libVMI::ShellParser {
public:
	ShellSensorModule();
	virtual ~ShellSensorModule();

	void initSensorModule();
};

#endif /* SHELLSENSORMODULE_H_ */
