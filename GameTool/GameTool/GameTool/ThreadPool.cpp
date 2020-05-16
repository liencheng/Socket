#include "stdafx.h"
#include "ThreadPool.h"
#include <iostream>
#include "winsock2.h"
#include "windows.h"


using namespace std;

std::mutex g_mutex;

#define LOCK std::lock_guard<std::mutex> lock(g_mutex);

void MyThread::StartThread()
{
	m_thread = std::thread(&MyThread::Tick, this);
}


void MyThread::Tick()
{
	int idx = 0;
	while (true)
	{
		Sleep(10);
		TickUser();

		ReqUser();
		Tick_ProcessSocket();
		Tick_ProcessInput();
		Tick_ProcessOutput();
		Tick_DisConnectUser();

	};

}

void MyThread::TickUser()
{
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		m_UserVec[idx].Tick();
	}

}

void MyThread::Tick_DisConnectUser()
{
	int nCt = m_UserVec.size();
	for (int idx = nCt - 1; idx >= 0; --idx)
	{
		if (m_UserVec[idx].GetNetworkState() == NetworkState::DISCONNECTED)
		{
			MyLog::Log("del disconnet:robot,{%d}", m_UserVec[idx].m_UserId);
			m_UserVec.erase(m_UserVec.begin() + idx);
			DecValidUserCnt();
		}
	}
}

void MyThread::ReqUser()
{
	ClientUser rUser(-1, MySocket());
	if (m_ThreadPool->PopUser(&rUser))
	{
		rUser.m_socket.SetLastActiveTime(MyTimeUtils::GetAnsiTime());
		m_UserVec.push_back(rUser);
		IncValidUserCnt();
		cout << "pid:" << GetCurrentThreadId() << endl;
	}
}

void MyThread::Tick_ProcessSocket()
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
		if (m_UserVec[idx].GetNetworkState() != NetworkState::CONNECTED)
		{
			continue;
		}
		FD_SET(m_UserVec[idx].m_socket.m_socket, &m_fs_read);
		FD_SET(m_UserVec[idx].m_socket.m_socket, &m_fs_write);
		FD_SET(m_UserVec[idx].m_socket.m_socket, &m_fs_exception);
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

void MyThread::Tick_ProcessException()
{
	int nValidSock = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].m_socket.m_socket;
		if (FD_ISSET(sock, &m_fs_exception))
		{
		}
	}
}

void MyThread::Tick_ProcessInput()
{
	int nValidSock = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].m_socket.m_socket;
		
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

				m_UserVec[idx].SetNetworkState(NetworkState::DISCONNECTED);
			}
			else
			{
				InputStream &sockstream = m_UserVec[idx].GetInputStream();
				sockstream.Write((char*)buf, recvlen);
				m_UserVec[idx].ProcessInput();
			}
		}
	}
}

void MyThread::Tick_ProcessOutput()
{
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		SOCKET sock = m_UserVec[idx].m_socket.m_socket;
		if (FD_ISSET(sock, &m_fs_write))
		{
			m_UserVec[idx].ProcessOutput();
		}
	}
}

void MyThread::Tick_PrintPoolInfo()
{
	int connectedCnt = 0;
	for (int idx = 0; idx < m_UserVec.size(); ++idx)
	{
		if (m_UserVec[idx].GetNetworkState() == NetworkState::CONNECTED)
		{
			connectedCnt++;
		}
	}
	MyLog::Log("Cur Active Player,Count(%d)", connectedCnt);
	
}

MyThreadPool::MyThreadPool()
{

}

bool MyThreadPool::PopUser(ClientUser* pClientUser)
{
	LOCK;
	if (pClientUser == nullptr)
	{
		return false;
	}
	if (m_GlobalUserQueue.size() <= 0)
	{
		return false;
	}
	ClientUser& rUser = m_GlobalUserQueue.front();
	m_GlobalUserQueue.pop();

	pClientUser->m_socket = rUser.m_socket;
	pClientUser->m_UserId = rUser.m_UserId;
	pClientUser->SetNetworkState(rUser.GetNetworkState());
	MyLog::Log("pop user,id(%d)", rUser.m_UserId);
	return true;
}

bool MyThreadPool::PushUser(const ClientUser& rUser)
{
	LOCK;
	m_GlobalUserQueue.push(rUser);
	MyLog::Log("new user,id(%d)", rUser.m_UserId);
	return true;
}

void MyThreadPool::Tick_PrintThreadInfo()
{
	if (m_TimeClock.DiffSec())
	{
		int32 nValidUser = 0;
		for (int idx = 0; idx < m_ThreadPool.size(); ++idx)
		{
			int32 nUserCnt = m_ThreadPool[idx].GetValidUserCnt();
			int32 nThreadId = m_ThreadPool[idx].GetMyThreadId();
			nValidUser += nUserCnt;

			MyLog::Log("ThreanInfo, usercnt(%d), thread(%d)", nUserCnt, nThreadId);
		}
		MyLog::Log("ThreanInfo, total usercnt(%d), threadnum(%d)", nValidUser, m_ThreadPool.size());
	}
}


