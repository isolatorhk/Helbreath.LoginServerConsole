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
	std::map<char*, cConfigurationFile*> ConfigurationFiles;	
	BOOL LoadConfiguration();
	cGameConfiguration();
	~cGameConfiguration();
private:
	std::vector<char*> ConfigurationFilesNames;
};

