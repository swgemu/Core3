/*
 * WearableObjectMenuComponent.cpp
 *
 *  Created on: 10/30/2011
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "WearableObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/tool/RepairToolTemplate.h"
#include "server/zone/objects/tangible/tool/repair/RepairTool.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

void WearableObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if(!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	if(tano->getConditionDamage() > 0 && tano->canRepair(player)) {
		menuResponse->addRadialMenuItem(70, 3, "@sui:repair"); // Slice
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

}

int WearableObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isASubChildOf(player))
		return 0;

	if(selectedID == 70) {

		if(!sceneObject->isTangibleObject())
			return 0;

		TangibleObject* tano = cast<TangibleObject*>(sceneObject);
		if(tano == NULL)
			return 0;

		tano->repair(player);

		return 1;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
