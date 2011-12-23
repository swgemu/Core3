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
		{ "getScreenPlayState", &LuaCreatureObject::getScreenPlayState },
		{ "playEffect", &LuaCreatureObject::playEffect },
		{ "sendNewbieTutorialEnableHudElement", &LuaCreatureObject::sendNewbieTutorialEnableHudElement },
		{ "getInCellNumber", &LuaCreatureObject::getInCellNumber },
		{ "sendOpenHolocronToPageMessage", &LuaCreatureObject::sendOpenHolocronToPageMessage },
		{ "inflictDamage", &LuaCreatureObject::inflictDamage },
		{ "setHAM", &LuaCreatureObject::setHAM },
		{ "getHAM", &LuaCreatureObject::getHAM },
		{ "getMaxHAM", &LuaCreatureObject::getMaxHAM },
		{ "getTargetID", &LuaCreatureObject::getTargetID },
		{ "clearCombatState", &LuaCreatureObject::clearCombatState },
		{ "getParent", &LuaSceneObject::getParent },
		{ "getObjectID", &LuaSceneObject::getObjectID },
		{ "getPositionX", &LuaSceneObject::getPositionX },
		{ "getPositionY", &LuaSceneObject::getPositionY },
		{ "getPositionZ", &LuaSceneObject::getPositionZ },
		{ "getParentID", &LuaSceneObject::getParentID },
		{ "isInRangeWithObject", &LuaSceneObject::isInRangeWithObject },
		{ "getDistanceTo", &LuaSceneObject::getDistanceTo },
		{ "getServerObjectCRC", &LuaSceneObject::getServerObjectCRC },
		{ "setState", &LuaCreatureObject::setState},
		{ "setPosture", &LuaCreatureObject::setPosture},
		{ "setCustomObjectName", &LuaCreatureObject::setCustomObjectName},
		{ "hasSkill", &LuaCreatureObject::hasSkill},
		{ "removeSkill", &LuaCreatureObject::removeSkill},
		{ 0, 0 }
};

LuaCreatureObject::LuaCreatureObject(lua_State *L) : LuaSceneObject(L) {
	realObject = static_cast<CreatureObject*>(lua_touserdata(L, 1));
}

LuaCreatureObject::~LuaCreatureObject(){
}

int LuaCreatureObject::_setObject(lua_State* L) {
	realObject = static_cast<CreatureObject*>(lua_touserdata(L, -1));

	return 0;
}

int LuaCreatureObject::setCustomObjectName(lua_State* L) {
	String value = lua_tostring(L, -1);
	realObject->setCustomObjectName(value, true);

	return 0;
}

int LuaCreatureObject::setState(lua_State* L) {
	uint32 state = (uint32) lua_tonumber(L, -1);

	realObject->setState(state, true);

	return 0;
}

int LuaCreatureObject::setPosture(lua_State* L) {
	uint32 posture = (uint32) lua_tonumber(L, -1);

	realObject->setPosture(posture, true);

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

int LuaCreatureObject::getScreenPlayState(lua_State *L) {
	String play = lua_tostring(L, -1);
	uint64 state = realObject->getScreenPlayState(play);

	lua_pushnumber(L, state);

	return 1;
}

int LuaCreatureObject::sendNewbieTutorialEnableHudElement(lua_State* L) {
	String ui = lua_tostring(L, -2);
	int enable = lua_tonumber(L, -1);

	realObject->sendNewbieTutorialEnableHudElement(ui, enable);

	return 0;
}

int LuaCreatureObject::hasSkill(lua_State* L) {
	String value = lua_tostring(L, -1);

	bool check = realObject->hasSkill(value);
	lua_pushnumber(L, check);
	return 1;
}

int LuaCreatureObject::removeSkill(lua_State* L) {
	String value = lua_tostring(L, -1);

	realObject->removeSkill(value, true);
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

int LuaCreatureObject::clearCombatState(lua_State* L) {
	bool clearDef = lua_tonumber(L, -1);

	realObject->clearCombatState(clearDef);

	return 0;
}

int LuaCreatureObject::getHAM(lua_State* L) {
	int type = lua_tonumber(L, -1);

	int value = realObject->getHAM(type);

	lua_pushnumber(L, value);

	return 1;
}

int LuaCreatureObject::getMaxHAM(lua_State* L) {
	int type = lua_tonumber(L, -1);

	int value = realObject->getMaxHAM(type);

	lua_pushnumber(L, value);

	return 1;
}

int LuaCreatureObject::inflictDamage(lua_State* L) {
 //int inflictDamage(TangibleObject attacker, int damageType, int damage, boolean destroy, boolean notifyClient = true);
	int destroy = lua_tonumber(L, -1);
	int damage = lua_tonumber(L, -2);
	int damageType = lua_tonumber(L, -3);
	TangibleObject* attacker = (TangibleObject*) lua_touserdata(L, -4);

	realObject->inflictDamage(attacker, damageType, damage, destroy);

	return 0;
}

int LuaCreatureObject::playEffect(lua_State* L) {
	//public native void playEffect(final string file, final string aux);

	String aux = lua_tostring(L, -1);
	String file = lua_tostring(L, -2);

	realObject->playEffect(file, aux);

	return 0;
}

int LuaCreatureObject::getBankCredits(lua_State *L) {
	lua_pushnumber(L, realObject->getBankCredits());

	return 1; // we return the number of vars pushed to the L stack
}
