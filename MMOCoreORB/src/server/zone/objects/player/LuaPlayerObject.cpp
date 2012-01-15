/*
 * LuaPlayerObject.cpp
 *
 *  Created on: 13/01/2012
 *      Author: victor
 */

#include "LuaPlayerObject.h"
#include "engine/engine.h"
#include "FactionStatus.h"

const char LuaPlayerObject::className[] = "LuaPlayerObject";

Luna<LuaPlayerObject>::RegType LuaPlayerObject::Register[] = {
		{ "_setObject", &LuaPlayerObject::_setObject },
		{ "getFactionStanding", &LuaPlayerObject::getFactionStanding },
		{ "setFactionStatus", &LuaPlayerObject::setFactionStatus },
		{ "isOnLeave", &LuaPlayerObject::isOnLeave },
		{ "isOvert", &LuaPlayerObject::isOvert },
		{ "isCovert", &LuaPlayerObject::isCovert },
		{ "isChangingFactionStatus", &LuaPlayerObject::isChangingFactionStatus },
		{ 0, 0 }
};


LuaPlayerObject::LuaPlayerObject(lua_State *L) : LuaIntangibleObject(L) {
	realObject = (PlayerObject*)lua_touserdata(L, 1);
}

LuaPlayerObject::~LuaPlayerObject() {
}

int LuaPlayerObject::_setObject(lua_State* L) {
	realObject = (PlayerObject*)lua_touserdata(L, -1);

	return 0;
}

int LuaPlayerObject::getFactionStanding(lua_State* L) {
	//String faction = lua_tostring(L, -1);

	const char* str = lua_tostring(L, -1);

	String faction(str);

	int standing = realObject->getFactionStanding(faction);

	lua_pushinteger(L, standing);

	return 1;
}

int LuaPlayerObject::isOnLeave(lua_State* L) {
	lua_pushboolean(L, realObject->getFactionStatus() == FactionStatus::ONLEAVE);

	return 1;
}

int LuaPlayerObject::isOvert(lua_State* L) {
	lua_pushboolean(L, realObject->getFactionStatus() == FactionStatus::OVERT);

	return 1;
}

int LuaPlayerObject::isCovert(lua_State* L) {
	lua_pushboolean(L, realObject->getFactionStatus() == FactionStatus::COVERT);

	return 1;
}

int LuaPlayerObject::isChangingFactionStatus(lua_State* L) {
	lua_pushboolean(L, realObject->getFactionStatus() == FactionStatus::CHANGINGSTATUS);

	return 1;
}

int LuaPlayerObject::setFactionStatus(lua_State* L) {
	int status = lua_tointeger(L, -1);

	realObject->setFactionStatus(status);

	return 0;
}
