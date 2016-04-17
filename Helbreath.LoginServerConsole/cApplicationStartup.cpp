#include "cApplicationStartup.h"
#include <exception>

void cApplicationStartup::Startup()
{
	cLogging::LogToConsole("Starting up Helbreath Login Server \n");
	try {
		ConnectToDatabase();
		//loginServer->DoInitialSetup();
	}
	catch (std::exception &e) {
		cLogging::LogToConsole((char*)e.what());
	}
	cLogging::LogToConsole("Entering to main loop \n");
	while (1) {
		if (PeekMessage(&Message, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&Message, NULL, 0, 0)) {
				//return static_cast<int>(Message.wParam);
			}
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else WaitMessage();
	}
	scanf("%d");
}

void cApplicationStartup::ConnectToDatabase()
{
	ZeroMemory(loginServer->mySqlUser, sizeof(loginServer->mySqlUser));
	ZeroMemory(loginServer->mySqlPwd, sizeof(loginServer->mySqlPwd));
	if (!loginServer->ReadProgramConfigFile("LServer.cfg")) {
		//return FALSE;
	}

	cLogging::LogToConsole("Connecting to mySql database... \n");
	PutLogList("(!) Connecting to mySql database...");

	if (loginServer == NULL) {
		throw "Unknown error occured! Server = NULL";
	}
	UINT iResult = 0;
	mysql_init(&mySQL);
	if (!mysql_real_connect(&mySQL, loginServer->mySqlAddress, loginServer->mySqlUser, loginServer->mySqlPwd, "helbreath", loginServer->mySqlPort, NULL, NULL)) {
		iResult = loginServer->MyAux_Get_Error(&mySQL);
		mysql_close(&mySQL);
	}
	if (iResult != NULL) {
		if (iResult == 2003) PutLogList("(!!!) mySql server seems to be offline, please check the IP", WARN_MSG);
		mysql_close(&mySQL);		
	}
	PutLogList("-Connection to mySQL database was sucessfully established!");
	/*if (!loginServer->InitServer()) {
		//SAFEDELETE(Server);
	}*/
}

cApplicationStartup::cApplicationStartup()
{
	loginServer = new CLoginServer;
}


cApplicationStartup::~cApplicationStartup()
{
}
