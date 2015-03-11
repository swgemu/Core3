/*
 * LuaBehavior.cpp
 *
 *  Created on: Sep 1, 2013
 *      Author: swgemu
 */

#include "LuaBehavior.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/creature/AiMap.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "engine/engine.h"

#ifndef AI_DEBUG
#define AI_DEBUG
#endif

LuaBehavior::LuaBehavior(String name) : Object() {
	this->className = name;
}

LuaBehavior::~LuaBehavior() {
}

bool LuaBehavior::initialize() {
	// TODO (dannuic): put validity checks here without trying to access DirectorManager (would cause endless initialization loop)

	return true;
}

uint16 LuaBehavior::getType() {
	return AiMap::BEHAVIOR;
}

bool LuaBehavior::checkConditions(AiAgent* agent) {
#ifdef AI_DEBUG
	Time timer;
#endif
	// Use DirectorManager in order to have access to AiAgent
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	// TODO (dannuic): should I check for valid table here?
	//agent->info(className, true);
	LuaFunction runMethod(lua->getLuaState(), className, "checkConditions", 1);
	runMethod << agent;

	//agent->info(className + " check...", true);
	runMethod.callFunction();

	bool result = lua_toboolean(lua->getLuaState(), -1);
	lua_pop(lua->getLuaState(), 1);

#ifdef AI_DEBUG
	String key = className + "::checkConditions";
	agent->incrementLuaCall(key);
	agent->addToLuaTime(key, Time().getMikroTime() - timer.getMikroTime());
#endif

	return result;
}

void LuaBehavior::start(AiAgent* agent) {
#ifdef AI_DEBUG
	Time timer;
#endif
	// Use DirectorManager in order to have access to AiAgent
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	// TODO (dannuic): should I check for valid table here?
	LuaFunction runMethod(lua->getLuaState(), className, "start", 1);
	runMethod << agent;

	//agent->info(className + " start...", true);
	runMethod.callFunction();

	int result = lua_tointeger(lua->getLuaState(), -1);
	lua_pop(lua->getLuaState(), 1);

#ifdef AI_DEBUG
	String key = className + "::start";
	agent->incrementLuaCall(key);
	agent->addToLuaTime(key, Time().getMikroTime() - timer.getMikroTime());
#endif
}

float LuaBehavior::end(AiAgent* agent) {
#ifdef AI_DEBUG
	Time timer;
#endif
	// Use DirectorManager in order to have access to AiAgent
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	// TODO (dannuic): should I check for valid table here?
	LuaFunction runMethod(lua->getLuaState(), className, "terminate", 1);
	runMethod << agent;

	//agent->info(className + " end...", true);
	runMethod.callFunction();

	float result = lua_tonumber(lua->getLuaState(), -1);
	lua_pop(lua->getLuaState(), 1);

#ifdef AI_DEBUG
	String key = className + "::terminate";
	agent->incrementLuaCall(key);
	agent->addToLuaTime(key, Time().getMikroTime() - timer.getMikroTime());
#endif

	return result;
}

int LuaBehavior::doAction(AiAgent* agent) {
#ifdef AI_DEBUG
	Time timer;
#endif
	// Use DirectorManager in order to have access to AiAgent
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	//agent->info(className, true);
	// TODO (dannuic): should I check for valid table here?
	LuaFunction runMethod(lua->getLuaState(), className, "doAction", 1);
	runMethod << agent;

	//agent->info(className + " do...", true);
	runMethod.callFunction();

	int result = lua_tointeger(lua->getLuaState(), -1);
	lua_pop(lua->getLuaState(), 1);

#ifdef AI_DEBUG
	String key = className + "::doAction";
	agent->incrementLuaCall(key);
	agent->addToLuaTime(key, Time().getMikroTime() - timer.getMikroTime());
#endif

	return result;
}

int LuaBehavior::interrupt(AiAgent* agent, SceneObject* source, int64 msg) {
#ifdef AI_DEBUG
	Time timer;
#endif

	Lua* lua = DirectorManager::instance()->getLuaInstance();

	LuaFunction messageFunc(lua->getLuaState(), className, "interrupt", 1);
	messageFunc << agent;
	messageFunc << source; //arg1
	messageFunc << msg; //arg2

	messageFunc.callFunction();

	int result = lua_tointeger(lua->getLuaState(), -1);
	lua_pop(lua->getLuaState(), 1);

#ifdef AI_DEBUG
	String key = className;
	if (msg == 17)
		key += "::startAwarenessInterrupt";
	else if (msg == 31)
		key += "::startCombatInterrupt";

	agent->incrementLuaCall(key);
	agent->addToLuaTime(key, Time().getMikroTime() - timer.getMikroTime());
#endif

	//1 remove observer, 0 keep observer
	return result;
}

bool LuaBehavior::doAwarenessCheck(AiAgent* agent, SceneObject* target) {
#ifdef AI_DEBUG
	Time timer;
#endif

	Lua* lua = DirectorManager::instance()->getLuaInstance();
	//agent->info(className, true);
	LuaFunction messageFunc(lua->getLuaState(), className, "doAwarenessCheck", 1);
	messageFunc << agent;
	messageFunc << target; //pObject

	messageFunc.callFunction();

	bool result = lua_toboolean(lua->getLuaState(), -1);
	lua_pop(lua->getLuaState(), 1);

#ifdef AI_DEBUG
	String key = className + "::doAwarenessCheck";
	agent->incrementLuaCall(key);
	agent->addToLuaTime(key, Time().getMikroTime() - timer.getMikroTime());
#endif

	return result;
}
