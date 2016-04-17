#pragma once

#include "LoginServer.h"
#include <stdio.h>
#include "cLogging.h"

class cApplicationStartup
{
public:
	void Startup();
	cApplicationStartup();
	~cApplicationStartup();
private:
	CLoginServer *loginServer;
	MSG Message;
};

