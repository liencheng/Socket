#pragma once


#define MYROUTINE_TICK_INTERVAL_DEFAULT (50)    //Ĭ��TICK���
#define HEART_BEAT_SLOW (200)                   //���ڸ�ֵ����Ϊ��������
#define ROOM_USER_MAX (64)						//ÿ�������������

enum class rt_type
{
	invalid,
	rt_city,
	rt_wild,
	rt_cs,
	rt_table,
};