MyThreadPoolEx::~MyThreadPoolEx()
{
	//如果未成功推出，析构推出
	if (m_thread_vec.size() > 0 
		|| m_rt_vec.size()>0)
	{
		stop();
	}
}

void MyThreadPoolEx::tick()
{
	int idx = 0;
	while (true)
	{
		Sleep(10);
		myroutine * rtPtr = takeroutine();
		if (nullptr != rtPtr)
		{
			rtPtr->tick();
			//MyLog::Log("treadid:%d", GetCurrentThreadId());
		}
	};
}



void MyThreadPoolEx::start()
{
	for (int32 idx = 0; idx < m_poolsize; ++idx)
	{
		m_thread_vec.push_back(new thread(&MyThreadPoolEx::tick, this));
	}
	MyLog::Log("start thread, count(%d)", m_poolsize);
}

void MyThreadPoolEx::stop()
{
	release_thread();
	release_routine();
}

void MyThreadPoolEx::release_thread()
{
	for (my_thread_vec::iterator itF = m_thread_vec.begin(); itF != m_thread_vec.end(); ++itF)
	{
		if ((*itF)->joinable())
		{
			(*itF)->join();
		}
		delete *itF;
	}
	MyLog::Log("release thread, count(%d)", m_thread_vec.size());
	m_thread_vec.clear();
}

int32 MyThreadPoolEx::addroutine(rt_type rttype)
{
	RT_LOCK;
	myroutine * rt = nullptr;
	switch (rttype)
	{
	case rt_type::rt_city:
		rt = new room_city(next_routine_id());
		break;
	case rt_type::rt_wild:
		rt = new room_wild(next_routine_id());
		break;
	case rt_type::rt_cs:
		rt = new room_cs(next_routine_id());
		break;
	case rt_type::rt_table:
		break;
	default:
		break;
	}

	if (rt == nullptr)
	{
		return -1;
	}
	m_rt_vec.push_back(rt);
	return rt->get_id();
}

int32 MyThreadPoolEx::delroutine(int rt_id)
{
	RT_LOCK;
	auto it = m_rt_vec.begin();
	for (; it != m_rt_vec.end(); ++it)
	{
		if ((*it)->get_id() == rt_id)
		{
			delete *it;
			m_rt_vec.erase(it);
			return rt_id;
		}
	}
	return -1;
}

myroutine * MyThreadPoolEx::getrotuine(const RoomInfo &rRoomInfo)
{
	RT_LOCK;
	auto it = m_rt_vec.begin();
	for (; it != m_rt_vec.end(); ++it)
	{
		if ((*it)->get_id() == rRoomInfo.RoomId)
		{
			return *it;
		}
	}
	return nullptr;
}

room * MyThreadPoolEx::getroom(int32 rt_id)
{
	RT_LOCK;
	auto it = m_rt_vec.begin();
	for (; it != m_rt_vec.end(); ++it)
	{
		if ((*it)->get_id() == rt_id)
		{
			room *pRoom = dynamic_cast<room*>(*it);
			return pRoom;
		}
	}
	return nullptr;
}

room *MyThreadPoolEx::getroomfree()
{
	RT_LOCK;
	auto it = m_rt_vec.begin();
	for (; it != m_rt_vec.end(); ++it)
	{
		if ((*it)->get_rt_type() == rt_type::rt_city)
		{
			room *pRoom = dynamic_cast<room*>(*it);
			if (pRoom != nullptr && !pRoom->IsUserFull())
			{
				return pRoom;
			}
		}
	}
	return nullptr;
}

myroutine * MyThreadPoolEx::takeroutine()
{
	RT_LOCK;
	if (m_rt_vec.size() <= 0)
	{
		return nullptr;
	}

	int32 routine_size = m_rt_vec.size();
	for (int32 idx = 0; idx < routine_size; ++idx)
	{
		 m_take_index = (m_take_index + idx) % routine_size;
		 myroutine * rtPtr = m_rt_vec[m_take_index];
		 if (nullptr != rtPtr && rtPtr->reach_tick())
		 {
			 return rtPtr;
		 }
	}
	return nullptr;
}

void MyThreadPoolEx::release_routine()
{
	for (my_routine_vec::iterator itF = m_rt_vec.begin(); itF != m_rt_vec.end(); ++itF)
	{
		delete *itF;
	}
	MyLog::Log("release routine, count(%d)", m_rt_vec.size());
	m_rt_vec.clear();
}

void MyThreadPoolEx::Tick_PrintRoomInfo()
{
	if (m_TimeClock.DiffSec())
	{
		int32 nValidUser = 0;
		for (int idx = 0; idx < m_rt_vec.size(); ++idx)
		{
			const room *pRoom = dynamic_cast<room*>(m_rt_vec[idx]);
			if (nullptr != pRoom)
			{

				int32 nUserCnt = pRoom->GetValidUserCnt();
				int32 nThreadId = pRoom->get_id();
				nValidUser += nUserCnt;

				MyLog::Log("RoomInfo, usercnt(%d), room(%d)", nUserCnt, nThreadId);
			}
		}
		MyLog::Log("RoomInfo, total usercnt(%d), roomnum(%d)", nValidUser, m_rt_vec.size());
	}
	m_TimeClock.Tick();
}
