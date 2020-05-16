#include "stdafx.h"
#include "ToolManager.h"
#include "Utils/GuidHelper.h"

void ToolManager::Tick_NewConnet()
{
	fd_set fd_reader;
	fd_set fd_writer;
	fd_set fd_exception;
	FD_ZERO(&fd_reader);
	FD_ZERO(&fd_writer);
	FD_ZERO(&fd_exception);

	FD_SET(m_listensocket, &fd_reader);
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	int nRet = select(m_socket_count + 1, &fd_reader, &fd_writer, &fd_exception, &tv);

	if (nRet == SOCKET_ERROR)
	{
		cout << "select error" << endl;
		return;
	}

	if (FD_ISSET(m_listensocket, &fd_reader))
	{//有新连接
		AcceptNewPlayer();
	}
}

void ToolManager::AcceptNewPlayer()
{
	sockaddr_in addr_in;
	int addr_len = sizeof(addr_in);
	SOCKET sock = accept(m_listensocket, (sockaddr*)(&addr_in), &addr_len);
	if (sock == SOCKET_ERROR)
	{
		cout << "accept new player error" << endl;
		return;
	}
	MySocket mySock(sock, addr_in);

	ClientUser user(GEN_USER_GUID(), mySock);
	user.SetNetworkState(NetworkState::CONNECTED);
	RoomInfo roomInfo;
	roomInfo.RoomId = -1;
	roomInfo.RoomType = (int32)rt_type::rt_city;
	m_RoomManager.Enter2Room(user, roomInfo);

	//m_rThreadPool.PushUser(user);

	cout << "accept succ." << endl;
}

void ToolManager::Tick_ProcessSocket()
{
	if (m_player_list.size() <= 0)
	{
		return;
	}
	FD_ZERO(&m_fs_read);
	FD_ZERO(&m_fs_write);
	FD_ZERO(&m_fs_exception);

	for (int idx = 0; idx < m_player_list.size(); ++idx)
	{
		FD_SET(m_player_list[idx].m_socket, &m_fs_read);
		FD_SET(m_player_list[idx].m_socket, &m_fs_write);
		FD_SET(m_player_list[idx].m_socket, &m_fs_exception);
	}
	timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 0;
	int nRet = select(m_socket_count, &m_fs_read, &m_fs_write, &m_fs_exception, &tv);

	if (nRet == SOCKET_ERROR)
	{
		cout << "query sockets error" << endl;
		return;
	}
}

void ToolManager::Tick_ProcessInput()
{
	int nValidSock = 0;
	for (int idx = 0; idx < m_player_list.size(); ++idx)
	{
		SOCKET sock = m_player_list[idx].m_socket;
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
				//cout << "recv data," << outbuf << endl;
				delete outbuf;
			}
		}
	}
	if (nValidSock > 0)
	{
		//cout << "nValidSock:" << nValidSock << endl;
	}
}

void ToolManager::Tick_ProcessOutput()
{
	for (int idx = 0; idx < m_player_list.size(); ++idx)
	{
		SOCKET sock = m_player_list[idx].m_socket;
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
				//cout << "send, sock:" << sock << endl;
			}
		}
	}
}