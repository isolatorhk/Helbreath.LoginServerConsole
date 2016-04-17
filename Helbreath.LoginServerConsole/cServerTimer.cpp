#include "cServerTimer.h"

cServerTimer::cServerTimer()
{	
}

void cServerTimer::_StopTimer(MMRESULT timerid)
{
	TIMECAPS caps;

	if (timerid != 0) {
		timeKillEvent(timerid);
		timerid = 0;
		timeGetDevCaps(&caps, sizeof(caps));
		timeEndPeriod(caps.wPeriodMin);
	}
}

cServerTimer::~cServerTimer()
{
}
