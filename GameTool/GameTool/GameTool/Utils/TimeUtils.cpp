#include "TimeUtils.h"
#include "sys/timeb.h"
#include "windows.h"

time_t MyTimeUtils::m_AnistimeSec = 0;
tm * MyTimeUtils::m_LocalTime = nullptr;
uint64 MyTimeUtils::m_AnsitimeMilliSec = 0;


int64 MyTimeUtils::GetAnsiTime()
{
	time_t anistime = time(nullptr);
	return anistime;
}

uint64 MyTimeUtils::GetAnsiTimeMilliSec()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	time_t anistime = time(nullptr);
	return sys.wMilliseconds + (uint64)anistime * 1000;
}

tm MyTimeUtils::GetLocaltime()
{
	int64 anistimesec = GetAnsiTime();
	tm* pTm;
	pTm = gmtime((time_t*)&anistimesec);
	return *pTm;
}
void MyTimeUtils::init()
{
	m_AnistimeSec = -1;
	m_LocalTime = nullptr;
}
void MyTimeUtils::tick()
{
	time_t ansitime;
	time(&ansitime);
	m_AnistimeSec = ansitime;
	m_LocalTime = localtime(&m_AnistimeSec);

	SYSTEMTIME sys;
	GetLocalTime(&sys);
	m_AnsitimeMilliSec = (uint64)m_AnistimeSec*1000 + sys.wMilliseconds;
}


bool MyClockTime::DiffSec()
{

	int nAnsiSec = MyTimeUtils::GetAnsiTime();
	if (m_AnsitimeSec != nAnsiSec)
	{
		return true;
	}
	return false;
}

bool MyClockTime::DiffMin()
{
	tm &rCurTM = MyTimeUtils::GetLocaltime();
	if (m_LastTickTimeTm.tm_year != rCurTM.tm_year
		|| m_LastTickTimeTm.tm_mon != rCurTM.tm_mon
		|| m_LastTickTimeTm.tm_mday != rCurTM.tm_mday
		|| m_LastTickTimeTm.tm_hour != rCurTM.tm_hour
		|| m_LastTickTimeTm.tm_min != rCurTM.tm_min)
	{
		return true;
	}
	return false;
}

bool MyClockTime::DiffHour()
{
	tm &rCurTM = MyTimeUtils::GetLocaltime();
	if (m_LastTickTimeTm.tm_year != rCurTM.tm_year
		|| m_LastTickTimeTm.tm_mon != rCurTM.tm_mon
		|| m_LastTickTimeTm.tm_mday != rCurTM.tm_mday
		|| m_LastTickTimeTm.tm_hour != rCurTM.tm_hour)
	{
		return true;
	}
	return false;
}

void MyClockTime::Tick()
{
	tm &rCurTM = MyTimeUtils::GetLocaltime();
	m_LastTickTimeTm = rCurTM;

	int64 nCurAnsitimeSec = MyTimeUtils::GetAnsiTime();
	m_AnsitimeSec = nCurAnsitimeSec;
}
