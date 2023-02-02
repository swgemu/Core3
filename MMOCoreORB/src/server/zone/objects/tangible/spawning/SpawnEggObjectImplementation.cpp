/*
 * SpawnEggObjectImplementation.cpp
 *
 *	1/30/23
 *	Author: H
 */

#include "server/zone/objects/tangible/spawning/SpawnEggObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

int SpawnEggObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (player == nullptr)
		return 0;

	return 0;
}

void SpawnEggObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player){
	if (player == nullptr)
		return;

	if (player->isPlayerCreature()) {
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr && ghost->isPrivileged()) {
			StringBuffer msg;
			msg << (isActive() ? "Spawner Active" : "Spawner Inactive") << "\n";
			msg << "Interest Area Name: " << areaName << "\n";
			msg << "Spawn Name: " << spawnName << "\n";
			msg << "Respawn Time: " << respawnTime << " seconds\n";
			msg << "Respawn Count: " << respawnCount << "\n";
			msg << getWorldPosition().toString();

			player->sendSystemMessage(msg.toString());
		}
	}
}