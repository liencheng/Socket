#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma once
#include "stdafx.h"
#include "winsock2.h"
#include "windows.h"
#include <iostream>
#include "MySocket.h"
#include <vector>

#include "ThreadPool.h"
#include "Room/RoomManager.h"


#define SERVER_ADDR ("127.0.0.1")
#define	PORT (2718)
#define BLOCK_LOG_MAX (2000)
#define THREAD_POOL_COUNT (30)

#pragma comment(lib, "WS2_32.lib")

class ToolManager
{
public:
	ToolManager() :
		m_rThreadPool(MyThreadPool()),
		m_rThreadPoolEx(THREAD_POOL_COUNT),
		m_RoomManager(&m_rThreadPoolEx)

	{ Clean(); };

	~ToolManager(){
		WSACleanup();
	};


	void Clean()
	{
		m_socket_count = 0;
		m_player_list.clear();
		FD_ZERO(&m_fs_read);
		FD_ZERO(&m_fs_write);
		FD_ZERO(&m_fs_exception);
	}
	void Start()
	{
		InitNetWork();
		InitAddr();
		InitListenSocket();

		m_rThreadPoolEx.start();
	}
	void InitNetWork()
	{
		int nret =WSAStartup(MAKEWORD(2, 2), &m_wsadata);
		if (nret == SOCKET_ERROR)
		{
			std::cout << "start up error" << endl;
			return;
		}
	}
	void InitListenSocket()
	{
		m_listensocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
		if (m_listensocket == SOCKET_ERROR)
		{
			std::cout << "socket error" << endl;
			return;
		}

		int nRet = ::bind(m_listensocket, (sockaddr*)(&m_addr_in), sizeof(m_addr_in));

		if (nRet == SOCKET_ERROR)
		{
			std::cout << "bind error" << endl;
			return;
		}

		nRet = listen(m_listensocket, BLOCK_LOG_MAX);

		if (nRet == SOCKET_ERROR)
		{
			std::cout << "listen error" << endl;
			return;
		}

		//设置成非阻塞方式
		ULONG NonBlock = 1;
		if (ioctlsocket(m_listensocket, FIONBIO, &NonBlock))
		{
			std::cout<<"ioctlsocket() failed with error:" <<WSAGetLastError()<<endl;
			return;
		}

		m_socket_count += 1;

		std::cout << "listen..ok." << endl;
	}

	void InitAddr()
	{
		memset(&m_addr_in, 0, sizeof(sockaddr_in));
		m_addr_in.sin_family = AF_INET;
		m_addr_in.sin_addr.S_un.S_addr = inet_addr(SERVER_ADDR);
		m_addr_in.sin_port = htons(PORT);
		std::cout << "init addr ok." << endl;
	}

	void Tick()
	{
		Tick_ProcessSocket();
		Tick_ProcessInput();
		Tick_ProcessOutput();
		Tick_NewConnet();

		m_rThreadPool.Tick();
		m_rThreadPoolEx.Tick_PrintRoomInfo();
	}
	void Tick_NewConnet();
	void Tick_ProcessSocket();
	void Tick_ProcessInput();
	void Tick_ProcessOutput();
	void Tick_ProcessException();

	void AcceptNewPlayer();
	
private:
	SOCKET m_listensocket;
	sockaddr_in m_addr_in;
	int m_port;
	int m_socket_count;

	std::vector<MySocket> m_player_list;
	fd_set m_fs_read;
	fd_set m_fs_write;
	fd_set m_fs_exception;
	WSADATA m_wsadata;

	MyThreadPool m_rThreadPool;
	MyThreadPoolEx m_rThreadPoolEx;
	RoomManager m_RoomManager;
};