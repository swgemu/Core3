/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef VISIBILITYMANAGER_H_
#define VISIBILITYMANAGER_H_

#include "engine/engine.h"
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
	static const int TERMINALVISIBILITYLIMIT = 24;

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
	 * Add the player to the bounty list.
	 * @param creature the player to add.
	 * @param reward the reward for the player bounty.
	 */
	void addPlayerToBountyList(CreatureObject* creature, int reward);

	/**
	 * Remove the player to the bounty list.
	 * @param creature the player to remove.
	 */
	void removePlayerFromBountyList(CreatureObject* creature);

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

	/**
	 * Constructor.
	 */
	VisibilityManager();

	/**
	 * Login a player and add it to the visibility list if he/she still has visibility.
	 * @param creature the player to login.
	 */
	void login(CreatureObject* creature);

	/**
	 * Logout a player and remove him/her from the visibility list.
	 * @param creature the player to logout.
	 */
	void logout(CreatureObject* creature);

	/**
	 * Increase visibility for a player. The player is added to the visibility list
	 * if not already in the list.
	 * @param creature the player to increase the visibility for.
	 */
	void increaseVisibility(CreatureObject* creature);

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
};

}
}
}
}

using namespace server::zone::managers::visibility;

#endif /* VISIBILITYMANAGER_H_ */
