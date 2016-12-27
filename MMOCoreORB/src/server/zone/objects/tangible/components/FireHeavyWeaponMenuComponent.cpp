/*
 * FireHeavyWeaponMenuComponent.cpp
 *
 *  Created on: May 10, 2012
 *      Author: chris.rush
 */

#include "FireHeavyWeaponMenuComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

void FireHeavyWeaponMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (sceneObject == NULL || !sceneObject->isWeaponObject() || player == NULL)
		return;

	WeaponObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int FireHeavyWeaponMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isWeaponObject() || !player->isPlayerCreature() || !sceneObject->isASubChildOf(player))
		return 0;

	if (selectedID == 20) {
		player->sendCommand(STRING_HASHCODE("fireheavyweapon"), String::valueOf(sceneObject->getObjectID()), player->getTargetID());

		return 1;
	}

	return WeaponObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
