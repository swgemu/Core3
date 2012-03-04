/*
 * TrapMenuComponent.cpp
 *
 *  Created on: 10/30/2011
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "LairMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/minigames/ForageManager.h"

void LairMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	if(player->hasSkill("outdoors_scout_novice") && player->getDistanceTo(sceneObject) < 8) {
		menuResponse->addRadialMenuItem(50, 3, "@lair_n:search_lair"); //Search Lair
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

}

int LairMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	if(selectedID == 50) {

		if(player->isPlayerCreature() && player->hasSkill("outdoors_scout_novice") &&
				player->getDistanceTo(sceneObject) < 8) {

			CreatureObject* playerCreature = cast<CreatureObject*>(player);
			ForageManager* forageManager = player->getZoneProcessServer()->getForageManager();
			forageManager->startForaging(playerCreature, ForageManager::LAIR);
			return 0;
		}
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

