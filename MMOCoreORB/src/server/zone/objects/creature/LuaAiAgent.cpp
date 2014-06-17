/*
 * LuaAiAgent.cpp
 *
 *  Created on: 21/01/2012
 *      Author: victor
 */

#include "LuaAiAgent.h"

#include <engine/core/ManagedReference.h>
#include <engine/lua/Luna.h>
#include <lua.h>
#include <stddef.h>
#include <system/lang/ref/Reference.h>
#include <system/lang/String.h>
#include <system/platform.h>

#include "../../../../autogen/server/chat/ChatManager.h"
#include "../../../../autogen/server/zone/ZoneServer.h"
#include "../../../chat/StringIdChatParameter.h"
#include "../../../ServerCore.h"

//#include "server/zone/objects/creature/AiAgent.h"

const char LuaAiAgent::className[] = "LuaAiAgent";

Luna<LuaAiAgent>::RegType LuaAiAgent::Register[] = {
		{ "_setObject", &LuaAiAgent::_setObject },
		{ "_getObject", &LuaAiAgent::_getObject },
		{ "setFollowObject", &LuaAiAgent::setFollowObject },
		{ "getFollowObject", &LuaAiAgent::getFollowObject },
		{ "findNextPosition", &LuaAiAgent::findNextPosition },
		{ "getMaxDistance", &LuaAiAgent::getMaxDistance },
		{ "generatePatrol", &LuaAiAgent::generatePatrol },
		{ "setDestination", &LuaAiAgent::setDestination },
		{ "completeMove", &LuaAiAgent::completeMove },
		{ "getCurrentSpeed", &LuaAiAgent::getCurrentSpeed },
		{ "setCurrentSpeed", &LuaAiAgent::setCurrentSpeed },
		{ "setBehaviorStatus", &LuaAiAgent::setBehaviorStatus },
		{ "getBehaviorStatus", &LuaAiAgent::getBehaviorStatus },
		{ "info", &LuaAiAgent::info },
		{ "spatialChat", &LuaAiAgent::spatialChat },
		{ 0, 0 }
};


LuaAiAgent::LuaAiAgent(lua_State *L) : LuaCreatureObject(L) {
	realObject = static_cast<AiAgent*>(lua_touserdata(L, 1));
}

LuaAiAgent::~LuaAiAgent(){
}

int LuaAiAgent::_setObject(lua_State* L) {
	realObject = static_cast<AiAgent*>(lua_touserdata(L, -1));

	return 0;
}

int LuaAiAgent::_getObject(lua_State* L) {
	lua_pushlightuserdata(L, realObject.get());

	return 1;
}

int LuaAiAgent::setFollowObject(lua_State* L) {
	SceneObject* obj = (SceneObject*) lua_touserdata(L, -1);

	realObject->setFollowObject(obj);

	return 0;
}

int LuaAiAgent::getFollowObject(lua_State* L) {
	lua_pushlightuserdata(L, realObject->getFollowObject());

	return 1;
}

/**
 * @param takes a float maxDistance argument
 * @return bool to lua depending on if a new position was found or not
 */
int LuaAiAgent::findNextPosition(lua_State* L) {
	uint16 maxDistance = lua_tonumber(L, -1);

	bool found = realObject->findNextPosition(maxDistance);

	lua_pushboolean(L, found);

	return 1;
}

int LuaAiAgent::getMaxDistance(lua_State* L) {
	float maxDistance = realObject->getMaxDistance();

	lua_pushnumber(L, maxDistance);

	return 1;
}

int LuaAiAgent::generatePatrol(lua_State* L) {
	int num = lua_tointeger(L, -1);
	float dist = lua_tonumber(L, -2);

	bool retVal = realObject->generatePatrol(num, dist);

	lua_pushboolean(L, retVal);

	return 1;
}

int LuaAiAgent::setDestination(lua_State* L) {
	int retVal = realObject->setDestination();

	lua_pushinteger(L, retVal);

	return 1;
}

int LuaAiAgent::completeMove(lua_State* L) {
	bool retVal = realObject->completeMove();

	lua_pushboolean(L, retVal);

	return 1;
}

int LuaAiAgent::getCurrentSpeed(lua_State* L) {
	float currentSpeed = realObject->getCurrentSpeed();

	lua_pushnumber(L, currentSpeed);

	return 1;
}

int LuaAiAgent::setCurrentSpeed(lua_State* L) {
	float currentSpeed = lua_tonumber(L, -1);

	realObject->setCurrentSpeed(currentSpeed);

	return 0;
}

int LuaAiAgent::setBehaviorStatus(lua_State* L) {
	uint8 status = (uint8) lua_tointeger(L, -1);

	realObject->setBehaviorStatus(status);

	return 0;
}

int LuaAiAgent::getBehaviorStatus(lua_State* L) {
	lua_pushnumber(L, realObject->getBehaviorStatus());

	return 1;
}

int LuaAiAgent::info(lua_State* L) {
	String msg = lua_tostring(L, -1);

	realObject->info(msg, true);

	return 0;
}

int LuaAiAgent::spatialChat(lua_State* L) {
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	if (zoneServer == NULL)
		return 0;

	ChatManager* chatManager = zoneServer->getChatManager();

	if (lua_islightuserdata(L, -1)) {
		StringIdChatParameter* message = (StringIdChatParameter*)lua_touserdata(L, -1);

		if (realObject != NULL && message != NULL) {
			chatManager->broadcastMessage(realObject, *message, 0, 0, 0);
		}
	} else {
		String message = lua_tostring(L, -1);

		if (realObject != NULL) {
			chatManager->broadcastMessage(realObject, message, 0, 0, 0);
		}
	}

	return 0;
}

