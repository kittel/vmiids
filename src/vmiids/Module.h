/*
 * Module.h
 *
 *  Created on: Jul 30, 2010
 *      Author: kittel
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <string>
#include <sstream>
#include <iostream>

#include "vmiids/util/Exception.h"
#include "vmiids/util/Settings.h"

#define STR(s) #s              /*!< Do not interpret s. Return as char* */
#define QUOTE(s) STR(s)  /*!< In case s contains spaces the STR_MACRO() is wrapped. */
#define CONCAT(a, b) a ## b

namespace vmi {

class ModuleException: public Exception {
protected:
	std::string message;
public:
	ModuleException(){};
	ModuleException(std::string text) : Exception(text){};
	virtual ~ModuleException() throw(){};
	virtual const char* what() const throw () {
		return "Module abort";
	}
};

class FunctionNotImplementedException: public ModuleException {
public:
	FunctionNotImplementedException(std::string text) : ModuleException(text) { }
	virtual const char* what() const throw () {
		return "Function not implemented";
	}
};

class DependencyNotFoundException: public ModuleException {
public:
	DependencyNotFoundException(std::string text) : ModuleException(text) { }
	virtual const char* what() const throw () {
		return "Dependency not found";
	}
};

class Module{
	private:
		std::string moduleName;

	public:
		Module(std::string moduleName){ this->moduleName = moduleName;};
		virtual ~Module(){};
		std::string getName(){ return this->moduleName; };
};

template<class Module>
class ModuleLoader{
private:
	Module *module;
public:
	ModuleLoader(){
		try {
			module = new Module();
		} catch (vmi::ModuleException &e) {
			std::cerr << "Loading Module FAILED" << std::endl;
			e.printException();
		} catch (std::exception &e) {
			std::cerr << "Loading Module FAILED" << std::endl;
			std::cerr << e.what() << std::endl;
		}
	}
	~ModuleLoader(){
	}
};

#define LOADMODULE(classname) \
	static vmi::ModuleLoader<classname> CONCAT(classname, p);
}

#endif /* MODULE_H_ */
