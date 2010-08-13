/*
 * DetectionModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef DETECTIONMODULE_H_
#define DETECTIONMODULE_H_

#include "Module.h"

namespace vmi {

class DetectionModule : public vmi::Module {
	public:
		DetectionModule(std::string moduleName) : vmi::Module(moduleName) {};
		virtual ~DetectionModule(){};

		virtual void run() = 0;
		virtual void runTime() = 0;
		virtual void runEvent() = 0;

		virtual void getThreadLevel() = 0;
};

}

#include "Modintern.h"

#endif /* DETECTIONMODULE_H_ */

