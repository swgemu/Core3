/*
 * LuaActiveArea.cpp
 *
 *  Created on: 21/01/2012
 *      Author: xyborn
 */

#include "LuaActiveArea.h"
#include "server/zone/objects/area/ActiveArea.h"

const char LuaActiveArea::className[] = "LuaActiveArea";

Luna<LuaActiveArea>::RegType LuaActiveArea::Register[] = {
		{ "_setObject", &LuaActiveArea::_setObject },
		{ "_getObject", &LuaSceneObject::_getObject },
		{ "setRadius", &LuaActiveArea::setRadius },
		{ "getRadius", &LuaActiveArea::getRadius },
		{ "setNoBuildArea", &LuaActiveArea::setNoBuildArea },
		{ "isNoBuildArea", &LuaActiveArea::isNoBuildArea },
		{ "getObjectID", &LuaSceneObject::getObjectID },
		{ "setCellObjectID", &LuaActiveArea::setCellObjectID },
		{ "getCellObjectID", &LuaActiveArea::getCellObjectID },
		{ "setNoSpawnArea", &LuaActiveArea::setNoSpawnArea },
		{ 0, 0 }
};

LuaActiveArea::LuaActiveArea(lua_State *L) : LuaSceneObject(L) {
#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<ActiveArea*>(_getRealSceneObject());

	assert(!_getRealSceneObject() || realObject != NULL);
#else
	realObject = static_cast<ActiveArea*>(lua_touserdata(L, 1));
#endif
}

LuaActiveArea::~LuaActiveArea(){
}

int LuaActiveArea::_setObject(lua_State* L) {
	LuaSceneObject::_setObject(L);

#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<ActiveArea*>(_getRealSceneObject());

	assert(!_getRealSceneObject() || realObject != NULL);
#else
	realObject = static_cast<ActiveArea*>(lua_touserdata(L, -1));
#endif

	return 0;
}

int LuaActiveArea::getRadius(lua_State* L) {
	lua_pushnumber(L, realObject->getRadius());

	return 1;
}

int LuaActiveArea::setRadius(lua_State* L) {
	int radius = lua_tonumber(L, -1);

	realObject->setRadius(radius);

	return 0;
}

int LuaActiveArea::setNoBuildArea(lua_State* L) {
	bool val = lua_toboolean(L, -1);

	realObject->setNoBuildArea(val);

	return 0;
}

int LuaActiveArea::isNoBuildArea(lua_State* L) {
	bool val = realObject->isNoBuildArea();

	lua_pushboolean(L, val);

	return 1;
}

int LuaActiveArea::setCellObjectID(lua_State* L) {
	uint64 val = lua_tointeger(L, -1);

	realObject->setCellObjectID(val);

	return 0;
}

int LuaActiveArea::getCellObjectID(lua_State* L) {
	uint64 val = realObject->getCellObjectID();

	lua_pushinteger(L, val);

	return 1;
}

int LuaActiveArea::setNoSpawnArea(lua_State* L) {
	bool val = lua_toboolean(L, -1);

	realObject->setNoSpawnArea(val);

	return 0;
}
