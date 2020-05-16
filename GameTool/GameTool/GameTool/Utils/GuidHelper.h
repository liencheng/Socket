#pragma once
#include "../stdafx.h"

//////////////////////////////////////////////////////////////////////////
//todo:先行测试使用，后期要考虑多线程，多功能复用

class GUIDTYPE
{
public:
	enum 
	{
		USER,
	};
};

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
#define GUID_OBJ(GuidType) \
	g##GuidType##Guid
#define GUID_DECL(GuidType) \
	extern MyGuid GUID_OBJ(GuidType)
#define GUID_IMPL(GuidType) \
	MyGuid GUID_OBJ(GuidType)
#define  GUID_GEN(GuidType) \
	GUID_OBJ(GuidType).GenGuid()


GUID_DECL(USER);

