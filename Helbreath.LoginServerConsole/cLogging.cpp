#include "windows.h"
#include "cLogging.h"
#include "defs.hpp"
#include <stdio.h>
#include "DIRECT.H"

void cLogging::Log(char * cMsg, BYTE MsgLvl, BOOL PutOnFile, char * FileName)
{	
	LogToFile(cMsg, FileName);
	LogToConsole(cMsg);
}

void cLogging::Log(std::string logMessage)
{
	LogToFile((char*)logMessage.c_str());
	LogToConsole((char*)logMessage.c_str());
}

void cLogging::LogToFile(char * cStr, char *FileName)
{
	LogToFileOld(cStr, FileName);
}

void cLogging::LogToConsole(char * cStr)
{
	char cBuffer[MAXLOGLINESIZE + 100];
	ZeroMemory(cBuffer, sizeof(cBuffer));
	strcat(cBuffer, cStr);
	strcat(cBuffer, " \n");
	printf(cBuffer);
}

cLogging::cLogging()
{
}


cLogging::~cLogging()
{
}

void cLogging::LogToFileOld(char * cStr, char *FileName)
{
	char Txt[50], FName[100];
	FILE * pFile;
	char cBuffer[MAXLOGLINESIZE + 100];
	SYSTEMTIME SysTime;

	if (strlen(cStr) > MAXLOGLINESIZE) return;
	GetLocalTime(&SysTime);

	_mkdir("Logs");

	if (FileName == NULL)
		pFile = fopen("Events.log", "at");
	else if (IsSame(FileName, GM_LOGFILE)) {
		_mkdir("Logs/GM");
		ZeroMemory(Txt, sizeof(Txt));
		ZeroMemory(FName, sizeof(FName));
		sprintf(Txt, "GM Events %4d-%02d-%02d.log", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
		SafeCopy(FName, FileName);
		strcat(FName, Txt);
		pFile = fopen(FName, "at");
	}
	else if (IsSame(FileName, PLAYER_LOGFILE)) {
		_mkdir("Logs/Player");
		ZeroMemory(Txt, sizeof(Txt));
		ZeroMemory(FName, sizeof(FName));
		sprintf(Txt, "Player Events %4d-%02d-%02d.log", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
		SafeCopy(FName, FileName);
		strcat(FName, Txt);
		pFile = fopen(FName, "at");
	}
	else if (IsSame(FileName, ITEM_LOGFILE)) {
		_mkdir("Logs/Item");
		ZeroMemory(Txt, sizeof(Txt));
		ZeroMemory(FName, sizeof(FName));
		sprintf(Txt, "Item Events %4d-%02d-%02d.log", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
		SafeCopy(FName, FileName);
		strcat(FName, Txt);
		pFile = fopen(FName, "at");
	}
	else if (IsSame(FileName, CRUSADE_LOGFILE)) {
		_mkdir("Logs/Crusade");
		ZeroMemory(Txt, sizeof(Txt));
		ZeroMemory(FName, sizeof(FName));
		sprintf(Txt, "Crusade Events %4d-%02d-%02d.log", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
		SafeCopy(FName, FileName);
		strcat(FName, Txt);
		pFile = fopen(FName, "at");
	}
	else if (IsSame(FileName, XSOCKET_LOGFILE) || IsSame(FileName, GSPACKET_LOGFILE) || IsSame(FileName, CLIENTPACKET_LOGFILE) ||
		IsSame(FileName, GSUNKNOWNMSG_LOGFILE) || IsSame(FileName, CLIENTUNKNOWNMSG_LOGFILE))
		pFile = fopen(FileName, "ab");
	else
		pFile = fopen(FileName, "at");

	if (pFile == NULL) return;

	ZeroMemory(cBuffer, sizeof(cBuffer));

	sprintf(cBuffer, "(%4d:%02d:%02d:%02d:%02d) - ", SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute);
	strcat(cBuffer, cStr);
	strcat(cBuffer, "\n");

	fwrite(cBuffer, 1, strlen(cBuffer), pFile);
	fclose(pFile);
}

bool cLogging::IsSame(char *c1, char *c2)
{
	DWORD size1, size2;

	size1 = strlen(c1);
	size2 = strlen(c2);
	if (size1 == size2 && memcmp(c1, c2, size1) == 0) return true;
	else return false;
}

void cLogging::SafeCopy(char *c1, char *c2, DWORD lenght)
{
	register DWORD d;

	if (lenght == 0) {
		d = 0;
		if (c2[d] == NULL) return;
		while (c2[d] != NULL) {
			c1[d] = c2[d];
			d++;
		}
	}
	else for (d = 0; d < lenght; d++) c1[d] = c2[d];

	c1[d] = NULL;
}