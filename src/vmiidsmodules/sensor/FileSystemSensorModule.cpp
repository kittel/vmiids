/*
 * FileSystemSensorModule.cpp
 *
 *  Created on: Jul 1, 2010
 *      Author: kittel
 */

#include "FileSystemSensorModule.h"

#include <cstdlib>
#include <gcrypt.h>

#include <dirent.h>
#include <iostream>

ADDDYNAMICSENSORMODULE(FileSystemSensorModule, __LINE__)
;

FileSystemSensorModule::FileSystemSensorModule() : SensorModule("FileSystemSensorModule") {
	//Get NotificationModule
	GETNOTIFICATIONMODULE(notify, ShellNotificationModule);

	GETOPTION(clearCacheCommand, this->clearCacheCommand);
	GETOPTION(fileSystemPath, this->fileSystemPath);
}

FileSystemSensorModule::~FileSystemSensorModule() {
	// TODO Auto-generated destructor stub
}

void FileSystemSensorModule::initSensorModule() {

}

bool FileSystemSensorModule::fileExists(const std::string absolutePath,
		struct stat * stFileInfo) {

	this->clearFSCache();

	if (!stFileInfo) {
		struct stat FileInfo;
		stFileInfo = &FileInfo;
	}
	if (stat(std::string().append(this->fileSystemPath).append(absolutePath).c_str(), stFileInfo) == 0) {
		return true;
	}
	return false;
}

void FileSystemSensorModule::openFileRO(const std::string absolutePath,
		std::ifstream *fileHandle) {
	this->clearFSCache();

	fileHandle->open(std::string().append(this->fileSystemPath).append(absolutePath).c_str(),
			std::ifstream::in);
	return;
}

void FileSystemSensorModule::getFileList(const std::string &directory, std::set<std::string> &directories, bool withdirs){
	DIR *d;
	struct dirent *dir;

	this->clearFSCache();
	d = opendir(std::string(this->fileSystemPath).append("/").append(directory).c_str());
	if (d == NULL) {
		return;
	}
	if (withdirs) directories.insert(directory);
	while ((dir = readdir(d))) {
		if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
			continue;
		}
		if (dir->d_type == DT_DIR) {
			this->getFileList(std::string(dir->d_name).insert(0, "/").insert(0,
							directory), directories, withdirs);
		} else {
			directories.insert(
					std::string(dir->d_name).insert(0, "/").insert(0, directory));
		}
	}
	closedir(d);
	return;
}

void FileSystemSensorModule::getFileSHA1Sum(const std::string &fileName, std::string &sha1Sum){
	this->clearFSCache();

	  std::ifstream fileHandle;
	  fileHandle.open(std::string().insert(0, this->fileSystemPath).append("/").append(fileName).c_str(), std::ifstream::in);

	  long begin,end;
	  begin = fileHandle.tellg();
	  fileHandle.seekg (0, std::ios::end);
	  end = fileHandle.tellg();
	  fileHandle.seekg (0, std::ios::beg);

	  char * fileContent = (char *) malloc(end-begin);

	  int count = 0;
	  while (fileHandle.good())
	    fileContent[count++] = fileHandle.get();

	  fileHandle.close();

	  int hash_len = gcry_md_get_algo_dlen( GCRY_MD_SHA1 );

	  unsigned char hash[ hash_len ];

	  char *out = (char *) malloc( sizeof(char) * ((hash_len*2)+1) );
	  char *p = out;

	  gcry_md_hash_buffer( GCRY_MD_SHA1, hash, fileContent, count - 1 );

	  for ( int i = 0; i < hash_len; i++, p += 2 )
	    snprintf ( p, 3, "%02x", hash[i] );

	  sha1Sum.append(out, sizeof(char) * ((hash_len*2)));

	  free(fileContent);
	  free( out );



}

bool FileSystemSensorModule::clearFSCache() {
	bool result = true;

	// To clear the file system cache and get the latest version of the rootkitvms file system.
	result = (system("sync") == -1) ? false : true;
	result = (system(this->clearCacheCommand.c_str()) == -1) ? false : true;
	return result;
}
