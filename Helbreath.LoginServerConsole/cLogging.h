#pragma once
class cLogging
{
public:		
	static void Log(char * cMsg, BYTE MsgLvl = NULL, BOOL PutOnFile = NULL, char *FileName = NULL);
	static void LogToFile(char * cStr, char *FileName = NULL);
	static void LogToConsole(char * cStr);
	cLogging();
	~cLogging();
private:
	static void LogToFileOld(char * cStr, char *FileName);
	static BOOL IsSame(char *c1, char *c2);
	static void SafeCopy(char *c1, char *c2, DWORD lenght = 0);
};

