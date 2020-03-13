#include "stdafx.h"
#include "ThreadPool.h"
#include <iostream>
#include "winsock2.h"
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
			char buf[2048];
			memset(buf, 0, sizeof(buf));
			int recvlen = recv(sock, buf, sizeof(buf), 0);

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
				nValidSock++;
				char* outbuf = new char[recvlen + 1];
				memcpy(outbuf, buf, recvlen);
				outbuf[recvlen] = 0;
				cout << "recv data," << outbuf << " ,pid:"<<GetCurrentThreadId()<<endl;
				delete outbuf;
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