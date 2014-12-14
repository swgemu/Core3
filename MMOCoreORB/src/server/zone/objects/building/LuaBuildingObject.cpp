/*
 * LuaBuildingObject.cpp
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#include "LuaBuildingObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

const char LuaBuildingObject::className[] = "LuaBuildingObject";

Luna<LuaBuildingObject>::RegType LuaBuildingObject::Register[] = {
		{ "_setObject", &LuaBuildingObject::_setObject },
		{ "_getObject", &LuaSceneObject::_getObject },
		{ "getCell", &LuaBuildingObject::getCell },
		{ "getOwnerID", &LuaBuildingObject::getOwnerID },
		{ "getParent", &LuaSceneObject::getParent },
		{ "getObjectID", &LuaSceneObject::getObjectID },
		{ "getPositionX", &LuaSceneObject::getPositionX },
		{ "getPositionY", &LuaSceneObject::getPositionY },
		{ "getPositionZ", &LuaSceneObject::getPositionZ },
		{ "getParentID", &LuaSceneObject::getParentID },
		{ "getServerObjectCRC", &LuaSceneObject::getServerObjectCRC },
		{ "getFaction", &LuaTangibleObject::getFaction },
		{ "grantPermission", &LuaBuildingObject::grantPermission },
		{ "broadcastSpecificCellPermissions", &LuaBuildingObject::broadcastSpecificCellPermissions },
		{ "spawnChildCreature", &LuaBuildingObject::spawnChildCreature },
		{ "spawnChildSceneObject", &LuaBuildingObject::spawnChildSceneObject },
		{ "destroyChildObjects", &LuaBuildingObject::destroyChildObjects },
		{ "initializeStaticGCWBase", &LuaBuildingObject::initializeStaticGCWBase },
		{ 0, 0 }
};

LuaBuildingObject::LuaBuildingObject(lua_State *L) : LuaTangibleObject(L) {
	realObject = (BuildingObject*)lua_touserdata(L, 1);
}

LuaBuildingObject::~LuaBuildingObject(){
}

int LuaBuildingObject::_setObject(lua_State* L) {
	realObject = (BuildingObject*)lua_touserdata(L, -1);

	LuaTangibleObject::_setObject(L);

	return 0;
}

int LuaBuildingObject::getCell(lua_State* L) {
	int number = lua_tonumber(L, -1);

	lua_pushlightuserdata(L, realObject->getCell(number));

	return 1;
}

int LuaBuildingObject::getOwnerID(lua_State* L) {
	lua_pushinteger(L, realObject->getOwnerObjectID());

	return 1;
}

int LuaBuildingObject::grantPermission(lua_State* L) {
	String list = lua_tostring(L, -2);
	uint64 playerid = lua_tointeger(L, -1);

	int i = 0;

	if (list == "ADMIN" || list == "BAN" || list == "ENTRY") {
		realObject->grantPermission(list, playerid);
		i = 1;
	}

	lua_pushnumber(L, i);

	return 1;
}

int LuaBuildingObject::broadcastSpecificCellPermissions(lua_State* L) {
	uint64 cellid = lua_tointeger(L, -1);

	realObject->broadcastCellPermissions(cellid);

	return 0;
}

int LuaBuildingObject::spawnChildCreature(lua_State* L) {
	uint64 parentID = lua_tointeger(L, -1);
	float heading = lua_tonumber(L, -2);
	float y = lua_tonumber(L, -3);
	float z = lua_tonumber(L, -4);
	float x = lua_tonumber(L, -5);
	int respawnTimer = lua_tointeger(L, -6);
	String mobile = lua_tostring(L, -7);

	realObject->spawnChildCreature(mobile, respawnTimer, x, z, y, heading, parentID);

	return 0;
}

int LuaBuildingObject::spawnChildSceneObject(lua_State* L) {
	float dz = lua_tonumber(L, -1);
	float dy = lua_tonumber(L, -2);
	float dx = lua_tonumber(L, -3);
	float dw = lua_tonumber(L, -4);
	uint64 cellID = lua_tointeger(L, -5);
	float y = lua_tonumber(L, -6);
	float z = lua_tonumber(L, -7);
	float x = lua_tonumber(L, -8);
	String script = lua_tostring(L, -9);

	realObject->spawnChildSceneObject(script, x, z, y, cellID, dw, dx, dy, dz);

	return 0;
}

int LuaBuildingObject::destroyChildObjects(lua_State* L) {
	realObject->destroyChildObjects();

	return 0;
}

int LuaBuildingObject::initializeStaticGCWBase(lua_State* L) {
	unsigned int faction = lua_tointeger(L, -1);

	Zone* zone = realObject->getZone();

	if (zone == NULL)
		return 0;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return 0;

	gcwMan->unregisterGCWBase(realObject);

	Locker locker(realObject);

	realObject->setFaction(faction);
	gcwMan->initializeNewVulnerability(realObject);
	gcwMan->registerGCWBase(realObject, false);

	return 0;
}
