#pragma once

#include "stdafx.h"
#include <vector>
#include "LuaDefine.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace std;

class CallLuaP
{

public: 
	CallLuaP(){ Clean(); };
	void Clean()
	{
		m_ParamList.clear();
	}
public:
	std::vector<int32> m_ParamList;
};

class CallLuaRetP
{
public:
	CallLuaRetP(){ Clean(); };

	void Clean()
	{
		m_ParamList.clear();
	}
public:
	std::vector<int32> m_ParamList;
};

class LuaInterface
{
public:
	LuaInterface();

	bool Init();
	bool Close();
	bool LoadScript(int32 nLuaId);
	bool LoadAllScript();
	bool CallLuaFunction(int32 nLuaId, const char * szFunc, CallLuaP &p);
	bool RegisterCppFunction2Lua();
private:
	lua_State * m_pLuaState;
};