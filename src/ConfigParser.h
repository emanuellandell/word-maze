#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>

class ConfigParser {

public:
	ConfigParser(const char* path);
	~ConfigParser();

	std::vector<std::string> loadSettings(const char* path);
	std::string getVariable(const char* name, std::string value = "");
	int getVariable(const char* name, int value = 0);	

private:
	std::vector<std::string> m_vConfig;

};