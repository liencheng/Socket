#pragma once

#include "stdafx.h"
#include "MySocket.h"
#include <queue>
#include "GameDefine/GameDefine_Packet.h"
#include "Packet/PbMsg.pb.h"
#include "Public/SocketStream/SocketStream.h"
#include <iostream>
#include "Packet/PKHandlerMgr.h"


class ClientUser
{
public:
	ClientUser()
	{
		Clean();
	}
	ClientUser(int userId, MySocket& sock)
		:m_UserId(userId)
		, m_socket(sock)
	{
		Clean();
	};

	ClientUser(const ClientUser &rUser)
	{
		CopyFrom(rUser);
	}

	~ClientUser() {};

	void Clean()
	{
		m_CurPackType = PACKET_TYPE::INVALID;
		m_SockData.Clean();
		m_SendBuf.Clean();
		m_NetworkState = NetworkState::INVALID;
	}

	InputStream &GetInputStream(){ return m_SockData; }

	void Tick();
	void ProcessInput();
	void ProcessOutput();

public:
	void RcvPacket(const Protobuf::CS_PING& rPacket) 
	{
		SetLastActiveTime(MyTimeUtils::GetAnsiTime());
		/*
		MyLog::Log("rev packet::pint, time = %d, id = %d, name = %s"
			, rPacket.ansi_time()
			, rPacket.id()
			, rPacket.name().c_str());
		*/

		Protobuf::SC_PONG pak;
		pak.set_ansi_time(100);
		PKHandlerMgr::PushPak(pak, PACKET_TYPE::SC_PONG, *this);
	};
	
	void PushPak(char *bBuf, int size, PACKET_TYPE type);
	
	NetworkState GetNetworkState() const { return m_NetworkState; }
	void SetNetworkState(NetworkState state) { m_NetworkState = state; }
	const MySocket& GetSocket()const { return m_socket; }
	int32 GetUserId() const { return m_UserId; }
	void SetUserId(int32 nVal){ m_UserId = nVal; }
	void SetLastActiveTime(int32 ansi){ m_socket.SetLastActiveTime(ansi); }
public:
	void CopyFrom(const ClientUser &rCUser)
	{
		m_UserId = rCUser.GetUserId();
		m_socket = rCUser.GetSocket();
		m_NetworkState = rCUser.GetNetworkState();
	}

	ClientUser& operator=(const ClientUser& rFrom)
	{
		if (this == &rFrom)
		{
			return *this;
		}
		this->CopyFrom(rFrom);
		return *this;
	}

public:
	int32 m_UserId;
	MySocket m_socket;
private:
	int32		m_CurPackSize = 0;
	PACKET_TYPE m_CurPackType = PACKET_TYPE::INVALID;
	InputStream m_SockData;
	OutputStream m_SendBuf;
	NetworkState m_NetworkState;
};
