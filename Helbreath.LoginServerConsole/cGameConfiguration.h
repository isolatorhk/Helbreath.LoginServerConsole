#pragma once

#include "windows.h"
#include "cLogging.h"
#include "defs.hpp"
#include <stdio.h>

class cGameConfiguration
{
public:
	char *ItemCfg, *Item2Cfg, *Item3Cfg, *BuildItemCfg, *DupItemIDCfg,
		*MagicCfg, *NoticementTxt, *NPCCfg, *PotionCfg, *QuestCfg,
		*SkillCfg, *CraftingCfg, *TeleportCfg;
	BOOL ReadConfig(char *FileName);
	cGameConfiguration();
	~cGameConfiguration();
private:
	BOOL IsSame(char *c1, char *c2);
	DWORD Filesize(FILE *stream);
};

