/*
 * Settings.h
 *
 *  Created on: Aug 27, 2010
 *      Author: tom
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <libconfig.h++>
#include <string>
#include <sstream>

#include "vmiids/util/Exception.h"

namespace vmi {

/**
 * @class ConfigFileException Settings.h "vmiids/util/Settings.h"
 * @brief Generic config file exception.
 * @sa vmi::Exception
 *
 * Exception thrown by Settings class.
 * Denotes an unspecified error within the class.
 */
class ConfigFileException: public Exception {
public:
	ConfigFileException(std::string fileName) : Exception() {
		std::stringstream msg;
		msg << "Could not parse Configfile: " << fileName << std::endl;
		this->message = msg.str();
	}
	virtual const char* what() const throw () {
		return "Setting not found";
	}
};

/**
 * @class OptionNotFoundException Settings.h "vmiids/util/Settings.h"
 * @brief Exception denoting an unknown option.
 * @sa vmi::Exception
 *
 * Exception thrown by Settings class.
 * Denotes that an unknown option was requested from the settings backend.
 */
class OptionNotFoundException: public Exception {
public:
	OptionNotFoundException(std::string setting) : Exception() {
		std::stringstream msg;
		msg << "Could not parse Setting: " << setting << std::endl;
		this->message = msg.str();
	}
	OptionNotFoundException(std::string module, std::string setting) : Exception() {
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

/**
 * @brief Macro to request Setting from inside a module.
 *
 * @def GETOPTION
 * @param option Option requested.
 * @param variable Variable to write options content to.
 *
 * This Macro is used to read settings from within the different modules.
 * If the requested option is not found, a vmi::OptionNotFoundException is raised.
 */
#define GETOPTION(option, variable) if(!vmi::Settings::getInstance()->getSetting(this->getName()).lookupValue(QUOTE(option),variable)){ \
	                                     throw vmi::OptionNotFoundException(this->getName(), QUOTE(option)); }
/**
 * @class Settings Settings.h "vmiids/util/Settings.h"
 * @brief Settings class
 *
 * Settings class, provided to hide the external libconfig interface. The Settings class is a Singelon.
 */
class Settings {
private:
	libconfig::Config config; //<! External libconfig object;

	/**
	 * Default Constructor
	 *
	 * Parses the configuration file vmiids.cfg, if it is located
	 * in the processes working directory or in /etc.
	 */
	Settings();
	/**
	 * Constructor
	 *
	 * Constructor which uses the file given in filename to parse options from.
	 *
	 * @param filename File to load options from.
	 */
	Settings(std::string filename);
	/**
	 * Private copy constructor.
	 *
	 * Constructor defined private, that no module is able to hold an own reference to an old configuration.
	 */
	Settings(const Settings&);
	/**
	 * Private copy operator.
	 *
	 * Operator defined private, that no module is able to hold an own reference to an old configuration.
	 */
	Settings& operator=(const Settings&);
	static Settings *instance;

public:
	virtual ~Settings();
	/**
	 * Parse configuration from file
	 * @param filename File to parse configuration from.
	 * @return True, if file could be parsed.
	 */
	bool openConfigFile(std::string filename);

	/**
	 * Returns an Instance of the singleton class Settings.
	 * @return Instance of the singleton class Settings.
	 */
	static Settings *getInstance();

	/**
	 * Query an configuration option from the settings already parsed.
	 * It is advisable to use the GETOPTION() macro.
	 *
	 * @param settingName Name of the Setting
	 * @return Libconfig representation of the setting.
	 */
	libconfig::Setting &getSetting(std::string settingName);
};

}

#endif /* SETTINGS_H_ */
