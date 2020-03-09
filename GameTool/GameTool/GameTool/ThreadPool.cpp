#include "stdafx.h"
#include "ThreadPool.h"
#include <iostream>
#include "windows.h"

using namespace std;

void MyThread::StartThread()
{
	m_thread = std::thread(&MyThread::Tick, this);
}


void MyThread::Tick()
{
	int idx = 0;
	while (true)
	{
		Sleep(1000);
		ReqUser();
	};
}

void MyThread::ReqUser()
{
	ClientUser rUser(-1, MySocket());
	//if (m_ThreadPool->PopUser(&rUser))
	{
		m_UserVec.push_back(rUser);

		cout << "add user to thread succ. count:" << m_UserVec.size() << endl;
	}
}