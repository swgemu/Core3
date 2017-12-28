/*
 * TrainerMenuComponent.cpp
 *
 *  Created on: 4/28/2012
 *      Author: TragD
 */

#include <stddef.h>
#include <algorithm>

#include "TrainerMenuComponent.h"
#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "server/zone/managers/city/CityRemoveAmenityTask.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "system/lang/ref/Reference.h"

void TrainerMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	ManagedReference<CityRegion*> city = sceneObject->getCityRegion().get();

	if (city != NULL && city->isMayor(player->getObjectID()))
		menuResponse->addRadialMenuItem(72, 3, "@city/city:mt_remove"); // Remove
}

int TrainerMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (selectedID == 72) {
		ManagedReference<CityRegion*> city = sceneObject->getCityRegion().get();

		if (city != NULL && city->isMayor(player->getObjectID())) {
			CityRemoveAmenityTask* task = new CityRemoveAmenityTask(sceneObject, city);
			task->execute();

			player->sendSystemMessage("@city/city:mt_removed"); // The object has been removed from the city.

		}

		return 0;

	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

