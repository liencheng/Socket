#include "stdafx.h"
#include "ClientUser.h"
#include "GameDefine/GameDefine_Packet.h"

using namespace std;
void InputStream::Write(byte *pByte, int len)
{
	for (int idx = 0; idx < len; ++idx)
	{
		m_Data.push(pByte[idx]);
	}
	cout << "add data.len:" << len << endl;
}

bool InputStream::ReadPacket(byte *pBuf, int len)
{
	if (m_Data.size() < len)
	{
		return false;
	}
	
	for (int idx = 0; idx < len; ++idx)
	{
		pBuf[idx] = m_Data.front();
		m_Data.pop();
	}
	return true;;
}

bool InputStream::ReadHeader(int &nPackType, int &nPackSize)
{
	nPackType = -1;
	nPackSize = -1;
	if (m_Data.size() < PACK_HEAD_LENGTH)
	{
		return false;
	}
	byte headBuf[PACK_HEAD_LENGTH];

	if (ReadPacket(headBuf, PACK_HEAD_LENGTH))
	{
		memcpy(&nPackType, headBuf, PACK_HEAD_LENGTH / 2);
		memcpy(&nPackSize, &(headBuf[PACK_HEAD_LENGTH / 2]), PACK_HEAD_LENGTH / 2);
		return true;
	}
	return false;
}


void ClientUser::ProcessInput()
{
	if (m_CurPackType == PACKET_TYPE::INVALID)
	{
		int nType = 0;
		int nSize = 0;
		if (m_SockData.ReadHeader(nType, nSize))
		{
			std::cout << nType << endl;
			std::cout << nSize << endl;
		}
		return;
	}

	if (m_CurPackType != PACKET_TYPE::INVALID  && m_CurPackSize > 0)
	{
		bool bRet = false;
		if (m_CurPackSize >= PACK_SIZE::SIZE_4096)
		{
			byte buf[PACK_SIZE::SIZE_8192];
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
		}
		else if (m_CurPackSize >= PACK_SIZE::SIZE_2048)
		{
			byte buf[PACK_SIZE::SIZE_4096];
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
		}
		else if (m_CurPackSize > PACK_SIZE::SIZE_1024)
		{
			byte buf[PACK_SIZE::SIZE_2048];
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
		}
		else if (m_CurPackSize > PACK_SIZE::SIZE_512)
		{
			byte buf[PACK_SIZE::SIZE_1024];
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
		}
		else
		{
			byte buf[PACK_SIZE::SIZE_512];
			bool bRet = m_SockData.ReadPacket(buf, m_CurPackSize);
		}


	}

}