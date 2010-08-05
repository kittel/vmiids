/*
 * Module.h
 *
 *  Created on: Jul 30, 2010
 *      Author: kittel
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <string>
#include <exception>
#include <iostream>

namespace vmi {

class ModuleException: public std::exception {
private:
	std::string message;
public:
	ModuleException(){ this->message = ""; }
	ModuleException(std::string text){ this->message = text; }
	virtual ~ModuleException() throw(){};
	virtual const char* what() const throw () {
		return "MemorySensorModule abort";
	}
	virtual void printException(){ std::cerr << what() << " " << this->message << std::endl; }
};

/*!
 * \exception QemuMonitorParserNotImplementedException QemuMonitorParser.h
 * \brief Exception for QemuMonitorParser.
 */
class FunctionNotImplementedException: public ModuleException {
	virtual const char* what() const throw () {
		return "Function not implemented";
	}
};

class Module{
	private:
		std::string moduleName;

	public:
		Module(std::string moduleName){ this->moduleName = moduleName;};
		std::string getName(){ return this->moduleName; };
};

}

#endif /* MODULE_H_ */
