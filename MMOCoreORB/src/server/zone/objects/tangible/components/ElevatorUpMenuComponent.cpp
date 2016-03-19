/*
 * ElevatorUpMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#include "ElevatorUpMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"

void ElevatorUpMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) const {
	menuResponse->addRadialMenuItem(198, 3, "@elevator_text:up");
}

int ElevatorUpMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) const {
	if (selectedID != 198)
		return 0;

	return ElevatorMenuComponent::handleObjectMenuSelect(sceneObject, creature, selectedID);
}
