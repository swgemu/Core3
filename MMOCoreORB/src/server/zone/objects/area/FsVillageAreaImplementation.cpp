/*
 * FsVillageAreaImplementation.cpp
 *
 *  Created on: 01/04/2012
 *      Author: victor
 */

#include "server/zone/objects/area/FsVillageArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/variables/PlayerQuestData.h"

void FsVillageAreaImplementation::notifyEnter(SceneObject* player) {
	ActiveAreaImplementation::notifyEnter(player);

	if (!player->isPlayerCreature()) {
		return;
	}

	float x = player->getPositionX();
	float y = player->getPositionY();

	float diffY = y - getPositionY();
	float diffX = x - getPositionX();

	float angle = atan2(diffY == 0.f ? 1 : diffY, diffX == 0.f ? 1 : diffX);

	CreatureObject* playerCreature = cast<CreatureObject*>(player);
	PlayerObject* ghost = playerCreature->getPlayerObject();
	float rad = getRadius() * 1.05;

	float newPosX = getPositionX() + (cos(angle) * rad);
	float newPosY = getPositionY() + (sin(angle) * rad);

	// Those who aren't a valid player, do not currently have or have had the Village elder quest cannot enter.
	if (ghost != NULL) {
		if (ghost->hasGodMode())
			return;

		if (!ghost->hasActiveQuestBitSet(PlayerQuestData::FS_VILLAGE_ELDER) && !ghost->hasCompletedQuestsBitSet(PlayerQuestData::FS_VILLAGE_ELDER)) {
			playerCreature->teleport(newPosX, getZone()->getHeight(newPosX, newPosY), newPosY, 0);
			playerCreature->sendSystemMessage("@base_player:fs_village_unavailable");
		} else if (playerCreature->isInCombat()) {
			playerCreature->teleport(newPosX, getZone()->getHeight(newPosX, newPosY), newPosY, 0);
			playerCreature->sendSystemMessage("@base_player:fs_village_no_combat");
		}
	}
}
