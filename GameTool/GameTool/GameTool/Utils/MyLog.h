#pragma once
#include <string>	
#include <fstream>
#include <tchar.h>
#include <ctime>
#include <iostream>

class MyLog
{
public:
	static void Log(const char* format, ...);
	
	/*
	static void Log(const char * content);

	template<typename T1>
	static void Log(const char * content, T1 p0)
	{
		return;
		std::string strArgData;
		char szBuffer[0x1024];
		memset(szBuffer, 0, sizeof(szBuffer));
		printf(content, p0);
		cout << endl;
	}
	template<typename T1, typename T2>
	static void Log(const char * content, T1 p0, T2 p1)
	{
		return;
		std::string strArgData;
		char szBuffer[0x1024];
		memset(szBuffer, 0, sizeof(szBuffer));
		printf(content, p0, p1);
		cout << endl;
	}
	*/
};