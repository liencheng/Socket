#pragma once

#include "../../stdafx.h"
#include <queue>
#include "../../GameDefine/GameDefine_Packet.h"
#include "../../Packet/PbMsg.pb.h"

class InputStream
{
public:
	InputStream(){ Clean(); };

	void Clean()
	{
		while (m_Data.size()>0)
		{
			m_Data.pop();
		}
	}
	void Write(char * pByte, int len);
	bool ReadPacket(char *pBuf, int len);
	bool ReadHeader(int &nPackType, int &nPackSize);
private:
	std::queue<char> m_Data;
	int32 m_WriteByte = 0;
	int32 m_ReadByte = 0;
};

class OutputStream
{

public:
	OutputStream(){ Clean(); };
	void Clean()
	{
		while (m_Data.size()>0)
		{
			m_Data.pop();
		}
		memset(m_WaitSendBuf, 0, SEND_BUF_MAX);
		m_Position = 0;
		m_EndPostion = 0;
	}
	void Write(char *pBuf, int len);
	void Flush();
	char * GetSendBuf();
	int GetSendSize(){ return m_EndPostion - m_Position; }
	int GetPosition() const{ return m_Position; }
	void SetPosition(int pos) { m_Position = pos; }
	bool WaitSend()const{ return m_Data.size() > 0 || (m_Position < m_EndPostion); }
private:
	std::queue<char> m_Data;
	int m_Position;
	int m_EndPostion = 0;
	char m_WaitSendBuf[SEND_BUF_MAX];
};
