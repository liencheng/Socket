#include "stdafx.h"
#include "ToolManager.h"
#include <thread>
#include "ThreadPool.h"
#include <iostream>
#include <map>
#include "Utils/TimeUtils.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	
	//init time
	MyTimeUtils::init();
	//load config
	//init thread
	cout << "main thread pid:" << GetCurrentThreadId() << endl;
	int nTickCt = 0;
	ToolManager toolMgr;
	toolMgr.InitNetWork();
	toolMgr.InitAddr();
	toolMgr.InitListenSocket();
	//tick logic
	cout << "main tread start" << endl;
	while (true)
	{
		Sleep(10);
		MyTimeUtils::tick();
		toolMgr.Tick();
	};

	return 0;
}

