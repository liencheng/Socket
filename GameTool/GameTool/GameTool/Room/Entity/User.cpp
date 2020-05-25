#include "User.h"

POOL_IMPL(User);

void User::Clean()
{
	m_UserGuid = 0;
	m_UserName = std::string();
	m_EntityId = 0;
}	