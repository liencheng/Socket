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
		//获取指定房间
		pRoom = m_pThreadPool->getroom(rRoomInfo.RoomId);
		if (nullptr != pRoom && !pRoom->IsUserFull())
		{
			break;
		}
		//获取空闲房间
		pRoom = m_pThreadPool->getroomfree();
		if (nullptr != pRoom)
		{
			break;
		}

		//创建新的房间
		int32 nRtId = m_pThreadPool->addroom((rt_type)rRoomInfo.RoomType, this);
		pRoom = m_pThreadPool->getroom(nRtId);
	} while (false);
	if (nullptr == pRoom || pRoom->get_id() < 0)
	{
		MyLog::Log("Trans2Room failed. get room failed.");
		return;
	}
	//新的房间成功
	PushUser(pRoom->get_id(), rClientUser);
	pRoom->IncEnteringUser();
	MyLog::Log("Trans2Room Succ. roomId(%d), roomType(%d)", pRoom->get_id(), rRoomInfo.RoomType);
}

bool RoomManager::PushUser(int32 roomId, const ClientUser& rUser)
{
	ROOM_MGR_LOCK;
	if (roomId < 0)
	{
		return false;
	}

	auto itF = m_UserPool.find(roomId);
	if (itF != m_UserPool.end())
	{
		itF->second.push_back(rUser);
	}
	else
	{
		RoomUserVec roomUserVec;
		std::pair<int32, RoomUserVec> assistRoom(roomId, roomUserVec);
		assistRoom.second.insert(assistRoom.second.begin(), rUser);
		m_UserPool.insert(assistRoom);
	}
	return true;
}

bool RoomManager::PopUser(int32 roomId, ClientUser* pClientUser)
{
	ROOM_MGR_LOCK;
	auto itF = m_UserPool.find(roomId);
	if (itF == m_UserPool.end())
	{
		return false;
	}
	RoomUserVec &rVec = itF->second;
	if (rVec.size() <= 0)
	{
		return false;
	}
	auto itBack =rVec.back();
	*pClientUser = itBack;
	rVec.pop_back();
	return nullptr != pClientUser;
}