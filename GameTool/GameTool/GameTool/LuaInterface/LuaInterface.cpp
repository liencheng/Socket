#include "LuaInterface.h"
#include "Utils/MyLog.h"
#include "LuaFunction.h"

bool LuaInterface::Init()
{
	//分配一个虚拟机
	m_pLuaState = luaL_newstate();
	if (nullptr == m_pLuaState)
	{
		MyLog::Log("init lua interface, m_pLuaState == null.");
		return false;
	}
	luaL_openlibs(m_pLuaState);

	return true;
}

bool LuaInterface::Close()
{
	if (nullptr == m_pLuaState)
	{
		MyLog::Log("Luainterface, close error. m_pLuaState is null.");
		return false;
	}

	lua_close(m_pLuaState);
	m_pLuaState = nullptr;
	MyLog::Log("close lua succ.");
	return true;
}

bool LuaInterface::LoadScript(int32 nLuaId)
{
	char *pFilePath = nullptr;
	int32 nDoRet = luaL_dofile(m_pLuaState, pFilePath);
	if (nDoRet == LUA_OK)
	{
		MyLog::Log("load script succ. luaid:(%d)", nLuaId);
		return true;
	}
	else
	{
		MyLog::Log("load script failed. luaid:(%d)", nLuaId);
	}
	return false;
}

bool LuaInterface::LoadAllScript()
{
	return false;
}

bool LuaInterface::RegisterCppFunction2Lua()
{
	Lua_Register(HelloLua);
	return true;
}

bool LuaInterface::CallLuaFunction(int32 nLuaId, const char * szFunc, CallLuaP &p)
{
	return false;
}



