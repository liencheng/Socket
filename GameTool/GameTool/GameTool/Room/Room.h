#pragma once

#include "../stdafx.h"
#include "../MyRoutine/MyRoutine.h"
#include "../ClientUser.h"
#include "Entity/User.h"
#include <mutex>
#include <atomic>

using namespace std;
class RoomManager;

struct RoomInfo
{
	int RoomId;
	int RoomType;
};



class room : public myroutine
{

#define ROOM_LOCK std::lock_guard<std::mutex> lock(m_mutex);
public:
	room(int roomid, RoomManager * pRoomMgr):
		myroutine(roomid),
		m_pRoomMgr(pRoomMgr)
	{ clean(); };
	~room(){};
	void clean()
	{
		m_ValidUserCnt = 0;
		m_EnteringUser = 0;
	}
private:
	virtual void tick_routine() override
	{
		ROOM_LOCK;
		TickPullUser();
		TickUser();
		Tick_DisConnectUser();
		Tick_ProcessSocket();
		Tick_ProcessInput();
		Tick_ProcessOutput();
		Tick_ProcessException();
		tick_room();
	}
public:
	virtual void tick_room(){};
	//////////////////////////////////////////////////////////////////////////
	//User管理
	//////////////////////////////////////////////////////////////////////////
public:

	void TickUser();
	void Tick_DisConnectUser();
	void Tick_ProcessSocket();
	void Tick_ProcessInput();
	void Tick_ProcessOutput();
	void Tick_ProcessException();
	void Tick_PrintPoolInfo();
	void TickPullUser();

	bool AddUser(const ClientUser &rClientUser);
	bool DelUser(int userid);
	bool IsUserFull();


	void IncValidUserCnt(){m_ValidUserCnt++;}
	void DecValidUserCnt(){m_ValidUserCnt--;}

	void IncEnteringUser() { m_EnteringUser++; }
	void DecEnteringUser(){ m_EnteringUser--; }

	int32 GetValidUserCnt() const{ return m_ValidUserCnt; }

private:
	fd_set m_fs_read;
	fd_set m_fs_write;
	fd_set m_fs_exception;
	std::vector<User> m_UserVec;
	int m_ValidUserCnt;
	std::atomic_int32_t m_EnteringUser;
	//////////////////////////////////////////////////////////////////////////
	//User管理
	//////////////////////////////////////////////////////////////////////////
	std::mutex m_mutex;
	RoomManager *m_pRoomMgr;
};

class room_city : public room
{
public:
	room_city(int roomid, RoomManager *pRoomMgr):room(roomid, pRoomMgr){ clean(); };
	~room_city(){};
	void clean()
	{
	}
public:
	virtual void tick_room() {}
	virtual rt_type get_rt_type(){ return rt_type::rt_city; }
private:
};
class room_wild :public room
{
public:
	room_wild(int roomid, RoomManager *pRoomMgr):room(roomid, pRoomMgr){ clean(); };
	~room_wild(){};
	void clean()
	{
	}
public:
	virtual void tick_room() {}
private:
};
class room_cs :public room
{
public:
	room_cs(int roomid, RoomManager *pRoomMgr):room(roomid, pRoomMgr){ clean(); };
	~room_cs(){};
	void clean()
	{
	}
public:
	virtual void tick_room() {}
private:
};