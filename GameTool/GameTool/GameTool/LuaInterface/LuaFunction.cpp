#include "LuaFunction.h"

int HelloLua(lua_State *pLuaState)
{
	MyLog::Log("Hello lua.");
	return LUA_OK;
}