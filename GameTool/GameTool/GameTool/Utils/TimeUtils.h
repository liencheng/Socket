#pragma once

#include "../stdafx.h"
#include <ctime>

class MyTimeUtils
{
private:
	static time_t m_AnistimeSec;
	static tm* m_LocalTime;
public:
	static int64 GetAnsiTime();
	static tm& GetLocaltime();
	static void init();
	static void tick();
	
};


class MyClockTime
{
public:
	MyClockTime()
	{
		memset(&m_LastTickTimeTm, 0, sizeof(m_LastTickTimeTm));
	}
public:
	bool DiffSec();
	bool DiffMin();
	bool DiffHour();
	void Tick();
private:
	tm m_LastTickTimeTm;
	time_t m_AnsitimeSec;
};