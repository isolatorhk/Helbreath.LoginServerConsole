#include "cGameConfiguration.h"

char * cGameConfiguration::GetConfigurationFileValue(char * fileName)
{
	return ConfigurationFiles.find(fileName)->second->Value;
}

BOOL cGameConfiguration::LoadConfiguration()
{
	std::map<char*, cConfigurationFile*>::iterator it = ConfigurationFiles.begin();
	for (it; it != ConfigurationFiles.end(); ++it)
	{
		if (!it->second->ReadConfig()) {
			return false;
		}		
	}
	return true;
}

cGameConfiguration::cGameConfiguration()
{	
	this->ConfigurationFilesNames = { "Item.cfg", "Item2.cfg", "Item3.cfg",
		"BuildItem.cfg", "DupItemID.cfg", "Magic.cfg", "noticement.txt", "NPC.cfg",
		"potion.cfg", "Quest.cfg", "Skill.cfg", "CraftItem.cfg", "Teleport.cfg", "Item4.cfg" };

	for (size_t i = 0; i < ConfigurationFilesNames.size(); i++)
	{
		ConfigurationFiles.insert(std::pair<char*, cConfigurationFile*>
			(ConfigurationFilesNames[i], new cConfigurationFile(ConfigurationFilesNames[i])));
	}	
}

cGameConfiguration::~cGameConfiguration()
{	
}