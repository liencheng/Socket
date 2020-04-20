
#include "SocketStream.h"

using namespace std;
void InputStream::Write(char *pByte, int len)
{
	for (int idx = 0; idx < len; ++idx)
	{
		m_Data.push(pByte[idx]);
	}
	cout << "add data.len:" << len << endl;
    
}

bool InputStream::ReadPacket(char *pBuf, int len)
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
	char headBuf[PACK_HEAD_LENGTH];

	if (ReadPacket(headBuf, PACK_HEAD_LENGTH))
	{
		memcpy(&nPackType, headBuf, PACK_HEAD_LENGTH / 2);
		memcpy(&nPackSize, &(headBuf[PACK_HEAD_LENGTH / 2]), PACK_HEAD_LENGTH / 2);
		return true;
	}
	return false;
}

void OutputStream::Write(char *pBuf, int len)
{
	for (int idx = 0; idx < len; ++idx)
	{
		m_Data.push(pBuf[idx]);
	}
	MyLog::Log("write to output.data len = %d", len);
}

char * OutputStream::GetSendBuf()
{
	if (m_Position >= m_EndPostion)
	{
		return nullptr;
	}
	if (m_Position >= sizeof(m_WaitSendBuf))
	{
		return nullptr;
	}
	return &(m_WaitSendBuf[m_Position]);
}

void OutputStream::Flush()
{
	if (m_Position >=m_EndPostion)
	{
		return;
	}
	for (int idx = 0; idx < sizeof(m_WaitSendBuf); ++idx)
	{
		if (m_Data.size()>0)
		{
			m_WaitSendBuf[idx] = m_Data.front();
			m_Data.pop();
			m_EndPostion = idx+1;
		}
		else
		{
			break;
		}
	}
	m_Position = 0;
}
