#pragma once
#include "windows.h"

class cServerTimer
{
public:
	cServerTimer();
	void _StopTimer(MMRESULT timerid);
	~cServerTimer();	
};
