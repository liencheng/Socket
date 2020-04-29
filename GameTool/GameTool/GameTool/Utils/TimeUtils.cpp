#include "TimeUtils.h"

time_t MyTime::m_AnistimeSec = 0;
tm * MyTime::m_LocalTime = nullptr;

int64 MyTime::GetAnsiTime()
{
	if (m_AnistimeSec < 0)
	{
		time_t anistime = time(nullptr);
		m_AnistimeSec = anistime;
	}
	return m_AnistimeSec;
}

tm& MyTime::GetLocaltime()
{
	if (nullptr == m_LocalTime)
	{
		int64 anistimesec = GetAnsiTime();
		tm* pTm;
		pTm = gmtime((time_t*)&anistimesec);
		m_LocalTime = pTm;
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
