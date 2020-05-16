#include "User.h"

void User::Clean()
{
	m_EntityId = 0;
	m_ClientUser.Clean();
}