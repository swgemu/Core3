/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VISIBILITYMANAGER_H_
#define VISIBILITYMANAGER_H_

#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace managers {
namespace visibility {

/**
 * Visibility manager that handles visibility and listing on bounty hunter terminals.
 */
class VisibilityManager : public Singleton<VisibilityManager>, public Logger, public Object {

	/**
	 * Any player with a visibility greater than or equal to this amount will be
	 * available on the bounty hunter mission terminal as a player bounty.
	 */

	float terminalVisThreshold;

	/**
	 * If a players visibility falls below this value they will be removed from the BH terminals
	 */
	float falloffThreshold;

	/**
	 * This is the maximum visibility that can be gained
	 */
	float maxVisibility;



	/**
	 * Number of days before complete visibility decay
	 */
	unsigned int totalDecayTimeInDays;

	/**
	 * Number of seconds before rescheduling the decay event. Must be SHORTER than 1 day
	 */
	unsigned int visDecayTickRate;

	/**
	 * Amount of visibility to decay per tick
	 */
	float visDecayPerTick;

	/**
	 * Jedi PVP rating divisor
	 */
	float pvpRatingDivisor;

	/**
	 * Rebel faction string.
	 */
	static const String factionStringRebel;

	/**
	 * Imperial faction string.
	 */
	static const String factionStringImperial;

	/**
	 * Rebel faction value.
	 */
	static const unsigned int factionRebel;

	/**
	 * Imperial faction value.
	 */
	static const unsigned int factionImperial;

	/**
	 * Visibility list that contains all currently online players with visibility.
	 */
	VectorMap<uint64, ManagedReference<CreatureObject*> > visibilityList;

	/**
	 * Mutex for the visibilityList.
	 */
	Mutex visibilityListLock;

	/**
	 * Calculate/generate a reward for the player bounty.
	 * @param creature the jedi's player creature object.
	 * @return calculated/generated reward.
	 */
	int calculateReward(CreatureObject* creature);

	/**
	 * Calculates the visibility increase for the player depending on the number
	 * of players and NPC's within 32 m.
	 * @param creature the player.
	 * @param visibilityIncrease base increase for the action.
	 */
	float calculateVisibilityIncrease(CreatureObject* creature);

	/**
	 * Decrease visibility for a player. The player is removed from the visibility list
	 * if visibility goes beneath the listing level.
	 * @param creature the player to decrease the visibility for.
	 */
	void decreaseVisibility(CreatureObject* creature);

public:

	enum { // default visibility modifiers if value does not exist in LUA
		SABERVISMOD = 10, // equipping saber cost
		COMBATVISMOD = 25, // Combat action or force power cost
		BUFFVISMOD = 10 // jedi self buff cost
	};

	/**
	 * Constructor.
	 */
	VisibilityManager();

	float getTerminalVisThreshold();

	/**
	 * Load lua configuration for visibility variables
	 */
	void loadConfiguration();

	/**
	 * Add player to the visibility list if he/she still has visibility.
	 * @param creature the player to add.
	 */
	void addToVisibilityList(CreatureObject* creature);

	/**
	 * Remove player from the visibility list.
	 * @param creature the player to remove.
	 */
	void removeFromVisibilityList(CreatureObject* creature);

	/**
	 * Increase visibility for a player. The player is added to the visibility list
	 * if not already in the list.
	 * @param creature the player to increase the visibility for.
	 */
	void increaseVisibility(CreatureObject* creature, int visibilityMultiplier);

	/**
	 * Clear the visibility for a player and remove him/her from the visibility
	 * list. Should be used when a player is killed from a bounty hunter with
	 * a mission for the player.
	 * @param creature the player to clear the visibility for.
	 */
	void clearVisibility(CreatureObject* creature);

	/**
	 * Iterates through all currently online players and decays their visibility.
	 */
	void performVisiblityDecay();

	int getPvpRatingDivisor() {
		return pvpRatingDivisor;
	}

	unsigned int getVisDecayTickRate() {
		return visDecayTickRate;
	}
};

}
}
}
}

using namespace server::zone::managers::visibility;

#endif /* VISIBILITYMANAGER_H_ */
