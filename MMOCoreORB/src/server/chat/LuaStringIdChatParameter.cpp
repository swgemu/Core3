/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "LuaStringIdChatParameter.h"

const char LuaStringIdChatParameter::className[] = "LuaStringIdChatParameter";

Luna<LuaStringIdChatParameter>::RegType LuaStringIdChatParameter::Register[] = {
		{ "_setObject", &LuaStringIdChatParameter::_setObject },
		{ "_getObject", &LuaStringIdChatParameter::_getObject },
		{ "setTT", &LuaStringIdChatParameter::setTT },
		{ "setTU", &LuaStringIdChatParameter::setTU },
		{ "setTO", &LuaStringIdChatParameter::setTO },
		{ "setDI", &LuaStringIdChatParameter::setDI },
		{ "setDF", &LuaStringIdChatParameter::setDF },
		{ 0, 0 }
};

LuaStringIdChatParameter::LuaStringIdChatParameter(lua_State * L) {
	String fullPath = lua_tostring(L, 1);
	realObject = new StringIdChatParameter(fullPath);
}

LuaStringIdChatParameter::~LuaStringIdChatParameter() {
}

int LuaStringIdChatParameter::_setObject(lua_State* L) {
	realObject = static_cast<StringIdChatParameter*>(lua_touserdata(L, -1));

	return 0;
}

int LuaStringIdChatParameter::_getObject(lua_State* L) {
	lua_pushlightuserdata(L, realObject.get());

	return 1;
}

int LuaStringIdChatParameter::setTT(lua_State *L) {
	String tt = lua_tostring(L, -1);

	realObject->setTT(tt);

	return 0;
}

int LuaStringIdChatParameter::setTU(lua_State *L) {
	String tu = lua_tostring(L, -1);

	realObject->setTU(tu);

	return 0;
}

int LuaStringIdChatParameter::setTO(lua_State *L) {
	String to = lua_tostring(L, -1);

	realObject->setTO(to);

	return 0;
}

int LuaStringIdChatParameter::setDI(lua_State *L) {
	int di = lua_tointeger(L, -1);

	realObject->setDI(di);

	return 0;
}

int LuaStringIdChatParameter::setDF(lua_State *L) {
	float df = lua_tonumber(L, -1);

	realObject->setDF(df);

	return 0;
}
