#pragma once

#include <winsock2.h>
#include <windows.h>
#include "LoginServer.h"
#include <stdio.h>
#include "cLogging.h"

class cApplicationStartup
{
public:
	void Startup();
	void ConnectToDatabase();
	void StartLoginServer();
	HWND CreateBackgroundWindow();	
	cApplicationStartup();
	~cApplicationStartup();
private:
	//LRESULT CALLBACK BackgroundWindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	CLoginServer *loginServer;
	MSG Message;
};

