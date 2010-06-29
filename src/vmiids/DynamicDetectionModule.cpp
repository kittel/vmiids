/*
 * DynamicDetectionModule.cpp
 *
 *  Created on: Jun 29, 2010
 *      Author: kittel
 */

#include "DynamicDetectionModule.h"

#include <stdio.h>

DynamicDetectionModule::DynamicDetectionModule(): DetectionModule("DynamicDetectionModule") {
	// TODO Auto-generated constructor stub
}

DynamicDetectionModule::~DynamicDetectionModule() {
	// TODO Auto-generated destructor stub
}

void DynamicDetectionModule::run(){
	printf("DynamicDetectionModule running\n");
}

void DynamicDetectionModule::runTime(){

}

void DynamicDetectionModule::runEvent(){

}

void DynamicDetectionModule::getThreadLevel(){

}
