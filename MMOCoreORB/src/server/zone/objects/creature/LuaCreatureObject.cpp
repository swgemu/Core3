/*
 * LuaCreatureObject.cpp
 *
 *  Created on: 31/08/2009
 *      Author: victor
 */

#include "LuaCreatureObject.h"
#include "CreatureObject.h"
#include "server/zone/objects/cell/CellObject.h"

const char LuaCreatureObject::className[] = "LuaCreatureObject";

Luna<LuaCreatureObject>::RegType LuaCreatureObject::Register[] = {
		{ "_setObject", &LuaCreatureObject::_setObject },
		{ "getBankCredits", &LuaCreatureObject::getBankCredits },
		{ "setBankCredits", &LuaCreatureObject::setBankCredits },
		{ "sendSystemMessage", &LuaCreatureObject::sendSystemMessage },
		{ "playMusicMessage", &LuaCreatureObject::playMusicMessage },
		{ "sendNewbieTutorialRequest", &LuaCreatureObject::sendNewbieTutorialRequest },
		{ "hasScreenPlayState", &LuaCreatureObject::hasScreenPlayState },
		{ "setScreenPlayState", &LuaCreatureObject::setScreenPlayState },
		{ "sendNewbieTutorialEnableHudElement", &LuaCreatureObject::sendNewbieTutorialEnableHudElement },
		{ "getInCellNumber", &LuaCreatureObject::getInCellNumber },
		{ "sendOpenHolocronToPageMessage", &LuaCreatureObject::sendOpenHolocronToPageMessage },
		{ "setHAM", &LuaCreatureObject::setHAM },
		{ "getTargetID", &LuaCreatureObject::getTargetID },
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

LuaCreatureObject::LuaCreatureObject(lua_State *L) : LuaSceneObject(L) {
	realObject = (CreatureObject*)lua_touserdata(L, 1);
}

LuaCreatureObject::~LuaCreatureObject(){
}

int LuaCreatureObject::_setObject(lua_State* L) {
	realObject = (CreatureObject*)lua_touserdata(L, -1);

	return 0;
}

int LuaCreatureObject::sendOpenHolocronToPageMessage(lua_State* L) {
	realObject->sendOpenHolocronToPageMessage();

	return 0;
}

int LuaCreatureObject::sendSystemMessage(lua_State* L) {
	String value = lua_tostring(L, -1);
	realObject->sendSystemMessage(value);

	return 0;
}

int LuaCreatureObject::setHAM(lua_State* L) {
	uint32 type = (uint32) lua_tonumber(L, -2);
	uint32 value = (uint32) lua_tonumber(L, -1);

	realObject->setHAM(type, value);

	return 0;
}

int LuaCreatureObject::playMusicMessage(lua_State *L) {
	String value = lua_tostring(L, -1);
	realObject->playMusicMessage(value);

	return 0;
}

int LuaCreatureObject::setBankCredits(lua_State *L) {
	uint32 credits = (uint32) lua_tonumber(L, -1);

	realObject->setBankCredits(credits);

	return 0;
}

int LuaCreatureObject::sendNewbieTutorialRequest(lua_State *L) {
	String value = lua_tostring(L, -1);
	realObject->sendNewbieTutorialRequest(value);

	return 0;
}

int LuaCreatureObject::hasScreenPlayState(lua_State *L) {
	String play = lua_tostring(L, -1);
	uint64 stateToCheck = lua_tonumber(L, -2);

	uint64 state = realObject->getScreenPlayState(play);

	if (state & stateToCheck)
		lua_pushnumber(L, 1);
	else
		lua_pushnumber(L, 0);

	return 1;
}

int LuaCreatureObject::sendNewbieTutorialEnableHudElement(lua_State* L) {
	String ui = lua_tostring(L, -2);
	int enable = lua_tonumber(L, -1);

	realObject->sendNewbieTutorialEnableHudElement(ui, enable);

	return 0;
}

int LuaCreatureObject::getInCellNumber(lua_State* L) {
	SceneObject* parent = realObject->getParent();

	if (parent == NULL || !parent->isCellObject())
		lua_pushnumber(L, -1);
	else {
		int cellId = ((CellObject*)parent)->getCellNumber();

		lua_pushnumber(L, cellId);
	}

	return 1; // we return the number of vars pushed to the L stack
}

int LuaCreatureObject::setScreenPlayState(lua_State *L) {
	String play = lua_tostring(L, -1);
	uint64 stateToSet = lua_tonumber(L, -2);

	realObject->setScreenPlayState(play, stateToSet | realObject->getScreenPlayState(play));

	return 0;
}

int LuaCreatureObject::getTargetID(lua_State* L) {
	uint64 targetID = realObject->getTargetID();

	lua_pushnumber(L, targetID);

	return 1;
}

int LuaCreatureObject::getBankCredits(lua_State *L) {
	lua_pushnumber(L, realObject->getBankCredits());

	return 1; // we return the number of vars pushed to the L stack
}
