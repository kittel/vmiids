/*
 * Module.h
 *
 *  Created on: Jul 30, 2010
 *      Author: kittel
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <string>

namespace vmi {

class Module{
	private:
		std::string moduleName;

	public:
		Module(std::string moduleName){ this->moduleName = moduleName;};
		std::string getName(){ return this->moduleName; };
};

}

#endif /* MODULE_H_ */
