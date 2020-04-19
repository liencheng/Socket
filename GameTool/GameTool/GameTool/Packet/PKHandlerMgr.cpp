#include "PKHandlerMgr.h"
#include "PbMsg.pb.h"
#include "../ClientUser.h"

void  PKHandlerMgr::ExecutePK(byte* pByte, int len, PACKET_TYPE pk_type, ClientUser & rUser)
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











