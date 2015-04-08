#include "ConfigParser.h"

ConfigParser::ConfigParser(const char* path) {
	this->m_vConfig = this->loadSettings(path);
}

ConfigParser::~ConfigParser() {
	
}

std::vector<std::string> ConfigParser::loadSettings(const char* path) {

	std::vector<std::string> wordList;

	std::string line;
	std::ifstream myfile (path);
	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
	      wordList.push_back( line );
	    }
	    myfile.close();
	  }

	  return wordList;
}

std::string ConfigParser::getVariable(const char* name, std::string value) {
	for (std::vector<std::string>::iterator it = this->m_vConfig.begin() ; it != this->m_vConfig.end(); ++it) {
		int iDelimiterPos = it->find("=");
		if(strcmp(it->substr(0,iDelimiterPos).c_str(),name)==0)
			return it->substr(iDelimiterPos+2,it->size()-iDelimiterPos-3);
	}

	return value;
}

int ConfigParser::getVariable(const char* name, int value) {
	for (std::vector<std::string>::iterator it = this->m_vConfig.begin() ; it != this->m_vConfig.end(); ++it) {
		int iDelimiterPos = it->find("=");
		if(strcmp(it->substr(0,iDelimiterPos).c_str(),name)==0) {
			return atoi(it->substr(iDelimiterPos+1,it->size()-iDelimiterPos-1).c_str());
		}
	}

	return value;
}