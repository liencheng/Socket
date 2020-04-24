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
		if (m_UserVec[idx].GetNetworkState() != NetworkState::CONNECTED)
		{
			continue;
		}
		FD_SET(m_UserVec[idx].m_socket.m_socket, &m_fs_read);
		FD_SET(m_UserVec[idx].m_socket.m_socket, &m_fs_write);
		FD_SET(m_UserVec[idx].m_socket.m_socket, &m_fs_exception);
	}
	timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 0;

	if (m_fs_read.fd_count > 0 || m_fs_write.fd_count > 0 || m_fs_exception.fd_count > 0)
	{
		int nRet = select(-1, &m_fs_read, &m_fs_write, &m_fs_exception, &tv);
		if (nRet == SOCKET_ERROR)
		{
			int errorno = WSAGetLastError();
			MyLog::Log("query sockets error, errorNo.{%d}", errorno);
			return;
		}
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
			char buf[2048];
			memset(buf, 0, sizeof(buf));
			int nRcvData1 = 0;
			int recvlen =  recv(sock, (char*)(buf), sizeof(buf), 0);
				
			if (recvlen == 0)
			{
				cout << "socket has been closed. sock:" << sock << endl;
			}
			else if (recvlen == SOCKET_ERROR)
			{
				int errorno = WSAGetLastError();
				MyLog::Log("socket error. sock(%d), errorno(%d)", sock, errorno);
				m_UserVec[idx].SetNetworkState(NetworkState::DISCONNECTED);
			}
			else
			{
				InputStream &sockstream = m_UserVec[idx].GetInputStream();
				sockstream.Write((char*)buf, recvlen);
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
			m_UserVec[idx].ProcessOutput();
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
	pClientUser->SetNetworkState(rUser.GetNetworkState());

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
