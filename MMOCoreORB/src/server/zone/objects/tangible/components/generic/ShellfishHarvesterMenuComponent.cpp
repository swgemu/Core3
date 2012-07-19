/*
 * ShellfishHarvesterMenuComponent.cpp
 *
 *  Created on: 3/11/2012
 *      Author: TragD
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "ShellfishHarvesterMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/minigames/ForageManager.h"



void ShellfishHarvesterMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

}

int ShellfishHarvesterMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isASubChildOf(player))
		return 0;

	if (!sceneObject->isTangibleObject())
		return 0;

	if(selectedID == 20) {
		ForageManager* forageManager = player->getZoneProcessServer()->getForageManager();
		forageManager->startForaging(player, ForageManager::SHELLFISH);
		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

