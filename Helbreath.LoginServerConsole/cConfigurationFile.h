#pragma once

#include "windows.h"
#include "cLogging.h"
#include "defs.hpp"
#include <stdio.h>

class cConfigurationFile
{
public:
	char* FileName;
	char* Value;
	BOOL ReadConfig();
	cConfigurationFile(char* fileName);
	~cConfigurationFile();
private:
	DWORD Filesize(FILE *stream);
};

