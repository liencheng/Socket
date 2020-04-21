#include <string>
#include <windows.h>
#include <string>
#include <fstream>
#include <tchar.h>
#include <ctime>
#include "MyLog.h"
#include <iostream>

void MyLog::Log(const char* format, ...)
{
		va_list arglist;
		std::string strArgData;
		char szBuffer[0x1024];
		memset(szBuffer, 0, sizeof(szBuffer));
		va_start(arglist, format);
		vsprintf_s(szBuffer, format, arglist);
		va_end(arglist);
		strArgData = szBuffer;
		std::cout << strArgData << std::endl;

}