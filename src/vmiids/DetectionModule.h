/*
 * DetectionModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef DETECTIONMODULE_H_
#define DETECTIONMODULE_H_

#include "Module.h"
#include "OutputModule.h"
#include "util/Thread.h"

namespace vmi {

class DetectionModule : public vmi::Module, protected OutputModule, public Thread{
	protected:
		bool intrusionDetected;
	public:
		DetectionModule(std::string moduleName) :
			vmi::Module(moduleName),
			vmi::OutputModule(moduleName){
			intrusionDetected = false;
		};
		virtual ~DetectionModule(){};

		bool getThreadLevel(){ return intrusionDetected; }
};

}

#include "Modintern.h"

#endif /* DETECTIONMODULE_H_ */

