/*
 * LootGroupMap.cpp
 *
 *  Created on: Jun 24, 2011
 *      Author: kyle
 */

#include "LootGroupMap.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/templates/LootItemTemplate.h"

Lua* LootGroupMap::lua = NULL;

LootGroupMap::LootGroupMap() {
	lua = NULL;
}

LootGroupMap::~LootGroupMap() {
	// TODO Auto-generated destructor stub

	delete lua;
	lua = NULL;
}

void LootGroupMap::initialize() {
	lua = new Lua();
	lua->init();

	registerFunctions();
	registerGlobals();

	lua->runFile("scripts/loot/lootgroup.lua");
	lua->runFile("scripts/loot/serverobjects.lua");
}

void LootGroupMap::registerFunctions() {
	//lua generic
	lua_register(lua->getLuaState(), "addLootGroupTemplate", addLootGroupTemplate);
	lua_register(lua->getLuaState(), "addLootItemTemplate", addLootItemTemplate);
	lua_register(lua->getLuaState(), "includeFile", includeFile);
}

void LootGroupMap::registerGlobals() {
	//AMAZINGSUCCESS = 0 GREATSUCCESS = 1 GOODSUCCESS = 2 MODERATESUCCESS = 3 SUCCESS = 4 MARGINALSUCCESS = 5 OK = 6 BARELYSUCCESSFUL = 7 CRITICALFAILURE = 8

	lua->setGlobalInt("AMAZINGSUCCESS", CraftingManager::AMAZINGSUCCESS);
	lua->setGlobalInt("GOODSUCCESS", CraftingManager::GOODSUCCESS);
	lua->setGlobalInt("MODERATESUCCESS", CraftingManager::MODERATESUCCESS);
	lua->setGlobalInt("OK", CraftingManager::OK);
	lua->setGlobalInt("CRITICALFAILURE", CraftingManager::CRITICALFAILURE);
}

int LootGroupMap::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);

	Lua::runFile("scripts/loot/" + filename, L);

	return 0;
}

int LootGroupMap::addLootGroupTemplate(lua_State* L) {
	String ascii = lua_tostring(L, -2);
	LuaObject obj(L);

	LuaObject luaItems = obj.getObjectField("lootItems");

	Reference<LootGroup*> group = new LootGroup();

	for (int i = 1; i <= luaItems.getTableSize(); ++i) {
		group->add(luaItems.getStringAt(i));
	}

	luaItems.pop();

	if (instance()->put(ascii, group) != NULL) {
		Logger::console.warning("duplicate loot group template with name " + ascii);
	}

	//printf("added loot group template\n");

	return 0;
}

int LootGroupMap::addLootItemTemplate(lua_State* L) {
	String ascii = lua_tostring(L, -2);
	LuaObject obj(L);

	Reference<LootItemTemplate*> item = new LootItemTemplate(ascii);
	item->readObject(&obj);

	if (instance()->lootItemMap.put(ascii, item) != NULL)
		Logger::console.warning("duplicate loot item template with name " + ascii);

	//printf("added loot item template\n");

	return 0;
}
