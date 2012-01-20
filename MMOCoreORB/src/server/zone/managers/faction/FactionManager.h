/*
 * FactionManager.h
 *
 *  Created on: Mar 17, 2011
 *      Author: crush
 */

#ifndef FACTIONMANAGER_H_
#define FACTIONMANAGER_H_

#include "engine/engine.h"
#include "FactionMap.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/templates/faction/FactionRanks.h"

class FactionMap;

class FactionManager : public Singleton<FactionManager>, public Logger, public Object {
	FactionMap factionMap;
	FactionRanks factionRanks;

public:
	FactionManager();

	/**
	 * Loads faction configuration information from the faction manager lua file: managers/faction_manager.lua
	 * Loads faction ranks from datatable
	 * Sets up faction relationships
	 */
	void loadData();

	/**
	 * Lua Interface function that adds a faction relationship to the FactionMap.
	 * @param L The Lua State containing the data.
	 */
	static int addFaction(lua_State* L);

	/**
	 * Awards points to the player based on the faction they killed.
	 * @pre: player locked
	 * @post: player locked
	 * @param player The player receiving the faction points for the kill.
	 * @param faction The string key of the faction that was killed.
	 */
	void awardFactionStanding(CreatureObject* player, const String& factionName);

	void awardPvpFactionPoints(TangibleObject* killer, CreatureObject* destructedObject);

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

	FactionMap* getFactionMap();

	String getRankName(int idx);
	int getRankCost(int rank);
	int getRankDelegateRatioFrom(int rank);
	int getRankDelegateRatioTo(int rank);
	int getFactionPointsCap(int rank);

	bool isHighestRank(int rank) {
		return rank >= factionRanks.getCount() - 1 || rank >= 15;
	}

protected:
	void loadFactionRanks();
	void loadLuaConfig();
};

#endif /* FACTIONMANAGER_H_ */
