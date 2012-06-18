/*
 * LuaPlayerObject.cpp
 *
 *  Created on: 13/01/2012
 *      Author: victor
 */

#include "LuaPlayerObject.h"
#include "engine/engine.h"
#include "FactionStatus.h"
#include "server/zone/managers/crafting/schematicmap/SchematicMap.h"

const char LuaPlayerObject::className[] = "LuaPlayerObject";

Luna<LuaPlayerObject>::RegType LuaPlayerObject::Register[] = {
		{ "_setObject", &LuaPlayerObject::_setObject },
		{ "getFactionStanding", &LuaPlayerObject::getFactionStanding },
		{ "setFactionStatus", &LuaPlayerObject::setFactionStatus },
		{ "isOnLeave", &LuaPlayerObject::isOnLeave },
		{ "isOvert", &LuaPlayerObject::isOvert },
		{ "isCovert", &LuaPlayerObject::isCovert },
		{ "isChangingFactionStatus", &LuaPlayerObject::isChangingFactionStatus },
		{ "increaseFactionStanding", &LuaPlayerObject::increaseFactionStanding },
		{ "decreaseFactionStanding", &LuaPlayerObject::decreaseFactionStanding },
		{ "addWaypoint", &LuaPlayerObject::addWaypoint },
		{ "addRewardedSchematic", &LuaPlayerObject::addRewardedSchematic},
		{ "addPermissionGroup", &LuaPlayerObject::addPermissionGroup},
		{ "removePermissionGroup", &LuaPlayerObject::removePermissionGroup},
		{ "awardBadge", &LuaPlayerObject::awardBadge},
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

	float standing = realObject->getFactionStanding(faction);

	lua_pushnumber(L, standing);

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

int LuaPlayerObject::increaseFactionStanding(lua_State* L) {
	float val = lua_tonumber(L, -1);
	const char* str = lua_tostring(L, -2);

	realObject->increaseFactionStanding(str, val);

	return 0;
}

int LuaPlayerObject::decreaseFactionStanding(lua_State* L) {
	float val = lua_tonumber(L, -1);
	const char* str = lua_tostring(L, -2);

	realObject->decreaseFactionStanding(str, val);

	return 0;
}

//addWaypoint(planet, name, desc, x, y, color, active, notifyClient)
int LuaPlayerObject::addWaypoint(lua_State* L) {
	String planet = lua_tostring(L, -8);
	String customName = lua_tostring(L, -7);
	String desc = lua_tostring(L, -6);
	float x = lua_tonumber(L, -5);
	float y = lua_tonumber(L, -4);
	int color = lua_tointeger(L, -3);
	bool active = lua_toboolean(L, -2);
	bool notifyClient = lua_toboolean(L, -1);

	ManagedReference<WaypointObject*> waypoint = realObject->addWaypoint(planet, x, y, false);
	waypoint->setCustomObjectName(customName, false);
	waypoint->setColor(color);
	waypoint->setActive(active);

	if (!desc.isEmpty())
		waypoint->setDetailedDescription(desc);

	realObject->setWaypoint(waypoint, notifyClient);

	return 0;
}

int LuaPlayerObject::addRewardedSchematic(lua_State* L){
	String templateString = lua_tostring(L, -3);
	int quantity = lua_tointeger(L, -2);
	bool notifyClient = lua_toboolean(L, -1);

	DraftSchematic* schematic = SchematicMap::instance()->get(templateString.hashCode());

	if (schematic != NULL)
		realObject->addRewardedSchematic(schematic, quantity, notifyClient);

	return 0;
}

int LuaPlayerObject::addPermissionGroup(lua_State* L){
	String permissionGroup = lua_tostring(L, -2);
	bool updateBuildings = lua_toboolean(L, -1);

	realObject->addPermissionGroup(permissionGroup, updateBuildings);

	return 0;
}

int LuaPlayerObject::removePermissionGroup(lua_State* L){
	String permissionGroup = lua_tostring(L, -2);
	bool updateBuildings = lua_toboolean(L, -1);

	realObject->removePermissionGroup(permissionGroup, updateBuildings);

	return 0;
}

int LuaPlayerObject::awardBadge(lua_State* L){
	int badgeId = lua_tointeger(L, -1);

	realObject->awardBadge(badgeId);

	return 0;
}
