#pragma once

#include "../stdafx.h"
#include "Room.h"
#include "../ThreadPool.h"


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
private:
	MyThreadPoolEx *m_pThreadPool;
};
