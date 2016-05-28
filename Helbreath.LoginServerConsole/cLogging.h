#pragma once
#include <stdio.h>
#include <iostream>
#include "windows.h"

class cLogging
{
public:		
	static void Log(char * cMsg, BYTE MsgLvl = NULL, BOOL PutOnFile = NULL, char *FileName = NULL);
	static void Log(std::string logMessage);
	static void LogToFile(char * cStr, char *FileName = NULL);
	static void LogToConsole(char * cStr);
	cLogging();
	~cLogging();
private:
	static void LogToFileOld(char * cStr, char *FileName);
	static bool IsSame(char *c1, char *c2);
	static void SafeCopy(char *c1, char *c2, DWORD lenght = 0);
};

