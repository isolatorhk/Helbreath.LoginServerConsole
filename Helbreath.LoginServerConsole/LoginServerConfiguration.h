#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "cLogging.h"
#include "packages\json.hpp"

class LoginServerConfiguration
{
public:
	std::string MySqlUser;
	std::string MySqlPassword;
	std::string ListenAddress;
	std::string MySqlAddress;
	std::string PermittedAddress;
	int ListenPort;
	int GateServerPort;
	int MySqlPort;
	bool LoadConfiguration();
	LoginServerConfiguration();
	~LoginServerConfiguration();
private:
	nlohmann::json loginServerConfiguration;
	bool SetIntConfiguration();
};

