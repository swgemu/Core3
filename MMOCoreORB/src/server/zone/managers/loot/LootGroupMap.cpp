/*
 * LootGroupMap.cpp
 *
 *  Created on: Jun 24, 2011
 *      Author: kyle
 */

#include "LootGroupMap.h"

Lua* LootGroupMap::lua = NULL;

LootGroupMap::LootGroupMap() {
	// TODO Auto-generated constructor stub
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
	lua_register(lua->getLuaState(), "includeFile", includeFile);
}

void LootGroupMap::registerGlobals() {

}

int LootGroupMap::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);

	Lua::runFile("scripts/loot/" + filename, L);

	return 0;
}

int LootGroupMap::addLootGroupTemplate(lua_State* L) {
	return 0;
}
