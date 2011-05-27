/*
 * LuaSceneObject.cpp
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#include "LuaSceneObject.h"
#include "SceneObject.h"
#include "server/zone/objects/cell/CellObject.h"

const char LuaSceneObject::className[] = "LuaSceneObject";

Luna<LuaSceneObject>::RegType LuaSceneObject::Register[] = {
		{ "_setObject", &LuaSceneObject::_setObject },
		{ "getParent", &LuaSceneObject::getParent },
		{ "getObjectID", &LuaSceneObject::getObjectID },
		{ "getPositionX", &LuaSceneObject::getPositionX },
		{ "getPositionY", &LuaSceneObject::getPositionY },
		{ "getPositionZ", &LuaSceneObject::getPositionZ },
		{ "getParentID", &LuaSceneObject::getParentID },
		{ "isInRangeWithObject", &LuaSceneObject::isInRangeWithObject },
		{ "getDistanceTo", &LuaSceneObject::getDistanceTo },
		{ "getServerObjectCRC", &LuaSceneObject::getServerObjectCRC },


		{ 0, 0 }
};

LuaSceneObject::LuaSceneObject(lua_State *L) {
	realObject = (SceneObject*)lua_touserdata(L, 1);
}

LuaSceneObject::~LuaSceneObject(){
}

int LuaSceneObject::_setObject(lua_State* L) {
	realObject = (SceneObject*)lua_touserdata(L, -1);

	return 0;
}

int LuaSceneObject::getPositionX(lua_State* L) {
	lua_pushnumber(L, realObject->getPositionX());

	return 1;
}

int LuaSceneObject::getPositionZ(lua_State* L) {
	lua_pushnumber(L, realObject->getPositionZ());

	return 1;
}

int LuaSceneObject::getPositionY(lua_State* L) {
	lua_pushnumber(L, realObject->getPositionY());

	return 1;
}

int LuaSceneObject::getObjectID(lua_State* L) {
	lua_pushnumber(L, realObject->getObjectID());

	return 1;
}

int LuaSceneObject::getParentID(lua_State* L) {
	lua_pushnumber(L, realObject->getParentID());

	return 1;
}

int LuaSceneObject::isInRange(lua_State* L) {
//public boolean isInRange(float x, float y, float range) {
	float range = lua_tonumber(L, -1);
	float y = lua_tonumber(L, -2);
	float x = lua_tonumber(L, -3);

	bool res = (static_cast<QuadTreeEntry*>(realObject))->isInRange(x, y, range);

	lua_pushnumber(L, res);

	return 1;
}

int LuaSceneObject::getDistanceTo(lua_State* L) {
	SceneObject* obj = (SceneObject*)lua_touserdata(L, -1);

	float res = realObject->getDistanceTo(obj);

	lua_pushnumber(L, res);

	return 1;
}

int LuaSceneObject::getServerObjectCRC(lua_State* L) {
	uint32 crc = realObject->getServerObjectCRC();

	lua_pushnumber(L, crc);

	return 1;
}

int LuaSceneObject::isInRangeWithObject(lua_State* L) {
	float range = lua_tonumber(L, -1);
	SceneObject* obj = (SceneObject*)lua_touserdata(L, -2);

	bool res = realObject->isInRange(obj, range);

	lua_pushnumber(L, res);

	return 1;
}

int LuaSceneObject::getParent(lua_State* L) {
	SceneObject* obj = realObject->getParent();

	lua_pushlightuserdata(L, obj);

	return 1;
}

int LuaSceneObject::wlock(lua_State* L) {
	return 0;
}

int LuaSceneObject::unlock(lua_State* L) {
	return 0;
}
