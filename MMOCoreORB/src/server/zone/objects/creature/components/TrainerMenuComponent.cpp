/*
 * TrainerMenuComponent.cpp
 *
 *  Created on: 4/28/2012
 *      Author: TragD
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "TrainerMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/city/CityRemoveAmenityTask.h"

void TrainerMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	ManagedReference<CityRegion*> city = sceneObject->getCityRegion();

	if (city != NULL && city->isMayor(player->getObjectID()))
		menuResponse->addRadialMenuItem(72, 3, "@city/city:mt_remove"); // Remove
}

int TrainerMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (selectedID == 72) {
		ManagedReference<CityRegion*> city = sceneObject->getCityRegion();

		if (city != NULL && city->isMayor(player->getObjectID())) {
			CityRemoveAmenityTask* task = new CityRemoveAmenityTask(sceneObject, city);
			task->execute();

			player->sendSystemMessage("@city/city:mt_removed"); // The object has been removed from the city.

		}

		return 0;

	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

