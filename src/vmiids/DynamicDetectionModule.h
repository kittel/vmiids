/*
 * DynamicDetectionModule.h
 *
 *  Created on: Jun 29, 2010
 *      Author: kittel
 */

#ifndef DYNAMICDETECTIONMODULE_H_
#define DYNAMICDETECTIONMODULE_H_

#include "VmiIDS.h"

class DynamicDetectionModule: public DetectionModule {
public:
	DynamicDetectionModule();
	virtual ~DynamicDetectionModule();

	virtual void run();
	virtual void runTime();
	virtual void runEvent();

	virtual void getThreadLevel();
};

extern "C" {
static DynamicDetectionModule *maker(){
   return new DynamicDetectionModule;
}
class proxy {
	public:
	proxy(){
		// register the maker with the factory
		VmiIDS::getInstance()->enqueueDetectionModule(new DynamicDetectionModule);
		//factory["square"] = maker;
   }
};
// our one instance of the proxy
static proxy p;
}

#endif /* DYNAMICDETECTIONMODULE_H_ */
