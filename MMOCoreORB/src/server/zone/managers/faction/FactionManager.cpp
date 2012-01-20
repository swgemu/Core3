/*
 * FactionManager.cpp
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#include "FactionManager.h"
#include "FactionMap.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/templates/TemplateManager.h"

FactionManager::FactionManager() {
	setLoggingName("FactionManager");
	setGlobalLogging(false);
	setLogging(false);
}

void FactionManager::loadData() {
	loadLuaConfig();
	loadFactionRanks();
}

void FactionManager::loadFactionRanks() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/faction/rank.iff");

	if (iffStream == NULL) {
		warning("Faction ranks could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	factionRanks.readObject(&dtiff);

	info("loaded " + String::valueOf(factionRanks.getCount()) + " ranks", true);
}

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

void FactionManager::awardFactionStanding(CreatureObject* player, const String& factionName) {
	if (player == NULL)
		return;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (!factionMap.contains(factionName))
		return;

	float lose = floor((float)75); //TODO: Find the equation for this.
	float gain = floor((float)lose / 2); //you gain half of what you lose

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


void FactionManager::awardPvpFactionPoints(TangibleObject* killer, CreatureObject* destructedObject) {
	if (killer->isPlayerCreature() && destructedObject->isPlayerCreature()) {
		ManagedReference<PlayerObject*> ghost = destructedObject->getPlayerObject();
		CreatureObject* killerCreature = cast<CreatureObject*>(killer);
		ManagedReference<PlayerObject*> killedGhost = destructedObject->getPlayerObject();

		if (killer->getFaction() != destructedObject->getFaction()) {
			if (killer->isRebel() && destructedObject->isImperial()) {
				killedGhost->increaseFactionStanding("rebel", 75);
				killedGhost->decreaseFactionStanding("imperial", 75);

				ghost->decreaseFactionStanding("imperial", 75); //TODO: find formulas
			} else if (killer->isImperial() && destructedObject->isRebel()) {
				killedGhost->increaseFactionStanding("imperial", 75);
				killedGhost->decreaseFactionStanding("rebel", 75);

				ghost->decreaseFactionStanding("rebel", 75);
			}
		}
	} else if (destructedObject->isPlayerCreature()) {
		ManagedReference<PlayerObject*> ghost = destructedObject->getPlayerObject();

		if (killer->getFaction() != destructedObject->getFaction()) {
			if (killer->isRebel() && destructedObject->isImperial()) {
				ghost->decreaseFactionStanding("imperial", 75); //TODO: find formulas
			} else if (killer->isImperial() && destructedObject->isRebel()) {
				ghost->decreaseFactionStanding("rebel", 75);
			}
		}
	}
}

String FactionManager::getRankName(int idx) {
	if (idx >= factionRanks.getCount())
		return "";

	return factionRanks.getRank(idx).getName();
}

int FactionManager::getRankCost(int rank) {
	if (rank >= factionRanks.getCount())
		return -1;

	return factionRanks.getRank(rank).getCost();
}

int FactionManager::getRankDelegateRatioFrom(int rank) {
	if (rank >= factionRanks.getCount())
		return -1;

	return factionRanks.getRank(rank).getDelegateRatioFrom();
}

int FactionManager::getRankDelegateRatioTo(int rank) {
	if (rank >= factionRanks.getCount())
		return -1;

	return factionRanks.getRank(rank).getDelegateRatioTo();
}

int FactionManager::getFactionPointsCap(int rank) {
	if (rank >= factionRanks.getCount())
		return -1;

	return MAX(1000, getRankCost(rank) * 20);
}
