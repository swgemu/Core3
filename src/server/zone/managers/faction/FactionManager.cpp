/*
 * FactionManager.cpp
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#include "FactionManager.h"
#include "FactionRelationshipMap.h"
#include "server/zone/objects/player/PlayerObject.h"

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
	String allies = Lua::getStringParameter(L);
	String enemies = Lua::getStringParameter(L);
	String faction = Lua::getStringParameter(L);

	FactionManager* factionManager = FactionManager::instance();

	FactionRelationshipMap* factionRelationshipMap = factionManager->getFactionRelationshipMap();

	if (factionRelationshipMap == NULL)
		return 1;

	factionManager->info("Faction: " + faction + " Enemies: " + enemies + " Allies: " + allies, true);

	factionRelationshipMap->addFactionRelationship(faction, enemies, allies);

	return 0;
}

FactionRelationshipMap* FactionManager::getFactionRelationshipMap() {
	return &factionRelationshipMap;
}

void FactionManager::awardFactionPoints(PlayerCreature* player, const String& faction) {
	if (player == NULL)
		return;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (!factionRelationshipMap.contains(faction))
		return;

	FactionRelationship factionRelationship = factionRelationshipMap.get(faction);
	SortedVector<String>* enemies = factionRelationship.getEnemies();
	SortedVector<String>* allies = factionRelationship.getAllies();

	int subtract = 30;
	int add = 45;

	ghost->subtractFactionPoints(faction, subtract);

	for (int i = 0; i < enemies->size(); ++i)
		ghost->addFactionPoints(enemies->get(i), add);

	for (int i = 0; i < allies->size(); ++i)
		ghost->subtractFactionPoints(allies->get(i), subtract);
}
