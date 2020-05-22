#pragma once

#include <mutex>
#include "../GameDefine/GameDefine_Room.h"
#include "../Utils/TimeUtils.h"


#define LOCK_RT std::lock_guard<std::mutex> lock(m_mutex);

class myroutine
{
public:
	myroutine(int routineid) :
		m_id(routineid)
	{
		clean();
	}
	~myroutine(){};
	void clean()
	{
		m_tick_interval_ms = MYROUTINE_TICK_INTERVAL_DEFAULT;
		m_last_tick_time_ms = 0;
	}
public:
	void tick();
	virtual void tick_routine(){};
	virtual rt_type get_rt_type(){ return rt_type::invalid; }
public:
	bool reach_tick();
	void set_interval(int32 interval_ms){ m_tick_interval_ms = interval_ms; }
	int32 get_id() const{ return m_id; }

protected:
	int32 m_id;
private:

	uint64 m_tick_interval_ms;
	uint64 m_last_tick_time_ms;

	std::mutex m_mutex;
};