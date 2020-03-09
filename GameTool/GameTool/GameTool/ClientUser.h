#pragma once

#include "stdafx.h"
#include "MySocket.h"

class ClientUser
{
public:
	ClientUser(int userId, MySocket& sock)
		:m_UserId(userId)
		, m_Socket(sock)
	{};
	~ClientUser() {};

public:
	int m_UserId;
	MySocket m_Socket;
};
