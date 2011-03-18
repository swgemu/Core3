/*
 * FactionManager.cpp
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#include "FactionManager.h"
#include "FactionMap.h"
#include "server/zone/objects/player/PlayerObject.h"

void FactionManager::loadLuaConfig() {
	info("Loading config file.", true);

	Lua* lua = new Lua();
	lua->init();

	lua_register(lua->getLuaState(), "addFaction", addFaction);

	//Load the faction manager lua file.
	lua->runFile("scripts/managers/faction_manager.lua");

	delete lua;
	lua = NULL;
}

int FactionManager::addFaction(lua_State* L) {
	String allies = Lua::getStringParameter(L);
	String enemies = Lua::getStringParameter(L);
	String factionName = Lua::getStringParameter(L);

	FactionManager* factionManager = FactionManager::instance();

	FactionMap* factionMap = factionManager->getFactionMap();

	if (factionMap == NULL)
		return 1;

	Faction faction(factionName);
	faction.parseEnemiesFromList(enemies);
	faction.parseAlliesFromList(allies);

	factionMap->addFaction(faction);

	return 0;
}

FactionMap* FactionManager::getFactionMap() {
	return &factionMap;
}

void FactionManager::awardFactionStanding(PlayerCreature* player, const String& factionName) {
	if (player == NULL)
		return;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (!factionMap.contains(factionName))
		return;

	float lose = floor(130); //TODO: Find the equation for this.
	float gain = floor(lose / 2); //you gain half of what you lose

	Faction faction = factionMap.get(factionName);
	SortedVector<String>* enemies = faction.getEnemies();
	SortedVector<String>* allies = faction.getAllies();

	ghost->decreaseFactionStanding(factionName, lose);

	//Lose faction standing to allies of the creature.
	for (int i = 0; i < allies->size(); ++i) {
		String ally = allies->get(i);
		ghost->decreaseFactionStanding(ally, lose);
	}

	//Gain faction standing to enemies of the creature.
	for (int i = 0; i < enemies->size(); ++i) {
		String enemy = enemies->get(i);
		ghost->increaseFactionStanding(enemy, gain);
	}
}

void FactionManager::awardFactionPoints(TangibleObject* killer, TangibleObject* destructedObject) {
	//Temporary for testing.

	if (killer->isPlayerCreature()) {
		PlayerCreature* playerKiller = (PlayerCreature*) killer;

		ManagedReference<PlayerObject*> ghost = playerKiller->getPlayerObject();
		ghost->getFactionStandingList()->increaseRebelPoints(45);
	}

	if (destructedObject->isPlayerCreature()) {
		PlayerCreature* victim = (PlayerCreature*) destructedObject;

		ManagedReference<PlayerObject*> ghost = victim->getPlayerObject();
		ghost->getFactionStandingList()->decreaseImperialPoints(30);
	}
}
