#include "stdafx.h"
#include "ThreadPool.h"
#include <iostream>
#include "winsock2.h"
#include "windows.h"


using namespace std;

std::mutex g_mutex;

#define LOCK std::lock_guard<std::mutex> lock(g_mutex);

void MyThread::StartThread()
{
	m_thread = std::thread(&MyThread::Tick, this);
}


void MyThread::Tick()
{
	int idx = 0;
	while (true)
	{
		Sleep(10);
		ReqUser();
		Tick_ProcessSocket();
		Tick_ProcessInput();
		Tick_ProcessOutput();
	};

}

void MyThread::ReqUser()
{
	ClientUser rUser(-1, MySocket());
	if (m_ThreadPool->PopUser(&rUser))
	{
		m_UserVec.push_back(rUser);
		cout << "pid:" << GetCurrentThreadId() << endl;
	}
}

void MyThread::Tick_ProcessSocket()
{
	if (m_UserVec.size() <= 0)
	{
		return;
	}
	FD_ZERO(&m_fs_read);
	FD_ZERO(&m_fs_write);
	FD_ZERO(&m_fs_exception);

	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		FD_SET(m_UserVec[idx].m_socket.m_socket, &m_fs_read);
		FD_SET(m_UserVec[idx].m_socket.m_socket, &m_fs_write);
		FD_SET(m_UserVec[idx].m_socket.m_socket, &m_fs_exception);
	}
	timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 0;
	int nRet = select(-1, &m_fs_read, &m_fs_write, &m_fs_exception, &tv);

	if (nRet == SOCKET_ERROR)
	{
		cout << "query sockets error" << endl;
		return;
	}
}

void MyThread::Tick_ProcessInput()
{
	int nValidSock = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].m_socket.m_socket;
		if (FD_ISSET(sock, &m_fs_read))
		{
			byte buf[2048];
			memset(buf, 0, sizeof(buf));
			int nRcvData1 = 0;
			int recvlen =  recv(sock, (char*)(buf), sizeof(buf), 0);
				
			if (recvlen == 0)
			{
				cout << "socket has been closed. sock:" << sock << endl;
			}
			else if (recvlen == SOCKET_ERROR)
			{
				cout << "socket error. sock:" << sock << endl;
			}
			else
			{
				InputStream &sockstream = m_UserVec[idx].GetInputStream();
				sockstream.Write((byte*)buf, recvlen);
				m_UserVec[idx].ProcessInput();
			}
		}
	}
}

void MyThread::Tick_ProcessOutput()
{
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].m_socket.m_socket;
		if (FD_ISSET(sock, &m_fs_write))
		{
			char buf[1024] = "ku wa yi madai";
			int nRet = send(sock, buf, sizeof(buf), 0);
			if (nRet == 0)
			{
				cout << "socket closed, sock:" << sock << endl;
			}
			else if (nRet == SOCKET_ERROR)
			{
				cout << "send error, sock:" << sock << endl;
			}
			else{
				cout << "send, sock:" << sock << endl;
			}
		}
	}
}

MyThreadPool::MyThreadPool()
{

}

bool MyThreadPool::PopUser(ClientUser* pClientUser)
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

bool MyThreadPool::PushUser(const ClientUser& rUser)
{
	LOCK;
	m_GlobalUserQueue.push(rUser);

	cout << "add client user." << endl;
	return true;
}
