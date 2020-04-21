#include "PKHandlerMgr.h"
#include "PbMsg.pb.h"
#include "../ClientUser.h"

void  PKHandlerMgr::ExecutePK(char* pByte, int len, PACKET_TYPE pk_type, ClientUser & rUser)
{
	switch (pk_type)
	{
	case PACKET_TYPE::CS_PING:
	{
		Protobuf::CS_PING pPacket;
		pPacket.ParsePartialFromArray(pByte, len);
		rUser.RcvPacket(pPacket);
		break;
	}
	default:
	{
		std::cout << "error type:" << (int)(pk_type) << std::endl;
		break;
	}
	}
}


void PKHandlerMgr::PushPak(google::protobuf::Message &rMsg, PACKET_TYPE type, ClientUser &rUser)
{
	char *pBuf = new char[rMsg.ByteSize()];
	rUser.PushPak(pBuf, rMsg.ByteSize(), type);
	delete []pBuf;
}










