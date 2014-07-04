/*
 * CityDecorationMenuComponent.cpp
 *
 *  Created on: Aug 25, 2013
 *      Author: root
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "CityDecorationMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/managers/city/CityDecorationTask.h"

void CityDecorationMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	ManagedReference<CityRegion*> city = player->getCityRegion();


	if(isInInventory(sceneObject, player) && player->getParent() == NULL){
		menuResponse->addRadialMenuItem(233, 3, "@city/city:place"); // Place Decoration
	}

	if(city != NULL && sceneObject->getParent() == NULL && sceneObject->getCityRegion() == city && city->isMayor(player->getObjectID()) ){
		menuResponse->addRadialMenuItem(234, 3, "Remove");
	}

}

int CityDecorationMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	if ( selectedID == 233 ) {

		Reference<CityDecorationTask*> task = new CityDecorationTask(player, sceneObject, CityDecorationTask::PLACE);
		task->execute();
		return 0;

	} else if (selectedID == 234) {

		Reference<CityDecorationTask*> task = new CityDecorationTask(player, sceneObject, CityDecorationTask::REMOVE);
		task->execute();
		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

bool CityDecorationMenuComponent::isInInventory(SceneObject* sceneObject, CreatureObject* player){
	return sceneObject->isASubChildOf(player);
}





