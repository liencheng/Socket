#pragma once
#include "stdafx.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

int HelloLua(lua_State *pLuaState);