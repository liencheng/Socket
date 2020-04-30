#pragma once

#define  PACK_HEAD_LENGTH (sizeof(int) + sizeof(int))
#define  SEND_BUF_MAX (2048)
#define  NETWORKDLOSTTIME (60)


enum PACKET_TYPE
{
	INVALID = -1,
	CS_PING = 1,
	SC_PONG = 2,
};

class PACK_SIZE
{
public:
	enum
	{
		SIZE_512 = 512,
		SIZE_1024 = 1024,
		SIZE_2048 = 2048,
		SIZE_4096 = 4096,
		SIZE_8192 = 8192,
	};
};

