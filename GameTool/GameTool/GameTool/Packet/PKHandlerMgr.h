#pragma once

#include "../stdafx.h"
#include "../GameDefine/GameDefine_Packet.h"
#include "PbMsg.pb.h"

class ClientUser;

class PKHandlerMgr
{
public:
	static void ExecutePK(char* pByte, int len, PACKET_TYPE pk_type, ClientUser & rUser);
	static void PushPak(google::protobuf::Message &rMsg, PACKET_TYPE type, ClientUser &rUser);
};
