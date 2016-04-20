#include "cConfigurationFile.h"



BOOL cConfigurationFile::ReadConfig()
{
	FILE * pFile;
	DWORD  dwFileSize;
	char   File[50], Txt100[100];

	ZeroMemory(Txt100, sizeof(Txt100));
	ZeroMemory(File, sizeof(File));
	sprintf(File, "Config/%s", FileName);
	pFile = fopen(File, "rt");
	if (pFile == NULL) {
		sprintf(Txt100, "(!) Cannot open configuration file [%s].", File);
		cLogging::Log(Txt100, WARN_MSG, TRUE, ERROR_LOGFILE);
		cLogging::Log("(!!!) Stopped!", WARN_MSG);
		return FALSE;
	}
	else {
		sprintf(Txt100, "(!) Reading configuration file [%s]...", File);
		cLogging::Log(Txt100);
		dwFileSize = Filesize(pFile);
		this->Value = new char[dwFileSize + 2];
		ZeroMemory(this->Value, dwFileSize + 2);
		fread(this->Value, dwFileSize, 1, pFile);		
		if (pFile != NULL) {
			fclose(pFile);
		}
		return TRUE;
	}
}

cConfigurationFile::cConfigurationFile(char* fileName)
{
	this->FileName = fileName;
}


cConfigurationFile::~cConfigurationFile()
{
}

DWORD cConfigurationFile::Filesize(FILE * stream)
{
	long curpos, length;

	curpos = ftell(stream);
	fseek(stream, 0L, SEEK_END);
	length = ftell(stream);
	fseek(stream, curpos, SEEK_SET);
	return length;
}