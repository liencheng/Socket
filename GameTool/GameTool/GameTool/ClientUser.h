#pragma once

#include "stdafx.h"
#include "MySocket.h"
#include <queue>
#include "GameDefine/GameDefine_Packet.h"
#include "Packet/PbMsg.pb.h"

class InputStream
{
public:
	InputStream(){ Clean(); };

	void Clean()
	{
		while (m_Data.size()>0)
		{
			m_Data.pop();
		}
	}
	void Write(byte * pByte, int len);
	bool ReadPacket(byte *pBuf, int len);
	bool ReadHeader(int &nPackType, int &nPackSize);
private:
	std::queue<byte> m_Data;
};

class ClientUser
{
public:
	ClientUser(int userId, MySocket& sock)
		:m_UserId(userId)
		, m_socket(sock)
	{
		Clean();
	};
	~ClientUser() {};

	void Clean()
	{
		m_CurPackType = PACKET_TYPE::INVALID;
		m_SockData.Clean();
	}

	InputStream &GetInputStream(){ return m_SockData; }

	void  ProcessInput();

public:
	void RcvPacket(const Protobuf::CS_PING& rPacket) 
	{
		std::cout << "rcv packet::ping" << std::endl;
	};


public:
	int m_UserId;
	MySocket m_socket;
private:
	int		m_CurPackSize = 0;
	PACKET_TYPE m_CurPackType = PACKET_TYPE::INVALID;
	InputStream m_SockData;
		
};
