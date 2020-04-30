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
		TickUser();

		ReqUser();
		Tick_ProcessSocket();
		Tick_ProcessInput();
		Tick_ProcessOutput();
		Tick_DisConnectUser();

	};

}

void MyThread::TickUser()
{
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		m_UserVec[idx].Tick();
	}

}

void MyThread::Tick_DisConnectUser()
{
	int nCt = m_UserVec.size();
	for (int idx = nCt - 1; idx >= 0; --idx)
	{
		if (m_UserVec[idx].GetNetworkState() == NetworkState::DISCONNECTED)
		{
			MyLog::Log("del disconnet:robot,{%d}", m_UserVec[idx].m_UserId);
			m_UserVec.erase(m_UserVec.begin() + idx);
			DecValidUserCnt();
		}
	}
}

void MyThread::ReqUser()
{
	ClientUser rUser(-1, MySocket());
	if (m_ThreadPool->PopUser(&rUser))
	{
		rUser.m_socket.SetLastActiveTime(MyTimeUtils::GetAnsiTime());
		m_UserVec.push_back(rUser);
		IncValidUserCnt();
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

	if (m_fs_read.fd_count > 0 || m_fs_read.fd_count > 0 || m_fs_exception.fd_count > 0)
	{

		int nRet = select(-1, &m_fs_read, &m_fs_write, &m_fs_exception, &tv);

		if (nRet == SOCKET_ERROR)
		{
			cout << "query sockets error" << endl;
			return;
		}
	}
}

void MyThread::Tick_ProcessException()
{
	int nValidSock = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].m_socket.m_socket;
		if (FD_ISSET(sock, &m_fs_exception))
		{
		}
	}
}

void MyThread::Tick_ProcessInput()
{
	int nValidSock = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].m_socket.m_socket;
		
		if (FD_ISSET(sock, &m_fs_read) && !FD_ISSET(sock, &m_fs_exception))
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

				MyLog::Log("recv. socket error. sock:{%d}, errorno:{%d}" ,sock, errorno);

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

void MyThread::Tick_PrintPoolInfo()
{
	int connectedCnt = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		if (m_UserVec[idx].GetNetworkState() == NetworkState::CONNECTED)
		{
			connectedCnt++;
		}
	}
	MyLog::Log("Cur Active Player,Count(%d)", connectedCnt);
	
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
	MyLog::Log("pop user,id(%d)", rUser.m_UserId);
	return true;
}

bool MyThreadPool::PushUser(const ClientUser& rUser)
{
	LOCK;
	m_GlobalUserQueue.push(rUser);
	MyLog::Log("new user,id(%d)", rUser.m_UserId);
	return true;
}

void MyThreadPool::Tick_PrintThreadInfo()
{
	if (m_TimeClock.DiffMin())
	{
		int32 nValidUser = 0;
		for (int idx = 0; idx < m_ThreadPool.size(); ++idx)
		{
			int32 nUserCnt = m_ThreadPool[idx].GetValidUserCnt();
			int32 nThreadId = m_ThreadPool[idx].GetMyThreadId();
			nValidUser += nUserCnt;

			MyLog::Log("ThreanInfo, usercnt(%d), thread(%d)", nUserCnt, nThreadId);
		}
		MyLog::Log("ThreanInfo, total usercnt(%d), threadnum(%d)", nValidUser, m_ThreadPool.size());
	}
}