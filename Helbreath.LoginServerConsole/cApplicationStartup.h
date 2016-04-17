#pragma once

#include <winsock2.h>
#include <windows.h>
#include "LoginServer.h"
#include <stdio.h>
#include "cLogging.h"
#include "cServerTimer.h"

class cApplicationStartup
{
public:
	void Startup();
	void ConnectToDatabase();
	void StartLoginServer();
	HWND CreateBackgroundWindow();
	MMRESULT _StartTimer();
	cApplicationStartup();
	~cApplicationStartup();
private:
	cServerTimer *serverTimer;
	//LRESULT CALLBACK BackgroundWindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	
	MSG Message;
};

