#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

#include <sys/types.h>
#include <malloc.h>
#include <regex.h>
#include <stdlib.h>

int main (int argc, char** argv){

	std::multimap<std::string,std::string> rkvars;

	std::ifstream fileHandle(argv[1], std::ifstream::in);
	std::string currentLine;

	std::string currentVariableName;
	std::string currentVariableContent;

	bool lineInteresting = false;

	int         result;
	regex_t     rxReturn;
	regex_t     rxDoSystemCheck;
	regex_t     rxEmptyLine;
	regex_t     rxCommentLine;
	regex_t     rxFirstLine;
	regex_t     rxVariables;
	regmatch_t  matches[100];

	result = regcomp( &rxReturn, "[:space:]*return", REG_EXTENDED );
	result = regcomp( &rxDoSystemCheck, "^do_system_check_initialisation().*$", REG_EXTENDED );
	result = regcomp( &rxEmptyLine, "^[:space:]*$", REG_EXTENDED );
	result = regcomp( &rxCommentLine, "([:space:]|\t)+#", REG_EXTENDED );
	result = regcomp( &rxFirstLine, "\\s*(\\w*)=(.*)", REG_EXTENDED );
	result = regcomp( &rxVariables, "\\$\\{(\\w*)\\}\\s*\\$\\{(\\w*)\\}\\s*\\$\\{(\\w*)\\}\\s*", REG_EXTENDED );

	while (std::getline(fileHandle, currentLine)){

		memset(matches, 0, sizeof(matches));
		if(lineInteresting) {
			if(regexec( &rxReturn, currentLine.c_str(), 0, 0, 0 ) == 0){
				lineInteresting = false;
				continue;
			}

			if(regexec( &rxEmptyLine, currentLine.c_str(), 0, 0, 0 ) == 0 ||
			             regexec( &rxCommentLine, currentLine.c_str(), 0, 0, 0 ) == 0){
				if(!currentVariableName.empty()){
					currentVariableName.clear();
				}
				continue;
			}
			
			result = currentLine.find("${RKHROOTDIR}");
			if (result != std::string::npos){
				currentLine.replace(result, 13 , "");
			}
			
			if(regexec( &rxFirstLine, currentLine.c_str(), 5, matches, 0 ) == 0 ){
				currentVariableName = currentLine.substr(matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
				currentVariableContent = currentLine.substr(matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
				memset(matches, 0, sizeof(matches));
				if(currentVariableContent[0] == '"') currentVariableContent.replace(0, 1, "");
				if(currentVariableContent[currentVariableContent.size()-1] == '"') currentVariableContent.replace(currentVariableContent.size()-1, 1, "");
				while((result = currentVariableContent.find("\n")) != std::string::npos){
					currentVariableContent.replace(result, 1, "");
				}
				if(currentVariableContent.empty()){
					currentVariableName.clear();
					continue;
				}
				if(regexec( &rxVariables, currentLine.c_str(), 10, matches, 0 ) == 0 ){
					for (int i = 0; i <= rxVariables.re_nsub; i++) {
						if (matches[i].rm_so != -1) {
							std::multimap<std::string, std::string>::iterator it;
							std::pair<std::multimap<std::string, std::string>::iterator,std::multimap<std::string, std::string>::iterator> ret;
							std::string currentVar = currentLine.substr(matches[i].rm_so, matches[i].rm_eo - matches[i].rm_so);
							ret = rkvars.equal_range(currentVar);
							for (it=ret.first; it!=ret.second; ++it)
								rkvars.insert(std::pair<std::string, std::string>(currentVariableName, (*it).second));
						}
					}
				}else{
					rkvars.insert(std::pair<std::string, std::string>(currentVariableName, currentVariableContent));
				}
			}else if(!currentVariableName.empty()){
				currentVariableContent = currentLine;
				while(currentVariableContent[0] == '\t' || currentVariableContent[0] == ' ') currentVariableContent.replace(0, 1, "");
				while(currentVariableContent[currentVariableContent.size()-1] == ' ') currentVariableContent.replace(currentVariableContent.size()-1, 1, "");
				for(int i = 0 ; i < currentVariableContent.size(); i++){
					if(currentVariableContent[i] == '\\'){
						currentVariableContent.replace(i, 1, "\\\\");
						i++;
					}
				}
				if(currentVariableContent[currentVariableContent.size()-1] == '"') currentVariableContent.replace(currentVariableContent.size()-1, 1, "");
				if(regexec( &rxVariables, currentLine.c_str(), 10, matches, 0 ) == 0 ){
					for (int i = 0; i <= rxVariables.re_nsub; i++) {
						if (matches[i].rm_so != -1) {
							std::multimap<std::string, std::string>::iterator it;
							std::pair<std::multimap<std::string, std::string>::iterator,std::multimap<std::string, std::string>::iterator> ret;
							std::string currentVar = currentLine.substr(matches[i].rm_so, matches[i].rm_eo - matches[i].rm_so);
							ret = rkvars.equal_range(currentVar);
							for (it=ret.first; it!=ret.second; ++it)
								rkvars.insert(std::pair<std::string, std::string>(currentVariableName, (*it).second));
						}
					}
				}else{
					rkvars.insert(std::pair<std::string, std::string>(currentVariableName, currentVariableContent));
				}
			}else{
				exit(0);
			}
		}else{
			if(regexec( &rxDoSystemCheck, currentLine.c_str(), 0, 0, 0 ) == 0){
				lineInteresting = true;
			}
		}
	}

	regfree( &rxReturn );
	regfree( &rxDoSystemCheck );
	regfree( &rxEmptyLine );
	regfree( &rxCommentLine );
	regfree( &rxFirstLine );
	regfree( &rxVariables );
	
	fileHandle.close();

	for(std::multimap<std::string, std::string>::iterator it = rkvars.begin(); it != rkvars.end(); ++it){
		std::cout << (*it).first << " -> " << (*it).second << std::endl;
	}

	return 0;
}
