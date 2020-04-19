#pragma once

#include "PacketBase.h"
#include "../PbMsg.pb.h"

class pk_cs_ping:PacketBase
{
public:
	pk_cs_ping() 
	{
		m_Data.Clear();
	}
	
	virtual void Execute(PacketBase* pPacket)
	{
	}
private:
	Protobuf::CS_PING m_Data;
};
