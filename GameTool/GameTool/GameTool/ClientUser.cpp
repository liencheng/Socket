#include "stdafx.h"
#include "ClientUser.h"
#include "GameDefine/GameDefine_Packet.h"
#include "Packet/Handler/PacketBase.h"
#include "Packet/PKHandlerMgr.h"

using namespace std;

void ClientUser::ProcessInput()
{
	PacketBase* pPak = nullptr;
	if (m_CurPackType == PACKET_TYPE::INVALID)
	{
		int nType = 0;
		int nSize = 0;
		if (m_SockData.ReadHeader(nType, nSize))
		{
			std::cout << nType << endl;
			std::cout << nSize << endl;
			m_CurPackType = PACKET_TYPE(nType);
			m_CurPackSize = nSize;
		}
		return;
	}

	if (m_CurPackType != PACKET_TYPE::INVALID  && m_CurPackSize > 0)
	{
		bool bRet = false;
		
		if (m_CurPackSize >= PACK_SIZE::SIZE_4096)
		{
			char buf[PACK_SIZE::SIZE_8192];
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
			if (bRet)
			{
				PKHandlerMgr::ExecutePK(buf, m_CurPackSize, m_CurPackType, *this);
				m_CurPackSize = 0;
				m_CurPackType = PACKET_TYPE::INVALID;
			}
		}
		else if (m_CurPackSize >= PACK_SIZE::SIZE_2048)
		{
			char buf[PACK_SIZE::SIZE_4096];
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
			if (bRet)
			{
				PKHandlerMgr::ExecutePK(buf, m_CurPackSize, m_CurPackType, *this);
				m_CurPackSize = 0;
				m_CurPackType = PACKET_TYPE::INVALID;
			}
		}
		else if (m_CurPackSize > PACK_SIZE::SIZE_1024)
		{
			char buf[PACK_SIZE::SIZE_2048];
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
			if (bRet)
			{
				PKHandlerMgr::ExecutePK(buf, m_CurPackSize, m_CurPackType, *this);
				m_CurPackSize = 0;
				m_CurPackType = PACKET_TYPE::INVALID;
			}
		}
		else if (m_CurPackSize > PACK_SIZE::SIZE_512)
		{
			char buf[PACK_SIZE::SIZE_1024];
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
			if (bRet)
			{
				PKHandlerMgr::ExecutePK(buf, m_CurPackSize, m_CurPackType, *this);
				m_CurPackSize = 0;
				m_CurPackType = PACKET_TYPE::INVALID;
			}
		}
		else
		{
			char buf[PACK_SIZE::SIZE_512];
			memset(buf, 0, PACK_SIZE::SIZE_512);
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
			if (bRet)
			{
				PKHandlerMgr::ExecutePK(buf, m_CurPackSize, m_CurPackType, *this);
				m_CurPackSize = 0;
				m_CurPackType = PACKET_TYPE::INVALID;
			}
		}
		
	}

}
void ClientUser::ProcessOutput()
{
	if (!m_SendBuf.WaitSend())
	{
		return;
	}

	m_SendBuf.Flush();

	if (m_SendBuf.GetSendBuf() == nullptr)
	{
		return;
	}
	SOCKET sock = m_socket.m_socket;
	int nSendSize = send(sock, m_SendBuf.GetSendBuf(), m_SendBuf.GetSendSize(), 0);
	if (nSendSize == 0)
	{
		MyLog::Log("socket closed, sock:%d",sock);
	}
	else if (nSendSize == SOCKET_ERROR)
	{
		MyLog::Log("socket closed, sock:%d",sock);
	}
	else
	{
		m_SendBuf.SetPosition(m_SendBuf.GetPosition() + nSendSize);
		MyLog::Log("send data:, sock:%d",sock);
	}
}

void ClientUser::PushPak(char *bBuf, int size, PACKET_TYPE type)
{
	if (size <= 0)
	{
		return;
	}
#define INT_SIZE (4)
	//类型
	int nType = (int)type;
	char nTypeByte[INT_SIZE];
	memset(nTypeByte, 0, INT_SIZE);
	memcpy(nTypeByte, &nType, INT_SIZE);
	m_SendBuf.Write(nTypeByte, INT_SIZE);
	//大小
	char nSizeByte[INT_SIZE];
	memset(nSizeByte, 0, INT_SIZE);
	memcpy(nTypeByte, &size, INT_SIZE);
	m_SendBuf.Write(nTypeByte, INT_SIZE);
	//数据
	m_SendBuf.Write(bBuf, size);
}
