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
		virtual void run() = 0;
		virtual void runTime() = 0;
		virtual void runEvent() = 0;

		virtual void getThreadLevel() = 0;
};

}

#include "VmiIDS.h"

#define ADDDYNAMICDETECTIONMODULE(classname) class CONCAT(classname, proxy) { \
	public: \
	CONCAT(classname, proxy)(){ try { \
		                       std::cerr << "Loading DetectionModule " << QUOTE(classname) << "... "; \
	                           vmi::VmiIDS::getInstance()->enqueueDetectionModule(new classname); \
		                       std::cerr << "Success" << std::endl; \
                           } \
	                       catch (vmi::ModuleException &e){ \
		                       std::cerr << "FAILED" << std::endl; \
	                    	   e.printException(); \
	                       } \
	                       catch (std::exception &e){ \
	                    	   std::cerr << "FAILED" << std::endl; \
	                    	   std::cerr << e.what() << std::endl; \
	                       } \
	                     } \
	}; \
static CONCAT(classname, proxy) CONCAT(classname, p);


#endif /* DETECTIONMODULE_H_ */
