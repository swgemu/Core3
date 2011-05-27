/*
 * LuaBuildingObject.cpp
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#include "LuaBuildingObject.h"
#include "BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"

const char LuaBuildingObject::className[] = "LuaBuildingObject";

Luna<LuaBuildingObject>::RegType LuaBuildingObject::Register[] = {
		{ "_setObject", &LuaBuildingObject::_setObject },
		{ "getCell", &LuaBuildingObject::getCell },
		{ "getParent", &LuaSceneObject::getParent },
		{ "getObjectID", &LuaSceneObject::getObjectID },
		{ "getPositionX", &LuaSceneObject::getPositionX },
		{ "getPositionY", &LuaSceneObject::getPositionY },
		{ "getPositionZ", &LuaSceneObject::getPositionZ },
		{ "getParentID", &LuaSceneObject::getParentID },
		{ "getServerObjectCRC", &LuaSceneObject::getServerObjectCRC },

		{ 0, 0 }
};

LuaBuildingObject::LuaBuildingObject(lua_State *L) : LuaSceneObject(L) {
	realObject = (BuildingObject*)lua_touserdata(L, 1);
}

LuaBuildingObject::~LuaBuildingObject(){
}

int LuaBuildingObject::_setObject(lua_State* L) {
	realObject = (BuildingObject*)lua_touserdata(L, -1);

	return 0;
}

int LuaBuildingObject::getCell(lua_State* L) {
	int number = lua_tonumber(L, -1);

	lua_pushlightuserdata(L, realObject->getCell(number));

	return 1;
}
