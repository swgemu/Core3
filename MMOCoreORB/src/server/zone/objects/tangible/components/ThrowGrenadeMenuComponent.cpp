/*
 * ThrowGrenadeMenuComponent.cpp
 *
 *  Created on: May 10, 2012
 *      Author: chris.rush
 */

#include "ThrowGrenadeMenuComponent.h"
#include "TangibleObjectMenuComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

int ThrowGrenadeMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	switch (selectedID) {
	case 20:
		player->sendExecuteConsoleCommand("throwgrenade");
		break;
	default:
		TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
	}
	return 0;
}
