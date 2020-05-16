#pragma once

#include "../../ClientUser.h"

class User
{
public:
	User(){
		Clean();
	}

	~User(){}

	void Clean();
	void Tick()
	{
		m_ClientUser.Tick();
	}

	int32 GetEntityId() const { return m_EntityId; }
	void SetEntityId(int32 nVal){ m_EntityId = nVal; }
	
	void SetClientUser(const ClientUser &rClientUser){ m_ClientUser = rClientUser; }
	ClientUser& GetClientUser() { return m_ClientUser; }

private:
	int32 m_EntityId;
	ClientUser	m_ClientUser;
};