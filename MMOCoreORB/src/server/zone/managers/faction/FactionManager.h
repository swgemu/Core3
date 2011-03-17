/*
 * FactionManager.h
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#ifndef FACTIONMANAGER_H_
#define FACTIONMANAGER_H_

#include "engine/engine.h"
#include "FactionRelationshipMap.h"
#include "server/zone/objects/player/PlayerCreature.h"

class FactionRelationshipMap;

class FactionManager : public Singleton<FactionManager>, public Logger {
	FactionRelationshipMap factionRelationshipMap;

public:
	FactionManager() {
		setLoggingName("FactionManager");
		setGlobalLogging(false);
		setLogging(false);
	}

	/**
	 * Loads faction configuration information from the faction manager lua file: managers/faction_manager.lua
	 * Sets up faction relationships
	 */
	void loadLuaConfig();

	/**
	 * Lua Interface function that adds a faction relationship to the FactionRelationshipMap.
	 * @param L The Lua State containing the data.
	 */
	static int addFactionRelationship(lua_State* L);

	/**
	 * Awards points to the player based on the faction they killed.
	 * @pre: player locked
	 * @post: player locked
	 * @param player The player receiving the faction points for the kill.
	 * @param faction The string key of the faction that was killed.
	 */
	void awardFactionPoints(PlayerCreature* player, const String& faction);

	/**
	 * Gets a list of enemy factions to the faction passed to the method.
	 * @param faction The faction to check for enemies.
	 */
	SortedVector<String> getEnemyFactions(const String& faction);

	/**
	 * Gets a list of ally factions to the faction passed to the method.
	 * @param faction The faction to check for enemies.
	 */
	SortedVector<String> getAllyFactions(const String& faction);

	FactionRelationshipMap* getFactionRelationshipMap();
};

#endif /* FACTIONMANAGER_H_ */
