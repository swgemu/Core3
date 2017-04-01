/*
 * CityDecorationMenuComponent.cpp
 *
 *  Created on: Aug 25, 2013
 *      Author: root
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "CityDecorationMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/managers/city/CityDecorationTask.h"

void CityDecorationMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	ManagedReference<CityRegion*> city = player->getCityRegion().get();


	if(isInInventory(sceneObject, player) && player->getParent() == NULL) {
		menuResponse->addRadialMenuItem(233, 3, "@city/city:place"); // Place Decoration
	}

	if(city != NULL && sceneObject->getParent() == NULL && sceneObject->getCityRegion() == city && city->isMayor(player->getObjectID()) ) {
		menuResponse->addRadialMenuItem(234, 3, "@city/city:mt_remove"); // Remove

		menuResponse->addRadialMenuItem(73, 3, "@city/city:align"); // Align
		menuResponse->addRadialMenuItemToRadialID(73, 74, 3, "@city/city:north"); // North
		menuResponse->addRadialMenuItemToRadialID(73, 75, 3, "@city/city:east"); // East
		menuResponse->addRadialMenuItemToRadialID(73, 76, 3, "@city/city:south"); // South
		menuResponse->addRadialMenuItemToRadialID(73, 77, 3, "@city/city:west"); // West
	}

}

int CityDecorationMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	if ( selectedID == 233 ) {

		Reference<CityDecorationTask*> task = new CityDecorationTask(player, cast<TangibleObject*>(sceneObject), CityDecorationTask::PLACE);
		task->execute();
		return 0;

	} else if (selectedID == 234) {

		Reference<CityDecorationTask*> task = new CityDecorationTask(player, cast<TangibleObject*>(sceneObject), CityDecorationTask::REMOVE);
		task->execute();
		return 0;

	} else if (selectedID == 74 || selectedID == 75 || selectedID == 76 || selectedID == 77) {
		ManagedReference<CityRegion*> city = player->getCityRegion().get();

		CityManager* cityManager = sceneObject->getZoneServer()->getCityManager();
		cityManager->alignAmenity(city, player, sceneObject, selectedID - 74);

		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}

bool CityDecorationMenuComponent::isInInventory(SceneObject* sceneObject, CreatureObject* player) const {
	return sceneObject->isASubChildOf(player);
}





