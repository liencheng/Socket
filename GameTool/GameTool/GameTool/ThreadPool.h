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
	MyThread(){ Clean(); }

	MyThread(const MyThread &rSour){}

	~MyThread() { m_thread.join(); }

	void Clean()
	{
		m_nThreadId = -1;
	}
	void  StartThread();

	void Tick();

	void ReqUser();

private:
	std::thread m_thread;
	int	m_nThreadId;
	std::vector<ClientUser> m_UserVec;
	//MyThreadPool  *m_ThreadPool;
};

class MyThreadPool
{
#define LOCK std::lock_guard<std::mutex> lock(m_mutex);

public:
	MyThreadPool(int nThreadCnt)
		:m_nThreadCount(nThreadCnt)
	{
		Init();
	}
	~MyThreadPool() { Clean(); }

	void Clean() {
		cout << "clean pool" << endl;
	}

	void Init()
	{
		for (int idx = 0; idx < m_nThreadCount; ++idx)
		{
			m_ThreadPool.push_back(*(new MyThread()));
			m_ThreadPool.back().StartThread();
		}
	}
	bool PushUser(const ClientUser& rUser)
	{
		LOCK;
		m_GlobalUserQueue.push(rUser);

		cout << "add client user." << endl;
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

		pClientUser->m_Socket = rUser.m_Socket;
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

/*

class B;

class A
{
public:
	A(B* pb)
	{
		ppbb = pb;
	}

	B* ppbb;
};

class B
{

};

*/