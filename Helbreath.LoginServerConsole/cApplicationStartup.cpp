#include "cApplicationStartup.h"
#include <exception>

void cApplicationStartup::Startup()
{	
	cLogging::LogToConsole("Starting up Helbreath Login Server \n");	
	try {
		loginServer->DoInitialSetup();
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

cApplicationStartup::cApplicationStartup()
{
	loginServer = new CLoginServer;
}


cApplicationStartup::~cApplicationStartup()
{
}
