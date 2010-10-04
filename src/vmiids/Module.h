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
#define QUOTE(s) STR(s)        /*!< In case s contains spaces the STR() is wrapped. */
#define CONCAT(a, b) a ## b    /*!< Concatinate a and b. */

namespace vmi {

/**
 * @class ModuleException Module.h "vmiids/Module.h"
 * @brief Generic module exception.
 * @sa vmi::Exception
 *
 * Exception thrown by subclasses of class Module within VmiIDS.
 * Denotes an unspecified error within the module.
 */
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

/**
 * @class FunctionNotImplementedException Module.h "vmiids/Module.h"
 * @brief Exception thrown when function is only stub.
 * @sa vmi::ModuleException
 *
 * Exception thrown by subclasses of class Module within VmiIDS.
 * Denotes that the called function is currently a stub.
 */
class FunctionNotImplementedException: public ModuleException {
public:
	FunctionNotImplementedException(std::string text) : ModuleException(text) { }
	virtual const char* what() const throw () {
		return "Function not implemented";
	}
};

/**
 * @class DependencyNotFoundException Module.h "vmiids/Module.h"
 * @brief Exception thrown when a dependency was not found.
 * @sa vmi::ModuleException
 *
 * Exception thrown by subclasses of class Module within VmiIDS.
 * Denotes that the module could not find a dependency.
 * For example a DetectionModule unable to find an appropriate SensorModule.
 */
class DependencyNotFoundException: public ModuleException {
public:
	DependencyNotFoundException(std::string text) : ModuleException(text) { }
	virtual const char* what() const throw () {
		return "Dependency not found";
	}
};

/**
 * @class Module Module.h "vmiids/Module.h"
 * @brief Generic module.
 *
 * VmiIDS is a framework managing different modules.
 * Each module is derived from the Module base class.
 * Subclasses currently there are: SensorModule, DetectionModule and NotificationModule.
 *
 * The base class contains the modules name.
 *
 * Modules which should be loadable to the VmiIDS framework must use the \ref LOADMODULE() macro.
 */
class Module{
	private:
		std::string moduleName; //!< Name of the module.

	public:
		/**
		 * Constructor. Sets the name of the new module to moduleName.
		 *
		 * @param moduleName Name of the new Module
		 */
		Module(std::string moduleName){ this->moduleName = moduleName;};
		/**
		 * Destructor
		 */
		virtual ~Module(){};
		/**
		 * Function returning the modules name.
		 * @return Name of the module.
		 */
		std::string getName(){ return this->moduleName; };
};

/**
 * @class ModuleLoader Module.h "vmiids/Module.h"
 * @brief ModuleLoader class.
 * @sa LOADMODULE
 *
 * VmiIDS is a framework managing different modules.
 * Each module is derived from the Module base class.
 *
 * The ModuleLoader class can be used to auto-load a module.
 */
template<class Module>
class ModuleLoader{
private:
	Module *module; //! Pointer to the module.
public:
	/**
	 * Constructor. Used to load the given module.
	 * Success or failure is reported to std::cerr.
	 * @return
	 */
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
	/**
	 * Empty Destructor.
	 * @return
	 */
	~ModuleLoader(){
	}
};

/**
 * @brief Macro to auto-load a Module.
 *
 * @def LOADMODULE
 * @param classname Class to load. Must be a subclass of vmi::Module.
 *
 * This macro creates a static instance of class vmi::ModuleLoader.
 * This macro is used by any module which should be auto-loaded
 * into vmi::VmiIDS. As the instance is static, its constructor
 * is called directly after the object file was loaded with the dl_open function.
 * @sa vmi::VmiIDS::loadModules().
 */
#define LOADMODULE(classname) \
	static vmi::ModuleLoader<classname> CONCAT(classname, p);
}

#endif /* MODULE_H_ */
