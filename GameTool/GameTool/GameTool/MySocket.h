#pragma  once
#include "stdafx.h"
#include "winsock2.h"
#include "windows.h"
#include "GameDefine/GameDefine_Packet.h"

class MySocket
{
public:
	MySocket() {};
	MySocket(SOCKET sock, sockaddr_in addr_in)
		:m_socket(sock),
		m_addr_in(addr_in)
	{}
	~MySocket(){}

public:
	SOCKET  m_socket;
	sockaddr_in m_addr_in;

public:
	bool IsNetworkLost()const
	{
		int64 nCurAnistime = MyTimeUtils::GetAnsiTime();
		return nCurAnistime - m_LastActiveTime >= NETWORKDLOSTTIME;
	}
	void SetLastActiveTime(int val) { m_LastActiveTime = val; }
private:
	int m_LastActiveTime = 0;
};