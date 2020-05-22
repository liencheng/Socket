#pragma once

#include "../stdafx.h"
#include "Room.h"
#include "../ThreadPool.h"
#include <vector>
#include <map>
#include <mutex>


using RoomId = int32;
using RoomUserVec = std::vector<ClientUser>;
using UserPool = std::map<RoomId, RoomUserVec>;

#define ROOM_MGR_LOCK std::lock_guard<std::mutex> lock(m_mutex);

class RoomManager
{
public:
	RoomManager()
	{
		m_pThreadPool = nullptr;
	}
	RoomManager(MyThreadPoolEx *pThreadPool) :
		m_pThreadPool(pThreadPool)
	{

	}
	~RoomManager(){}

	void Clean()
	{
		m_pThreadPool = nullptr;
	}

public:
	void Enter2Room(const ClientUser &rClientUser, RoomInfo &rRoomInfo);
	bool PushUser(int32 roomId, const ClientUser& rUser);
	bool PopUser(int32 roomId, ClientUser* pClientUser);
private:
	UserPool m_UserPool;
	MyThreadPoolEx *m_pThreadPool;
	std::mutex m_mutex;
};
