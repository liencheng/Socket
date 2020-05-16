#pragma once


#define MYROUTINE_TICK_INTERVAL_DEFAULT (50)    //默认TICK间隔
#define HEART_BEAT_SLOW (200)                   //大于该值，认为是慢心跳
#define ROOM_USER_MAX (64)						//每个房间最大人数

enum class rt_type
{
	invalid,
	rt_city,
	rt_wild,
	rt_cs,
	rt_table,
};