/*
 * DetectionModule.h
 *
 *  Created on: Jun 26, 2010
 *      Author: kittel
 */

#ifndef DETECTIONMODULE_H_
#define DETECTIONMODULE_H_

#include <string>

class DetectionModule{

	private:
		std::string moduleName;

	public:
		DetectionModule(std::string moduleName){ this->moduleName = moduleName;};
		std::string getName(){ return this->moduleName; };
		virtual void run() = 0;
		virtual void runTime() = 0;
		virtual void runEvent() = 0;

		virtual void getThreadLevel() = 0;
};


#endif /* DETECTIONMODULE_H_ */
