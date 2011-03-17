/*
 * FactionManager.cpp
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#include "FactionManager.h"
#include "FactionRelationshipMap.h"

void FactionManager::loadLuaConfig() {
	info("Loading config file.", true);

	Lua* lua = new Lua();
	lua->init();

	lua_register(lua->getLuaState(), "addFactionRelationship", addFactionRelationship);

	//Load the faction manager lua file.
	lua->runFile("scripts/managers/faction_manager.lua");

	delete lua;
	lua = NULL;
}

int FactionManager::addFactionRelationship(lua_State* L) {
	String faction = Lua::getStringParameter(L);
	String enemies = Lua::getStringParameter(L);
	String allies = Lua::getStringParameter(L);

	FactionManager* factionManager = FactionManager::instance();
	factionManager->info("Adding faction " + faction + " with enemies " + enemies, true);

	FactionRelationshipMap* factionRelationshipMap = factionManager->getFactionRelationshipMap();

	if (factionRelationshipMap == NULL)
		return 1;

	factionRelationshipMap->addFactionRelationship(faction, enemies, allies);

	return 0;
}

FactionRelationshipMap* FactionManager::getFactionRelationshipMap() {
	return &factionRelationshipMap;
}
