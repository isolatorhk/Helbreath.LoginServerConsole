#include "LoginServerConfiguration.h"

using json = nlohmann::json;
using namespace std;

bool LoginServerConfiguration::LoadConfiguration()
{
	cLogging::Log("Starting reading LServer.json... \n");
	ifstream ifs("LServer.json");

	if (!ifs.is_open()) {
		cLogging::Log("Can't open LServer.json... \n");
		return false;
	}
	string str(istreambuf_iterator<char>{ifs}, {});
	loginServerConfiguration = json::parse(str);

	if (loginServerConfiguration.find("login-server-address") != loginServerConfiguration.end()) {
		string loginServerAddress = loginServerConfiguration.at("login-server-address");
		this->ListenAddress = loginServerAddress;
		cLogging::Log("Login server address has been set up : " + loginServerAddress);
	}
	else {
		cLogging::Log("Couldn't find login-server-address");
		return false;
	}

	if (loginServerConfiguration.find("login-server-port") != loginServerConfiguration.end()) {
		int loginServerPort = loginServerConfiguration.at("login-server-port");
		this->ListenPort = loginServerPort;
		cLogging::Log("Login server port has been set up : " + to_string(loginServerPort));
	}
	else {
		cLogging::Log("Couldn't find login-server-port");
		return false;
	}

	if (loginServerConfiguration.find("gate-server-port") != loginServerConfiguration.end()) {
		int gateServerPort = loginServerConfiguration.at("gate-server-port");
		this->GateServerPort = gateServerPort;
		cLogging::Log("Gate server port has been set up : " + to_string(gateServerPort));
	}
	else {
		cLogging::Log("Couldn't find gate-server-port");
		return false;
	}

	if (loginServerConfiguration.find("mysql-address") != loginServerConfiguration.end()) {
		string mysqlAddress = loginServerConfiguration.at("mysql-address");
		this->MySqlAddress = mysqlAddress;
		cLogging::Log("MySQL address has been set up : " + mysqlAddress);
	}
	else {
		cLogging::Log("Couldn't find mysql-address");
		return false;
	}

	if (loginServerConfiguration.find("mysql-server-port") != loginServerConfiguration.end()) {
		int mysqlServerPort = loginServerConfiguration.at("mysql-server-port");
		this->MySqlPort = mysqlServerPort;
		cLogging::Log("MySQL server port has been set up : " + to_string(mysqlServerPort));
	}
	else {
		cLogging::Log("Couldn't find mysql-server-port");
		return false;
	}

	if (loginServerConfiguration.find("mysql-user") != loginServerConfiguration.end()) {
		string mysqlUser = loginServerConfiguration.at("mysql-user");
		this->MySqlUser = mysqlUser;
		cLogging::Log("MySQL user has been set up : " + mysqlUser);
	}
	else {
		cLogging::Log("Couldn't find mysql-user");
		return false;
	}

	if (loginServerConfiguration.find("mysql-password") != loginServerConfiguration.end()) {
		string mysqlPassword = loginServerConfiguration.at("mysql-password");
		this->MySqlPassword = mysqlPassword;
		cLogging::Log("MySQL password has been set up");
	}
	else {
		cLogging::Log("Couldn't find mysql-password");
		return false;
	}
	return true;
}

LoginServerConfiguration::LoginServerConfiguration()
{
}


LoginServerConfiguration::~LoginServerConfiguration()
{
}