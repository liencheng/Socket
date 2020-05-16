#include "RoomManager.h"
#include "../ThreadPool.h"
#include "../GameDefine/GameDefine_Room.h"

#define ASSERT_THREAD_POOL() assert(m_pThreadPool != nullptr, "");

void RoomManager::Enter2Room(const ClientUser &rClientUser, RoomInfo &rRoomInfo)
{
	ASSERT_THREAD_POOL();
	room *pRoom = nullptr;
	do
	{
		//��ȡָ������
		pRoom = m_pThreadPool->getroom(rRoomInfo.RoomId);
		if (nullptr != pRoom && !pRoom->IsUserFull())
		{
			break;
		}
		//��ȡ���з���
		pRoom = m_pThreadPool->getroomfree();
		if (nullptr != pRoom)
		{
			break;
		}

		//�����µķ���
		int32 nRtId = m_pThreadPool->addroutine((rt_type)rRoomInfo.RoomType);
		pRoom = m_pThreadPool->getroom(nRtId);
	} while (false);
	if (nullptr == pRoom)
	{
		MyLog::Log("Trans2Room failed. get room failed.");
		return;
	}
	//�����µķ���
	pRoom->AddUser(rClientUser);
	MyLog::Log("Trans2Room Succ. roomId(%d), roomType(%d)", rRoomInfo.RoomId, rRoomInfo.RoomType);
}