#pragma once

#include "windows.h"
#include "cLogging.h"
#include "defs.hpp"
#include <vector>
#include <map>
#include <string>
#include "cConfigurationFile.h"

class cGameConfiguration
{
public:		
	char* GetConfigurationFileValue(char *fileName);
	BOOL LoadConfiguration();
	cGameConfiguration();
	~cGameConfiguration();
private:
	std::map<char*, cConfigurationFile*> ConfigurationFiles;
	std::vector<char*> ConfigurationFilesNames;
};

