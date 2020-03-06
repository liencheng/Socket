#include "stdafx.h"
#include "ToolManager.h"

int _tmain(int argc, _TCHAR* argv[])
{

	int nTickCt = 0;
	ToolManager toolMgr;
	toolMgr.InitNetWork();
	toolMgr.InitAddr();
	toolMgr.InitListenSocket();
	while (true)
	{
		toolMgr.Tick();
	};
	return 0;
}

