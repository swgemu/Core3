/*
 * ShuttleInstallationImplementation.cpp
 *
 *  Created on: 31/07/2010
 *      Author: victor
 */

#include "ShuttleInstallation.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

bool ShuttleInstallationImplementation::checkRequisitesForPlacement(PlayerCreature* player) {
	/*
	ManagedReference<ActiveArea*> playerArea = player->getActiveRegion();

	//TODO: Check to make sure the player is the mayor of the city.
	if (playerArea == NULL || !playerArea->isRegion()) {
		player->sendSystemMessage("@player_structure:cant_place_civic"); //This structure must be placed within the borders of the city in which you are mayor.
		return false;
	}
	*/

	/*
	Region* region = (Region*) playerArea.get();

	if (region->getShuttle() != NULL) {
		player->sendSystemMessage("@player_structure:cant_place_unique"); //This city can only support a single structure of this type.
		return false;
	}
	*/

	return true;
}
