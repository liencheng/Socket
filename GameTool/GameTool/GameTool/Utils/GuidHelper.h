#pragma once
#include "../stdafx.h"

//////////////////////////////////////////////////////////////////////////
//todo:���в���ʹ�ã�����Ҫ���Ƕ��̣߳��๦�ܸ���
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