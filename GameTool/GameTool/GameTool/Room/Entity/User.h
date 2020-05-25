#pragma once

#include "../../ClientUser.h"
#include "../../Utils/ObjPool.h"

class User
{
public:
	User(){
		Clean();
	}

	~User(){}

	void Clean();

	int32 GetEntityId() const { return m_EntityId; }
	void SetEntityId(int32 nVal){ m_EntityId = nVal; }
	

private:
	uint64_t m_UserGuid;
	std::string m_UserName;
	int32 m_EntityId;

};

POOL_DEF(User);