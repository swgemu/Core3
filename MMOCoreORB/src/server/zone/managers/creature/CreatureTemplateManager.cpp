/*
 * CreatureTemplateManager.cpp
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#include "CreatureTemplateManager.h"

CreatureTemplateManager::CreatureTemplateManager() : Logger("CreatureTemplateManager") {
	/*setLogging(false);
		setGlobalLogging(true);*/
	//setLoggingName("CreatureTemplateManager");

	lua = new Lua();
	lua->init();
	hashTable.setNullValue(NULL);

	lua_register(lua->getLuaState(), "includeFile", includeFile);
	lua_register(lua->getLuaState(), "addTemplate", addTemplate);
	lua_register(lua->getLuaState(), "addWeapon", addWeapon);
	lua_register(lua->getLuaState(), "addDynamicGroup", addDynamicGroup);
	lua_register(lua->getLuaState(), "addStaticGroup", addStaticGroup);
	lua_register(lua->getLuaState(), "addConversationTemplate", addConversationTemplate);
	lua_register(lua->getLuaState(), "addLairTemplate", addLairTemplate);

	lua->setGlobalInt("NONE", CreatureFlag::NONE);
	lua->setGlobalInt("ATTACKABLE", CreatureFlag::ATTACKABLE);
	lua->setGlobalInt("AGGRESSIVE", CreatureFlag::AGGRESSIVE);
	lua->setGlobalInt("OVERT", CreatureFlag::OVERT);
	lua->setGlobalInt("TEF", CreatureFlag::TEF);
	lua->setGlobalInt("PLAYER", CreatureFlag::PLAYER);
	lua->setGlobalInt("ENEMY", CreatureFlag::ENEMY);
	lua->setGlobalInt("CHANGEFACTIONSTATUS", CreatureFlag::CHANGEFACTIONSTATUS);
	lua->setGlobalInt("BLINK_GREEN", CreatureFlag::BLINK_GREEN);

	lua->setGlobalInt("PACK", CreatureFlag::PACK);
	lua->setGlobalInt("HERD", CreatureFlag::HERD);
	lua->setGlobalInt("KILLER", CreatureFlag::KILLER);
	lua->setGlobalInt("STALKER", CreatureFlag::STALKER);
	lua->setGlobalInt("BABY", CreatureFlag::BABY);
	lua->setGlobalInt("LAIR", CreatureFlag::LAIR);

	lua->setGlobalInt("CARNIVORE", CreatureFlag::CARNIVORE);
	lua->setGlobalInt("HERBIVORE", CreatureFlag::HERBIVORE);
}

CreatureTemplateManager::~CreatureTemplateManager() {
}

void CreatureTemplateManager::loadTemplates() {
	info("loading mobile templates...", true);

	try {
		lua->runFile("scripts/mobile/creatures.lua");
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	info("done loading mobile templates", true);
}

int CreatureTemplateManager::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);

	Lua::runFile("scripts/mobile/" + filename, L);

	return 0;
}

int CreatureTemplateManager::addTemplate(lua_State* L) {
	String ascii =  lua_tostring(L, -2);
	uint32 crc = (uint32) ascii.hashCode();

	LuaObject obj(L);
	CreatureTemplate* newTemp = new CreatureTemplate();
	newTemp->setTemplateName(ascii);
	newTemp->readObject(&obj);

	CreatureTemplateManager::instance()->hashTable.put(crc, newTemp);

	return 0;
}

int CreatureTemplateManager::addConversationTemplate(lua_State* L) {
	String ascii =  lua_tostring(L, -2);
	uint32 crc = (uint32) ascii.hashCode();

	LuaObject obj(L);
	Reference<ConversationTemplate*> newTemp = new ConversationTemplate(crc);
	CreatureTemplateManager::instance()->conversations.put(crc, newTemp);

	newTemp->readObject(&obj);

	return 0;
}

int CreatureTemplateManager::addWeapon(lua_State* L) {
	String ascii = lua_tostring(L, -2);
	uint32 crc = (uint32) ascii.hashCode();

	LuaObject obj(L);
	if (obj.isValidTable()) {
		Vector<String> weps;
		for (int i = 1; i <= obj.getTableSize(); ++i)
			weps.add(obj.getStringAt(i));

		CreatureTemplateManager::instance()->weaponMap.put(crc, weps);
	}

	return 0;
}

int CreatureTemplateManager::addDynamicGroup(lua_State* L) {
	String ascii = lua_tostring(L, -2);
	uint32 crc = (uint32) ascii.hashCode();

	LuaObject obj(L);
	CreatureTemplateManager::instance()->dynamicGroupMap.put(crc, new DynamicSpawnGroup(ascii, obj));

	return 0;
}

int CreatureTemplateManager::addStaticGroup(lua_State* L) {
	String ascii = lua_tostring(L, -2);
	uint32 crc = (uint32) ascii.hashCode();

	LuaObject obj(L);
	CreatureTemplateManager::instance()->staticGroupMap.put(crc, new StaticSpawnGroup(ascii, obj));

	return 0;
}

int CreatureTemplateManager::addLairTemplate(lua_State* L) {
	String ascii = lua_tostring(L, -2);
	uint32 crc = (uint32) ascii.hashCode();

	LuaObject obj(L);

	Reference<LairTemplate*> templ = new LairTemplate(ascii);
	templ->readObject(&obj);

	CreatureTemplateManager::instance()->lairTemplates.put(crc, templ);

	return 0;
}
