#pragma once

#include "LoginServer.h"
#include <stdio.h>
#include "cLogging.h"

class cApplicationStartup
{
public:
	void Startup();
	void ConnectToDatabase();
	cApplicationStartup();
	~cApplicationStartup();
private:
	CLoginServer *loginServer;
	MSG Message;
};

