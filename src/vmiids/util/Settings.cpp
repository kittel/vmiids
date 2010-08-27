/*
 * Settings.cpp
 *
 *  Created on: Aug 27, 2010
 *      Author: tom
 */

#include "Settings.h"

namespace vmi {

vmi::Settings* vmi::Settings::instance = NULL;

Settings::Settings() {
	if( this->openConfigFile("vmiids.cfg") ||
			this->openConfigFile("/etc/vmiids.cfg") ){
	}
}

Settings::Settings(std::string fileName) {
	if(!this->openConfigFile(fileName)) throw ConfigFileException(fileName);
}

vmi::Settings::~Settings() {
	// TODO Auto-generated destructor stub
}

bool Settings::openConfigFile(std::string filename){
	FILE * configFile;

	if( (configFile = fopen (filename.c_str() , "r")) != NULL ){
		try {
			config.read(configFile);
			fclose (configFile);
			return true;
		}catch(libconfig::ParseException &e){
			return false;
		}
	}
	return false;
}

Settings *Settings::getInstance(){
	if (!instance)
		instance = new Settings();
	return instance;
}

libconfig::Setting &Settings::getSetting(std::string settingName){
	try {
		return this->config.lookup(settingName);
	}catch(libconfig::SettingNotFoundException &e){
			throw OptionNotFoundException(settingName);
	}
}

}
