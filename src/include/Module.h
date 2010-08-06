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

#define STR(s) #s              /*!< Do not interpret s. Return as char* */
#define QUOTE(s) STR(s)  /*!< In case s contains spaces the STR_MACRO() is wrapped. */

namespace vmi {

class ModuleException: public std::exception {
private:
	std::string message;
public:
	ModuleException(){ this->message = ""; }
	ModuleException(std::string text){ this->message = text; }
	virtual ~ModuleException() throw(){};
	virtual const char* what() const throw () {
		return "Module abort: ";
	}
	virtual void printException(){ std::cerr << what() << " " << this->message << std::endl; }
};


class FunctionNotImplementedException: public ModuleException {
public:
	FunctionNotImplementedException(std::string text) : ModuleException(text) { }
	virtual const char* what() const throw () {
		return "Function not implemented: ";
	}
};

class DependencyNotFoundException: public ModuleException {
public:
	DependencyNotFoundException(std::string text) : ModuleException(text) { }
	virtual const char* what() const throw () {
		return "Dependency not found: ";
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
