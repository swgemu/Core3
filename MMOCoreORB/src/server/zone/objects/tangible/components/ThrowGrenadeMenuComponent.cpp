/*
 * ThrowGrenadeMenuComponent.cpp
 *
 *  Created on: May 10, 2012
 *      Author: chris.rush
 */

#include "ThrowGrenadeMenuComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

void ThrowGrenadeMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
		if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL)
		return;

	WeaponObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int ThrowGrenadeMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject() || !player->isPlayerCreature())
		return 0;

	if (!sceneObject->isASubChildOf(player)) {
		return 0;
	}

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject);
	if(weapon == NULL)
		return 1;

	if(selectedID == 20) {
		ManagedReference<ZoneServer*> server = player->getZoneServer();
		if(server == NULL)
			return 0;

		String args = String::valueOf(sceneObject->getObjectID());
		String action = "/throwgrenade ";
		String command = action + args;

		player->sendExecuteConsoleCommand(command);

		return 1;
	}
	return WeaponObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
