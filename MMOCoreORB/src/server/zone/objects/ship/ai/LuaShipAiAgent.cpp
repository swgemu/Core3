/*
 * LuaShipAiAgent.cpp
 *
 *  Created on: 24/10/30
 *  Author: Hakry
 */

#include "LuaShipAiAgent.h"

#include <engine/core/ManagedReference.h>
#include <system/lang/ref/Reference.h>
#include <system/lang/String.h>

#include "templates/params/ship/ShipFlag.h"
#include "server/chat/ChatManager.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/ServerCore.h"

#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/area/ActiveArea.h"

const char LuaShipAiAgent::className[] = "LuaShipAiAgent";

Luna<LuaShipAiAgent>::RegType LuaShipAiAgent::Register[] = {
	{ "_setObject", &LuaShipAiAgent::_setObject },
	{ "_getObject", &LuaSceneObject::_getObject },
	{ "setShipAiTemplate", &LuaShipAiAgent::setShipAiTemplate },
	{ "setGuardPatrol", &LuaShipAiAgent::setGuardPatrol },
	{ "setRandomPatrol", &LuaShipAiAgent::setRandomPatrol },
	{ "setFixedPatrol", &LuaShipAiAgent::setFixedPatrol },
	{ "setSquadronPatrol", &LuaShipAiAgent::setSquadronPatrol },
	{ "setSquadronFollow", &LuaShipAiAgent::setSquadronFollow },
	{ "setDespawnOnNoPlayerInRange", &LuaShipAiAgent::setDespawnOnNoPlayerInRange },
	{ "setMinimumGuardPatrol", &LuaShipAiAgent::setMinimumGuardPatrol },
	{ "setMaximumGuardPatrol", &LuaShipAiAgent::setMaximumGuardPatrol },
	{ "addFixedPatrolPoint", &LuaShipAiAgent::addFixedPatrolPoint },
	{ 0, 0 }
};

LuaShipAiAgent::LuaShipAiAgent(lua_State *L) : LuaShipObject(L) {
#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<ShipAiAgent*>(_getRealSceneObject());

	E3_ASSERT(!_getRealSceneObject() || realObject != nullptr);
#else
	realObject = static_cast<AiAgent*>(lua_touserdata(L, 1));
#endif
}

LuaShipAiAgent::~LuaShipAiAgent(){
}

int LuaShipAiAgent::_setObject(lua_State* L) {
	LuaShipObject::_setObject(L);

#ifdef DYNAMIC_CAST_LUAOBJECTS
	auto obj = dynamic_cast<ShipAiAgent*>(_getRealSceneObject());

	if (realObject != obj)
		realObject = obj;

	E3_ASSERT(!_getRealSceneObject() || realObject != nullptr);
#else
	auto obj = static_cast<AiAgent*>(lua_touserdata(L, -1));

	if (realObject != obj)
		realObject = obj;
#endif

	return 0;
}

int LuaShipAiAgent::setShipAiTemplate(lua_State* L) {
	Locker locker(realObject);
	realObject->setShipAiTemplate();

	return 0;
}

int LuaShipAiAgent::setGuardPatrol(lua_State* L) {
	Locker locker(realObject);

	realObject->addShipFlag(ShipFlag::GUARD_PATROL);
	realObject->setShipAiTemplate();

	return 0;
}

int LuaShipAiAgent::setRandomPatrol(lua_State* L) {
	Locker locker(realObject);

	realObject->addShipFlag(ShipFlag::RANDOM_PATROL);
	realObject->setShipAiTemplate();

	return 0;
}

int LuaShipAiAgent::setFixedPatrol(lua_State* L) {
	Locker locker(realObject);

	realObject->addShipFlag(ShipFlag::FIXED_PATROL);
	realObject->setShipAiTemplate();

	return 0;
}

int LuaShipAiAgent::setSquadronPatrol(lua_State* L) {
	Locker locker(realObject);

	realObject->addShipFlag(ShipFlag::SQUADRON_PATROL);
	realObject->setShipAiTemplate();

	return 0;
}

int LuaShipAiAgent::setSquadronFollow(lua_State* L) {
	Locker locker(realObject);

	realObject->addShipFlag(ShipFlag::SQUADRON_FOLLOW);
	realObject->setShipAiTemplate();

	return 0;
}

int LuaShipAiAgent::setDespawnOnNoPlayerInRange(lua_State* L) {
	bool val = lua_toboolean(L, -1);

	Locker locker(realObject);

	realObject->setDespawnOnNoPlayerInRange(val);

	return 0;
}

int LuaShipAiAgent::setMinimumGuardPatrol(lua_State* L) {
	float minDist = lua_tonumber(L, -1);

	Locker locker(realObject);

	realObject->setMinimumGuardPatrol(minDist);

	return 0;
}

int LuaShipAiAgent::setMaximumGuardPatrol(lua_State* L) {
	float maxDist = lua_tonumber(L, -1);

	Locker locker(realObject);

	realObject->setMaximumGuardPatrol(maxDist);

	return 0;
}

int LuaShipAiAgent::addFixedPatrolPoint(lua_State* L) {
	String name = lua_tostring(L, -1);

	if (name.isEmpty()) {
		return 0;
	}

	Locker locker(realObject);

	realObject->addFixedPatrolPoint(name.hashCode());

	return 0;
}
