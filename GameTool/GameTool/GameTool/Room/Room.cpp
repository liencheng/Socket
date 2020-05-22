#include "Room.h"
#include "../Utils/IncIdHelper.h"
#include "RoomManager.h"

using namespace std;

void room::TickUser()
{
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		m_UserVec[idx].Tick();
	}

}

void room::Tick_DisConnectUser()
{
	int nCt = m_UserVec.size();
		
	std::vector<int32> needDel;
	for (int idx = nCt - 1; idx >= 0; --idx)
	{
		if (m_UserVec[idx].GetClientUser().GetNetworkState() == NetworkState::DISCONNECTED)
		{
			needDel.push_back(m_UserVec[idx].GetEntityId());
		}
	}

	for (int idx = 0; idx < needDel.size(); ++idx)
	{
		for (auto it = m_UserVec.begin(); it != m_UserVec.end(); ++it)
		{
			if (it->GetEntityId() == needDel[idx])
			{
				MyLog::Log("del disconnet:robot,{%d}", it->GetClientUser().m_UserId);
				m_UserVec.erase(it);
				DecValidUserCnt();
				break;;
			}
		}
	}
}


void room::Tick_ProcessSocket()
{
	if (m_UserVec.size() <= 0)
	{
		return;
	}
	FD_ZERO(&m_fs_read);
	FD_ZERO(&m_fs_write);
	FD_ZERO(&m_fs_exception);

	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		if (m_UserVec[idx].GetClientUser().GetNetworkState() != NetworkState::CONNECTED)
		{
			continue;
		}
		FD_SET(m_UserVec[idx].GetClientUser().m_socket.m_socket, &m_fs_read);
		FD_SET(m_UserVec[idx].GetClientUser().m_socket.m_socket, &m_fs_write);
		FD_SET(m_UserVec[idx].GetClientUser().m_socket.m_socket, &m_fs_exception);
	}
	timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 0;

	if (m_fs_read.fd_count > 0 || m_fs_read.fd_count > 0 || m_fs_exception.fd_count > 0)
	{

		int nRet = select(-1, &m_fs_read, &m_fs_write, &m_fs_exception, &tv);

		if (nRet == SOCKET_ERROR)
		{
			cout << "query sockets error" << endl;
			return;
		}
	}
}

void room::Tick_ProcessException()
{
	int nValidSock = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].GetClientUser().m_socket.m_socket;
		if (FD_ISSET(sock, &m_fs_exception))
		{
		}
	}
}

void room::Tick_ProcessInput()
{
	int nValidSock = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].GetClientUser().m_socket.m_socket;
		
		if (FD_ISSET(sock, &m_fs_read) && !FD_ISSET(sock, &m_fs_exception))
		{
			char buf[2048];
			memset(buf, 0, sizeof(buf));
			int nRcvData1 = 0;
			int recvlen =  recv(sock, (char*)(buf), sizeof(buf), 0);
				
			if (recvlen == 0)
			{
				cout << "socket has been closed. sock:" << sock << endl;
			}
			else if (recvlen == SOCKET_ERROR)
			{
				int errorno = WSAGetLastError();

				MyLog::Log("recv. socket error. sock:{%d}, errorno:{%d}" ,sock, errorno);

				m_UserVec[idx].GetClientUser().SetNetworkState(NetworkState::DISCONNECTED);
			}
			else
			{
				InputStream &sockstream = m_UserVec[idx].GetClientUser().GetInputStream();
				sockstream.Write((char*)buf, recvlen);
				m_UserVec[idx].GetClientUser().ProcessInput();
			}
		}
	}
}

void room::Tick_ProcessOutput()
{
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].GetClientUser().m_socket.m_socket;
		if (FD_ISSET(sock, &m_fs_write))
		{
			m_UserVec[idx].GetClientUser().ProcessOutput();
		}
	}
}

void room::Tick_PrintPoolInfo()
{
	int connectedCnt = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		if (m_UserVec[idx].GetClientUser().GetNetworkState() == NetworkState::CONNECTED)
		{
			connectedCnt++;
		}
	}
	MyLog::Log("Cur Active Player,roomId(%d),Count(%d)", m_id, connectedCnt);
}

bool room::AddUser(const ClientUser &rClientUser)
{
	User newUser = User();
	newUser.SetClientUser(rClientUser);
	newUser.SetEntityId(INCID_GEN(USER));
	newUser.GetClientUser().SetLastActiveTime(MyTimeUtils::GetAnsiTime());
	m_UserVec.push_back(newUser);
	IncValidUserCnt();
	return true;
}


bool room::IsUserFull()
{
	return GetValidUserCnt() + m_EnteringUser >= ROOM_USER_MAX;
}

void room::TickPullUser()
{
	if (nullptr == m_pRoomMgr)
	{
		return;
	}
	if (m_EnteringUser <= 0)
	{
		return;
	}

	ClientUser pClientUser;
	if (m_pRoomMgr->PopUser(m_id, &pClientUser))
	{
		AddUser(pClientUser);
		DecEnteringUser();
	}
}
