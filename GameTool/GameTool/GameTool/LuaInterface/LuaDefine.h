#pragma once

#define Lua_Register(function) \
	lua_register(m_pLuaState, #function, function)