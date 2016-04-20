#include "cGameConfiguration.h"

BOOL cGameConfiguration::LoadConfiguration()
{
	for (size_t i = 0; i < ConfigurationFiles.size(); i++)
	{
		if (!ReadConfig(ConfigurationFiles[i])) {
			return false;	
		}
	}
	return true;
}

cGameConfiguration::cGameConfiguration()
{
	ConfigurationFiles = { "Item.cfg", "Item2.cfg", "Item3.cfg", "BuildItem.cfg",
		"DupItemID.cfg", "Magic.cfg", "noticement.txt", "NPC.cfg",
		"potion.cfg", "Quest.cfg", "Skill.cfg", "CraftItem.cfg", "Teleport.cfg" };
}

cGameConfiguration::~cGameConfiguration()
{

}

BOOL cGameConfiguration::ReadConfig(char * FileName)
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

		if (IsSame(FileName, "Item.cfg")) {
			ItemCfg = new char[dwFileSize + 2];
			ZeroMemory(ItemCfg, dwFileSize + 2);
			fread(ItemCfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "Item2.cfg")) {
			Item2Cfg = new char[dwFileSize + 2];
			ZeroMemory(Item2Cfg, dwFileSize + 2);
			fread(Item2Cfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "Item3.cfg")) {
			Item3Cfg = new char[dwFileSize + 2];
			ZeroMemory(Item3Cfg, dwFileSize + 2);
			fread(Item3Cfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "BuildItem.cfg")) {
			BuildItemCfg = new char[dwFileSize + 2];
			ZeroMemory(BuildItemCfg, dwFileSize + 2);
			fread(BuildItemCfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "DupItemID.cfg")) {
			DupItemIDCfg = new char[dwFileSize + 2];
			ZeroMemory(DupItemIDCfg, dwFileSize + 2);
			fread(DupItemIDCfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "Magic.cfg")) {
			MagicCfg = new char[dwFileSize + 2];
			ZeroMemory(MagicCfg, dwFileSize + 2);
			fread(MagicCfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "noticement.txt")) {
			NoticementTxt = new char[dwFileSize + 2];
			ZeroMemory(NoticementTxt, dwFileSize + 2);
			fread(NoticementTxt, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "NPC.cfg")) {
			NPCCfg = new char[dwFileSize + 2];
			ZeroMemory(NPCCfg, dwFileSize + 2);
			fread(NPCCfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "potion.cfg")) {
			PotionCfg = new char[dwFileSize + 2];
			ZeroMemory(PotionCfg, dwFileSize + 2);
			fread(PotionCfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "Quest.cfg")) {
			QuestCfg = new char[dwFileSize + 2];
			ZeroMemory(QuestCfg, dwFileSize + 2);
			fread(QuestCfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "Skill.cfg")) {
			SkillCfg = new char[dwFileSize + 2];
			ZeroMemory(SkillCfg, dwFileSize + 2);
			fread(SkillCfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "CraftItem.cfg")) {
			CraftingCfg = new char[dwFileSize + 2];
			ZeroMemory(CraftingCfg, dwFileSize + 2);
			fread(CraftingCfg, dwFileSize, 1, pFile);
		}
		else if (IsSame(FileName, "Teleport.cfg")) {
			TeleportCfg = new char[dwFileSize + 2];
			ZeroMemory(TeleportCfg, dwFileSize + 2);
			fread(TeleportCfg, dwFileSize, 1, pFile);
		}
		else {
			sprintf(Txt100, "(!) Cannot handle configuration file [%s].", File);
			cLogging::Log(Txt100, WARN_MSG, TRUE, ERROR_LOGFILE);
			cLogging::Log("(!!!) Stopped!", WARN_MSG);
		}

		if (pFile != NULL) fclose(pFile);
		return TRUE;
	}
}

BOOL cGameConfiguration::IsSame(char * c1, char * c2)
{
	DWORD size1, size2;

	size1 = strlen(c1);
	size2 = strlen(c2);
	if (size1 == size2 && memcmp(c1, c2, size1) == 0) return true;
	else return false;
}

DWORD cGameConfiguration::Filesize(FILE * stream)
{
	long curpos, length;

	curpos = ftell(stream);
	fseek(stream, 0L, SEEK_END);
	length = ftell(stream);
	fseek(stream, curpos, SEEK_SET);
	return length;
}
