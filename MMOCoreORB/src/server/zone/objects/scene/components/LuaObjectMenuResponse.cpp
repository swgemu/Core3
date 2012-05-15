/*
 * LuaObjectMenuResponse.cpp
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#include "LuaObjectMenuResponse.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

const char LuaObjectMenuResponse::className[] = "LuaObjectMenuResponse";

Luna<LuaObjectMenuResponse>::RegType LuaObjectMenuResponse::Register[] = {
		{ "_setObject", &LuaObjectMenuResponse::_setObject },
		{ "addRadialMenuItem", &LuaObjectMenuResponse::addRadialMenuItem },
		{ "addRadialMenuItemToRadialID", &LuaObjectMenuResponse::addRadialMenuItemToRadialID },
		{ 0, 0 }
};

LuaObjectMenuResponse::LuaObjectMenuResponse(lua_State *L) {
	realObject = (ObjectMenuResponse*)lua_touserdata(L, 1);
}

LuaObjectMenuResponse::~LuaObjectMenuResponse(){
}

int LuaObjectMenuResponse::_setObject(lua_State* L) {
	realObject = (ObjectMenuResponse*)lua_touserdata(L, -1);

	return 0;
}

int LuaObjectMenuResponse::addRadialMenuItem(lua_State* L) {
	uint8 radialid = lua_tointeger(L, -3);
	uint8 callback = lua_tointeger(L, -2);
	String text = lua_tostring(L, -1);

	realObject->addRadialMenuItem(radialid, callback, text);

	return 0;
}

int LuaObjectMenuResponse::addRadialMenuItemToRadialID(lua_State* L) {
	uint8 parentRadialID = lua_tointeger(L, -4);
	uint8 newRadialID = lua_tointeger(L, -3);
	uint8 callback = lua_tointeger(L, -2);
	String text = lua_tostring(L, -1);

	realObject->addRadialMenuItemToRadialID(parentRadialID, newRadialID, callback, text);

	return 0;
}
