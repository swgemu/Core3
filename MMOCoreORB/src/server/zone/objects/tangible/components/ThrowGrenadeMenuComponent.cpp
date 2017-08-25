/*
 * ThrowGrenadeMenuComponent.cpp
 *
 *  Created on: May 10, 2012
 *      Author: chris.rush
 */

#include "ThrowGrenadeMenuComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

void ThrowGrenadeMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
		if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL)
		return;

	WeaponObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int ThrowGrenadeMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isTangibleObject() || !player->isPlayerCreature())
		return 0;

	if (!sceneObject->isASubChildOf(player)) {
		return 0;
	}

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject);
	if(weapon == NULL)
		return 1;

	if(selectedID == 20) {
		Reference<CreatureObject*> strongRef = player;
		Reference<WeaponObject*> strongRefWeapon = weapon;

		Core::getTaskManager()->executeTask([strongRef, strongRefWeapon] () {
			Locker locker(strongRef);

			strongRef->sendCommand(STRING_HASHCODE("throwgrenade"), String::valueOf(strongRefWeapon->getObjectID()), strongRef->getTargetID());
		}, "ThrowGrenadeSendCommandLambda");

		return 1;
	}
	return WeaponObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
