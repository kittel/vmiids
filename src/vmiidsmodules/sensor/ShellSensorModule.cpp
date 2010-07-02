/*
 * ShellSensorModule.cpp
 *
 *  Created on: Jul 2, 2010
 *      Author: kittel
 */

#include "ShellSensorModule.h"

ADDDYNAMICSENSORMODULE(ShellSensorModule, __LINE__);

ShellSensorModule::ShellSensorModule() : SensorModule("ShellSensorModule"), ShellParser(){
	// TODO Auto-generated constructor stub

}

ShellSensorModule::~ShellSensorModule() {
	// TODO Auto-generated destructor stub
}

void ShellSensorModule::initSensorModule(){

}
