#pragma  once
#include "stdafx.h"
#include "winsock2.h"
#include "windows.h"

class MySocket
{
public:
	MySocket(SOCKET sock, sockaddr_in addr_in)
		:m_socket(sock),
		m_addr_in(addr_in)
	{}
	~MySocket(){}

public:
	SOCKET  m_socket;
	sockaddr_in m_addr_in;
};