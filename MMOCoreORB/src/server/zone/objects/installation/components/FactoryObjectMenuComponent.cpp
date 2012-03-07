/*
 * FactoryObjectMenuComponent.cpp
 *
 *  Created on: Feb 27, 2012
 *      Author: xyborn
 */

#include "FactoryObjectMenuComponent.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/installation/factory/FactoryObject.h"

void FactoryObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!sceneObject->isFactory())
		return;

	FactoryObject* factory = cast<FactoryObject*>(sceneObject);

	if (!factory->isOnAdminList(player->getFirstName()))
		return;

	InstallationObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	menuResponse->addRadialMenuItem(29, 3, "@manf_station:options"); //Options

	if(factory->getContainerObjectsSize() > 0) {
		if(!factory->isOperating()) {
			menuResponse->addRadialMenuItemToRadialID(29, 69, 3, "@manf_station:activate"); //Start manufacturing objects.
			menuResponse->addRadialMenuItemToRadialID(29, 68, 3, "@manf_station:ingredients"); //List ingredients needed for station
		} else {
			menuResponse->addRadialMenuItemToRadialID(29, 69, 3, "@manf_station:deactivate"); //Stop manufacturing objects.
		}
	}

	if(!factory->isOperating()) {
		menuResponse->addRadialMenuItemToRadialID(29, 197, 3, "@manf_station:schematic"); //Access schematic slot.
		menuResponse->addRadialMenuItemToRadialID(29, 195, 3, "@manf_station:input_hopper"); //Access station ingredient hopper
		menuResponse->addRadialMenuItemToRadialID(29, 196, 3, "@manf_station:output_hopper"); //Access station output hopper
	}
}

int FactoryObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isFactory())
		return 1;

	FactoryObject* factory = cast<FactoryObject*>(sceneObject);

	if (!factory->isOnAdminList(player->getFirstName()))
		return 1;

	switch (selectedID) {
	case 195: /// Send ingredient Hopper
		factory->sendIngredientHopper(player);
		break;
	case 29:
	case 196: /// Send output Hopper
		factory->sendOutputHopper(player);
		break;
	case 197: /// Schematic Slot
		factory->sendInsertManuSui(player);
		break;
	case 68: /// Send ingredients list
		factory->sendIngredientsNeededSui(player);
		break;
	case 69: /// Send schematic requirements
		factory->handleOperateToggle(player);
		break;

	default:
		InstallationObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
		break;
	}

	return 0;
}
