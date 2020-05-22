#pragma once
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include "ClientUser.h"
#include <iostream>
#include "GameDefine/GameDefine_Room.h"
#include "Room/Room.h"
#include "MyRoutine/MyRoutine.h"

//#include "windows.h"

using namespace std;

class MyThreadPool;

class MyThread
{
public:
	MyThread()
	{
		Clean();
	}
	MyThread(int nThreadId, MyThreadPool* pPool) :
		m_nThreadId(nThreadId),
		m_ThreadPool(pPool)
	{ 
		Clean();
	}

	MyThread(const MyThread &my)
	{
		Clean();
		this->m_nThreadId = my.GetMyThreadId();
		this->m_ThreadPool = my.GetThreadPoolPtr();
	}

	~MyThread()
	{
		if (m_thread.joinable())
		{
			m_thread.join();
		}
	}
	void  StartThread();

	void Tick();
	void TickUser();
	void Tick_DisConnectUser();
	void Tick_ProcessSocket();
	void Tick_ProcessInput();
	void Tick_ProcessOutput();
	void Tick_ProcessException();

	void Tick_PrintPoolInfo();

	void ReqUser();
	
	int GetMyThreadId() const
	{
		return m_nThreadId;
	}
	MyThreadPool * GetThreadPoolPtr() const
	{
		return m_ThreadPool;
	}

	void Clean()
	{
		m_ValidUserCnt = 0;
	}

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
	std::thread m_thread;
	int	m_nThreadId;
	std::vector<ClientUser> m_UserVec;
	MyThreadPool  *m_ThreadPool;
	int m_ValidUserCnt;
};

class MyThreadPool
{

public:
	MyThreadPool();;
	MyThreadPool(int nThreadCnt)
		:m_nThreadCount(nThreadCnt)
	{
		Init();
	};
	~MyThreadPool() { Clean(); }

	void Clean() {
		cout << "clean pool" << endl;
	}

	void Init()
	{
		for (int idx = 0; idx < m_nThreadCount; ++idx)
		{
			MyThread td(m_ThreadPool.size()+1, this);
			m_ThreadPool.push_back(move(td));
		}
		for (int idx = 0; idx < m_nThreadCount; ++idx)
		{
			m_ThreadPool[idx].StartThread();
		}
	}

	void Tick()
	{
		Tick_PrintThreadInfo();
		m_TimeClock.Tick();
	}

	void Tick_PrintThreadInfo();

	bool PushUser(const ClientUser& rUser);
	bool PopUser(ClientUser* pClientUser);
private:
	int m_nThreadCount = 0;
	std::queue<ClientUser> m_GlobalUserQueue;
	std::vector<MyThread> m_ThreadPool;
	MyClockTime m_TimeClock;
};


struct MyRoutineWrap
{

}; 

using my_routine_vec = std::vector<myroutine*>;
using my_thread_vec = std::vector<std::thread*>;
class  MyThreadPoolEx
{
#define RT_LOCK std::lock_guard<std::mutex> lock(m_mutex);
#define RT_MAP_LOCK std::lock_guard<std::mutex> lock(m_mutex_rt_map);
public:
	MyThreadPoolEx(int nPoolSize) :
		m_mutex(std::mutex()),
		m_poolsize(nPoolSize)
	{
		Clean();
	}
	~MyThreadPoolEx();

	void Clean()
	{
		m_rt_vec.clear();
		m_thread_vec.clear();
		m_take_index = 0;
		m_next_routine_id = 0;
	}
public:
	void start();
	void stop();
	void release_thread();
	void tick();
	int32 addroutine(rt_type rttype);
	int32 addroom(rt_type rt_type, RoomManager * pRoomMgr);
	int32 delroutine(int rt_id);
	myroutine * getrotuine(const RoomInfo &rRoomInfo);
	void release_routine();
	myroutine * takeroutine();
	int32 next_routine_id(){ return m_next_routine_id++; };

	room * getroom(int32 rt_id);
	room * getroomfree();

private:
	void lock_rt(int32 rt_id);
	void unlock_rt(int32 rt_id);
	bool locked_rt(int32 rt_id);
	//////////////////////////////////////////////////////////////////////////
	//debug start
public:
	void Tick_PrintRoomInfo();
	//debug end
	//////////////////////////////////////////////////////////////////////////
private:
	my_thread_vec m_thread_vec;
	my_routine_vec m_rt_vec;
	std::mutex m_mutex;
	std::mutex m_mutex_rt_map;
	int32 m_poolsize;
	int32 m_take_index;
	int32 m_next_routine_id;

	std::map<int32, bool> m_locked_rt_map;

	MyClockTime m_TimeClock;
};

