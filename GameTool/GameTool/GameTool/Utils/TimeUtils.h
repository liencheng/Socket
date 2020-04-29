#pragma once

#include "../stdafx.h"
#include <ctime>

class MyTime
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
