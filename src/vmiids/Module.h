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
#include <exception>
#include <iostream>


#define STR(s) #s              /*!< Do not interpret s. Return as char* */
#define QUOTE(s) STR(s)  /*!< In case s contains spaces the STR_MACRO() is wrapped. */

namespace vmi {

class ModuleException: public std::exception {
protected:
	std::string message;
public:
	ModuleException(){ this->message = ""; }
	ModuleException(std::string text){ this->message = text; }
	virtual ~ModuleException() throw(){};
	virtual const char* what() const throw () {
		return "Module abort";
	}
	virtual void printException(){ std::cerr << what() << ": " << this->message << std::endl; }
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

class OptionNotFoundException: public ModuleException {
public:
	OptionNotFoundException(std::string module, std::string setting) : ModuleException() {
		std::stringstream msg;
		msg << "Could not parse Option. Please add the following section to the config file:"
			<< std::endl << module << " = {" << std::endl
			<< "\t" << setting << " =  \"<value>\";"
			<< std::endl << "};";
		this->message = msg.str();
	}
	virtual const char* what() const throw () {
		return "Setting not found";
	}
};

#define GETOPTION(option, variable) if(vmi::VmiIDS::getInstance()->getSetting(this->getName()) == NULL || \
	                                  !vmi::VmiIDS::getInstance()->getSetting(this->getName())->lookupValue(QUOTE(option),variable)){ \
	                                     throw vmi::OptionNotFoundException(this->getName(), QUOTE(option)); }

class Module{
	private:
		std::string moduleName;

	public:
		Module(std::string moduleName){ this->moduleName = moduleName;};
		virtual ~Module(){};
		std::string getName(){ return this->moduleName; };
};

}

#endif /* MODULE_H_ */
