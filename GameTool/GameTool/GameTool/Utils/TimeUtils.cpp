#include "TimeUtils.h"

time_t MyTime::m_AnistimeSec = 0;
tm * MyTime::m_LocalTime = nullptr;

int64 MyTime::GetAnsiTime()
{
	if (m_AnistimeSec < 0)
	{
		time_t anistime = time(0);
		m_AnistimeSec = anistime;
	}
	return m_AnistimeSec;
}

tm& MyTime::GetLocaltime()
{
	if (nullptr == m_LocalTime)
	{
		int64 anistimesec = GetAnsiTime();
		m_LocalTime = gmtime((time_t*)(&anistimesec));
	}
	return *(m_LocalTime);
}
void MyTime::init()
{
	m_AnistimeSec = -1;
	m_LocalTime = nullptr;
}
void MyTime::tick()
{
	time_t ansitime;
	time(&ansitime);
	m_AnistimeSec = ansitime;
	m_LocalTime = localtime(&m_AnistimeSec);
}
