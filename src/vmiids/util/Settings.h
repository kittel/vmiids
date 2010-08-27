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

#define GETOPTION(option, variable) if(!vmi::Settings::getInstance()->getSetting(this->getName()).lookupValue(QUOTE(option),variable)){ \
	                                     throw vmi::OptionNotFoundException(this->getName(), QUOTE(option)); }

class Settings {
private:
	libconfig::Config config;

	Settings();
	Settings(std::string filename);
	Settings(const Settings&);
	Settings& operator=(const Settings&);
	static Settings *instance;

public:
	virtual ~Settings();
	bool openConfigFile(std::string filename);

	static Settings *getInstance();

	libconfig::Setting &getSetting(std::string settingName);
};

}

#endif /* SETTINGS_H_ */
