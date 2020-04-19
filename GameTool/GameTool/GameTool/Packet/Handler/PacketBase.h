#pragma once

class PacketBase
{
public:
	virtual void Excute(PacketBase* pPacket) = 0;
};
