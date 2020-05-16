
#include "../stdafx.h"
#include "MyRoutine.h"
#include "../Utils/TimeUtils.h"

bool myroutine::reach_tick()
{
	uint64 ncurtime = MyTimeUtils::GetAnsiTimeMilliSec();
	uint64 npasttime = ncurtime - m_last_tick_time_ms;

	if (npasttime >= HEART_BEAT_SLOW)
	{
		MyLog::Log("slow beat. rt(%d)", m_id);
	}

	if (npasttime > m_tick_interval_ms)
	{
		return true;
	}
	return false;
}

void myroutine::tick()
{
	uint64 ncurtime = MyTimeUtils::GetAnsiTimeMilliSec();
	m_last_tick_time_ms = ncurtime;
	tick_routine();
}