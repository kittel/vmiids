/*
 * DynamicDetectionModule.h
 *
 *  Created on: Jun 29, 2010
 *      Author: kittel
 */

#ifndef DYNAMICDETECTIONMODULE_H_
#define DYNAMICDETECTIONMODULE_H_

#include "DetectionModule.h"

class DynamicDetectionModule: public DetectionModule {
public:
	DynamicDetectionModule();
	virtual ~DynamicDetectionModule();

	virtual void run();
	virtual void runTime();
	virtual void runEvent();

	virtual void getThreadLevel();
};
ADDDYNAMICDETECTIONMODULE(DynamicDetectionModule, __LINE__);

#endif /* DYNAMICDETECTIONMODULE_H_ */
