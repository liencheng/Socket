#pragma once
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include "ClientUser.h"
#include <iostream>
//#include "windows.h"

using namespace std;

class MyThreadPool;

class MyThread
{
public:
	MyThread()
	{
	}
	MyThread(int nThreadId, MyThreadPool* pPool) :
		m_nThreadId(nThreadId),
		m_ThreadPool(pPool)
	{ 
	}

	MyThread(const MyThread &my)
	{
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
	void Tick_ProcessSocket();
	void Tick_ProcessInput();
	void Tick_ProcessOutput();
	void Tick_ProcessException();

	void ReqUser();
	
	int GetMyThreadId() const
	{
		return m_nThreadId;
	}
	MyThreadPool * GetThreadPoolPtr() const
	{
		return m_ThreadPool;
	}

private:
	fd_set m_fs_read;
	fd_set m_fs_write;
	fd_set m_fs_exception;

	std::thread m_thread;
	int	m_nThreadId;
	std::vector<ClientUser> m_UserVec;
	MyThreadPool  *m_ThreadPool;
};

class MyThreadPool
{
#define LOCK std::lock_guard<std::mutex> lock(m_mutex);

public:
	MyThreadPool(){};
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

	bool PushUser(const ClientUser& rUser)
	{
		LOCK;
		m_GlobalUserQueue.push(rUser);

		cout << "add client user." << endl;
		return true;
	}
	bool PopUser(ClientUser * pClientUser)
	{
		LOCK;
		if (pClientUser == nullptr)
		{
			return false;
		}
		if (m_GlobalUserQueue.size() <= 0)
		{
			return false;
		}
		ClientUser& rUser = m_GlobalUserQueue.front();
		m_GlobalUserQueue.pop();

		pClientUser->m_socket = rUser.m_socket;
		pClientUser->m_UserId = rUser.m_UserId;

		cout << "get client user" << endl;
		return true;
	}

private:
	std::mutex m_mutex;
	std::queue<ClientUser> m_GlobalUserQueue;
	int m_nThreadCount = 0;
	std::vector<MyThread> m_ThreadPool;
};
