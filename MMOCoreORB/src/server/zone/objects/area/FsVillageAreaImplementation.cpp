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

	float newPosX = getPositionX() + (cos(angle) * 530);
	float newPosY = getPositionY() + (sin(angle) * 530);

	// Those who aren't a valid player, do not currently have or have had the Village elder quest cannot enter.
	if (ghost != NULL) {
		if (!ghost->hasActiveQuestBitSet(PlayerQuestData::FS_VILLAGE_ELDER)) {
			if (!ghost->hasCompletedQuestsBitSet(PlayerQuestData::FS_VILLAGE_ELDER)){
				if (ghost->isPrivileged())
					return;

				playerCreature->teleport(newPosX, getZone()->getHeight(newPosX, newPosY), newPosY, 0);
				playerCreature->sendSystemMessage("@fs_quest_village:expel_shield");
			}
		}
	}
}
