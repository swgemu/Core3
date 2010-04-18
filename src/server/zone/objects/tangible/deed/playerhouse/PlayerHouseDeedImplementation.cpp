/*
 * PlayerHouseDeedImplementation.cpp
 *
 *  Created on: Apr 18, 2010
 *      Author: crush
 */

#include "PlayerHouseDeed.h"
#include "server/zone/objects/player/PlayerCreature.h"

void PlayerHouseDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("PlayerHouseDeed");
}

int PlayerHouseDeedImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID != 20) // not use object
		return 1;

	player->sendSystemMessage("Entering placement mode...");

	return 0;
}
