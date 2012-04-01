/*
 * FsVillageAreaImplementation.cpp
 *
 *  Created on: 01/04/2012
 *      Author: victor
 */

#include "FsVillageArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/Zone.h"

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

	playerCreature->sendSystemMessage("@fs_quest_village:expel_shield");

	float newPosX = getPositionX() + (cos(angle) * 530);
	float newPosY = getPositionY() + (sin(angle) * 530);

	playerCreature->teleport(newPosX, getZone()->getHeight(newPosX, newPosY), newPosY, 0);
}
