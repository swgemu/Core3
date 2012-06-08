/*
 * FireHeavyWeaponMenuComponent.cpp
 *
 *  Created on: May 10, 2012
 *      Author: chris.rush
 */

#include "FireHeavyWeaponMenuComponent.h"
#include "TangibleObjectMenuComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

int FireHeavyWeaponMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	switch (selectedID) {
	case 20:
		player->sendExecuteConsoleCommand("fireheavyweapon");
		break;
	default:
		TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
		break;
	}
	return 0;
}
