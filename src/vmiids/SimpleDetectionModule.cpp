/*
 * SimpleDetectionModule.cpp
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#include <stdio.h>

#include "SimpleDetectionModule.h"

SimpleDetectionModule::SimpleDetectionModule() : DetectionModule("SimpleDetectionModule") {
	// TODO Auto-generated constructor stub

}

SimpleDetectionModule::~SimpleDetectionModule() {
	// TODO Auto-generated destructor stub
}

void SimpleDetectionModule::run(){
	printf("SimpleDetectionModule running\n");
}

void SimpleDetectionModule::runTime(){

}

void SimpleDetectionModule::runEvent(){

}

void SimpleDetectionModule::getThreadLevel(){

}
