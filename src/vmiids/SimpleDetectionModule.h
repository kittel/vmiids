/*
 * SimpleDetectionModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef SIMPLEDETECTIONMODULE_H_
#define SIMPLEDETECTIONMODULE_H_

#include "DetectionModule.h"

class SimpleDetectionModule: public DetectionModule {
public:
	SimpleDetectionModule();
	virtual ~SimpleDetectionModule();

	virtual void run();
	virtual void runTime();
	virtual void runEvent();

	virtual void getThreadLevel();
};

#endif /* SIMPLEDETECTIONMODULE_H_ */
