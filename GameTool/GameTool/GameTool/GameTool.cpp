#include "stdafx.h"
#include "ToolManager.h"
#include <thread>
#include "ThreadPool.h"
#include <iostream>

using namespace std;

#define THREAD_POOL_COUNT (10)

int _tmain(int argc, _TCHAR* argv[])
{
	MyThreadPool threadPool(THREAD_POOL_COUNT);

	MyThread my;
	my.StartThread();

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

