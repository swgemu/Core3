/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "JediManager.h"
#include "server/zone/managers/director/DirectorManager.h"

JediManager::JediManager() : Logger("JediManager") {
	jediProgressionType = NOJEDIPROGRESSION;
	setJediManagerName("JediManager");
}

JediManager::~JediManager() {

}

const String& JediManager::getJediManagerName() {
	ReadLocker locker(this);

	return jediManagerName;
}

int JediManager::getJediProgressionType() {
	ReadLocker locker(this);

	return jediProgressionType;
}

void JediManager::setJediManagerName(const String& name) {
	Locker writeLock(this);

	jediManagerName = name;
}

void JediManager::setupLuaValues(Lua* luaEngine) {
	luaEngine->setGlobalInt("NOJEDIPROGRESSION", JediManager::NOJEDIPROGRESSION);
	luaEngine->setGlobalInt("HOLOGRINDJEDIPROGRESSION", JediManager::HOLOGRINDJEDIPROGRESSION);
	luaEngine->setGlobalInt("VILLAGEJEDIPROGRESSION", JediManager::VILLAGEJEDIPROGRESSION);
	luaEngine->setGlobalInt("CUSTOMJEDIPROGRESSION", JediManager::CUSTOMJEDIPROGRESSION);
	luaEngine->setGlobalInt("ITEMHOLOCRON", JediManager::ITEMHOLOCRON);
	luaEngine->setGlobalInt("ITEMWAYPOINTDATAPAD", JediManager::ITEMWAYPOINTDATAPAD);
	luaEngine->setGlobalInt("ITEMTHEATERDATAPAD", JediManager::ITEMTHEATERDATAPAD);
}

void JediManager::loadConfiguration(Lua* luaEngine) {
	setupLuaValues(luaEngine);

	luaEngine->runFile("scripts/managers/jedi/jedi_manager.lua");

	jediProgressionType = luaEngine->getGlobalInt(String("jediProgressionType"));

	switch (jediProgressionType) {
	case HOLOGRINDJEDIPROGRESSION:
		luaEngine->runFile("scripts/managers/jedi/hologrind_jedi_manager.lua");
		break;
	case VILLAGEJEDIPROGRESSION:
		luaEngine->runFile("scripts/managers/jedi/village_jedi_manager.lua");
		break;
	case CUSTOMJEDIPROGRESSION:
		luaEngine->runFile(luaEngine->getGlobalString(String("customJediProgressionFile")));
		break;
	default:
		break;
	}

	setJediManagerName(luaEngine->getGlobalString(String("jediManagerName")));

	info("Loaded.");
}

void JediManager::onPlayerCreated(CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	Reference<LuaFunction*> luaOnPlayerCreated = lua->createFunction(getJediManagerName(), "onPlayerCreated", 0);
	*luaOnPlayerCreated << creature;

	luaOnPlayerCreated->callFunction();
}

void JediManager::onPlayerLoggedIn(CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	Reference<LuaFunction*> luaOnPlayerLoggedIn = lua->createFunction(getJediManagerName(), "onPlayerLoggedIn", 0);
	*luaOnPlayerLoggedIn << creature;

	luaOnPlayerLoggedIn->callFunction();
}

void JediManager::onPlayerLoggedOut(CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	Reference<LuaFunction*> luaOnPlayerLoggedOut = lua->createFunction(getJediManagerName(), "onPlayerLoggedOut", 0);
	*luaOnPlayerLoggedOut << creature;

	luaOnPlayerLoggedOut->callFunction();
}

void JediManager::checkForceStatusCommand(CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	Reference<LuaFunction*> luaCheckForceStatusCommand = lua->createFunction(getJediManagerName(), "checkForceStatusCommand", 0);
	*luaCheckForceStatusCommand << creature;

	luaCheckForceStatusCommand->callFunction();
}

void JediManager::useItem(SceneObject* item, const int itemType, CreatureObject* creature) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	Reference<LuaFunction*> luaUseItem = lua->createFunction(getJediManagerName(), "useItem", 0);
	*luaUseItem << item;
	*luaUseItem << itemType;
	*luaUseItem << creature;

	luaUseItem->callFunction();
}

bool JediManager::canLearnSkill(CreatureObject* creature, const String& skillName) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	Reference<LuaFunction*> luaStartTask = lua->createFunction(getJediManagerName(), "canLearnSkill", 1);
	*luaStartTask << creature;
	*luaStartTask << skillName;

	lua_State* L = luaStartTask->callFunction();

	bool result = lua_toboolean(L, -1);

	lua_pop(L, 1);

	return result;
}

bool JediManager::canSurrenderSkill(CreatureObject* creature, const String& skillName) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	Reference<LuaFunction*> luaStartTask = lua->createFunction(getJediManagerName(), "canSurrenderSkill", 1);
	*luaStartTask << creature;
	*luaStartTask << skillName;

	lua_State* L = luaStartTask->callFunction();

	bool result = lua_toboolean(L, -1);

	lua_pop(L, 1);

	return result;
}

void JediManager::onFSTreeCompleted(CreatureObject* creature, const String& branch) {
	Lua* lua = DirectorManager::instance()->getLuaInstance();
	Reference<LuaFunction*> luaStartTask = lua->createFunction(getJediManagerName(), "onFSTreeCompleted", 0);
	*luaStartTask << creature;
	*luaStartTask << branch;

	luaStartTask->callFunction();
}
