#pragma once

#include "../stdafx.h"
#include "../GameDefine/GameDefine_Packet.h"
#include "windows.h"

class ClientUser;

class PKHandlerMgr
{
public:
	void ExecutePK(byte* pByte, int len, PACKET_TYPE pk_type, ClientUser & rUser);
};
