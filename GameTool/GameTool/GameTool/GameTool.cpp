#include "stdafx.h"
#include "ToolManager.h"
#include <thread>
#include "ThreadPool.h"
#include <iostream>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "main thread pid:" << GetCurrentThreadId() << endl;
	int nTickCt = 0;
	ToolManager toolMgr;
	toolMgr.InitNetWork();
	toolMgr.InitAddr();
	toolMgr.InitListenSocket();
	cout << "main tread start" << endl;
	while (true)
	{
		toolMgr.Tick();
	};

	return 0;
}

