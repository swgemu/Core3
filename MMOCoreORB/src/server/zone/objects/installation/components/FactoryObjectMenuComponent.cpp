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
#include "server/zone/managers/radial/RadialOptions.h"

void FactoryObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (!sceneObject->isFactory())
		return;

	FactoryObject* factory = cast<FactoryObject*>(sceneObject);

	if (!factory->isOnAdminList(player))
		return;

	InstallationObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	menuResponse->addRadialMenuItem(29, 3, "@manf_station:options"); //Options

	if (factory->getContainerObjectsSize() > 0) {
		if(!factory->isActive()) {
			menuResponse->addRadialMenuItemToRadialID(RadialOptions::CRAFT_OPTIONS, RadialOptions::SERVER_MENU2, 3, "@manf_station:activate"); //Start manufacturing objects.
			menuResponse->addRadialMenuItemToRadialID(RadialOptions::CRAFT_OPTIONS, RadialOptions::SERVER_MENU1, 3, "@manf_station:ingredients"); //List ingredients needed for station
		} else {
			menuResponse->addRadialMenuItemToRadialID(RadialOptions::CRAFT_OPTIONS, RadialOptions::SERVER_MENU2, 3, "@manf_station:deactivate"); //Stop manufacturing objects.
		}
	}

	if (!factory->isActive()) {
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::CRAFT_OPTIONS, RadialOptions::SERVER_MANF_STATION_SCHEMATIC, 3, "@manf_station:schematic"); //Access schematic slot.
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::CRAFT_OPTIONS, RadialOptions::SERVER_MANF_HOPPER_INPUT, 3, "@manf_station:input_hopper"); //Access station ingredient hopper
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::CRAFT_OPTIONS, RadialOptions::SERVER_MANF_HOPPER_OUTPUT, 3, "@manf_station:output_hopper"); //Access station output hopper
	}
}

int FactoryObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isFactory())
		return 1;

	FactoryObject* factory = cast<FactoryObject*>(sceneObject);

	if (!factory->isOnAdminList(player))
		return 1;

	switch (selectedID) {
	case RadialOptions::SERVER_MANF_HOPPER_INPUT: /// Send ingredient Hopper
		factory->sendIngredientHopper(player);
		break;
	case 29:
	case RadialOptions::SERVER_MANF_HOPPER_OUTPUT: /// Send output Hopper
		factory->sendOutputHopper(player);
		break;
	case RadialOptions::SERVER_MANF_STATION_SCHEMATIC: /// Schematic Slot
		factory->sendInsertManuSui(player);
		break;
	case RadialOptions::SERVER_MENU1: /// Send ingredients list
		factory->sendIngredientsNeededSui(player);
		break;
	case RadialOptions::SERVER_MENU2: /// Send schematic requirements
		factory->handleOperateToggle(player);
		break;
	default:
		InstallationObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
		break;
	}

	return 0;
}
