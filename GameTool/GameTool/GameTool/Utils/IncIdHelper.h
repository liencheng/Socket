
#pragma once
#include "../stdafx.h"

//////////////////////////////////////////////////////////////////////////
//todo:���в���ʹ�ã�����Ҫ���Ƕ��̣߳��๦�ܸ���

class IDTYPE
{
public:
	enum 
	{
		USER,
	};
};

class MyEntityId
{
public:
	MyEntityId()
	{
		m_id_val = 0;
	}
	int32 GenId(){ return m_id_val++; }
private:
	int32 m_id_val;
};


#define ID_OBJ(IDType) \
	g##IDType##ID
#define ID_DECL(IDType) \
	extern MyEntityId ID_OBJ(IDType)
#define ID_IMPL(IDType) \
	MyEntityId  ID_OBJ(IDType)
#define  INCID_GEN(IDType) \
	ID_OBJ(IDType).GenId()

ID_DECL(USER);

