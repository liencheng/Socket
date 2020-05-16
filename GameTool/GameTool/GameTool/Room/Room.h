#pragma once

#include "../stdafx.h"
#include "../MyRoutine/MyRoutine.h"
#include "../ClientUser.h"
#include "Entity/User.h"
#include <mutex>

using namespace std;

struct RoomInfo
{
	int RoomId;
	int RoomType;
};



class room : public myroutine
{

#define ROOM_LOCK std::lock_guard<std::mutex> lock(m_mutex);
public:
	room(int roomid):
		myroutine(roomid),
		m_mutex(mutex())
	{ clean(); };
	~room(){};
	void clean()
	{
		m_ValidUserCnt = 0;
	}
private:
	virtual void tick_routine() override
	{
		ROOM_LOCK;
		TickUser();
		Tick_DisConnectUser();
		Tick_ProcessSocket();
		Tick_ProcessInput();
		Tick_ProcessOutput();
		Tick_ProcessException();

		tick_room();
	}
public:
	virtual void tick_room()
	{
		
	}
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

	bool AddUser(const ClientUser &rClientUser);
	bool DelUser(int userid);
	bool IsUserFull();


	void IncValidUserCnt()
	{
		m_ValidUserCnt++;
	}
	void DecValidUserCnt()
	{
		m_ValidUserCnt--;
	}

	int32 GetValidUserCnt() const{ return m_ValidUserCnt; }

private:
	fd_set m_fs_read;
	fd_set m_fs_write;
	fd_set m_fs_exception;
	std::vector<User> m_UserVec;
	int m_ValidUserCnt;
	//////////////////////////////////////////////////////////////////////////
	//User管理
	//////////////////////////////////////////////////////////////////////////
	std::mutex m_mutex;
};

class room_city : public room
{
public:
	room_city(int roomid):room(roomid){ clean(); };
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
	room_wild(int roomid):room(roomid){ clean(); };
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
	room_cs(int roomid):room(roomid){ clean(); };
	~room_cs(){};
	void clean()
	{
	}
public:
	virtual void tick_room() {}
private:
};