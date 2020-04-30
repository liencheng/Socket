#pragma once
#include "../stdafx.h"

//////////////////////////////////////////////////////////////////////////
//todo:先行测试使用，后期要考虑多线程，多功能复用
class MyGuid
{
public:
	MyGuid()
	{
		m_guid_val = 0;
	}
	uint64 GenGuid(){ return m_guid_val++; }
private:
	uint64 m_guid_val;
};


extern MyGuid gUserGuid;

#define GEN_USER_GUID() gUserGuid.GenGuid()