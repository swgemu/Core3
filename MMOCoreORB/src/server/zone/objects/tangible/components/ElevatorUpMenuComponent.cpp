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

void ElevatorUpMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) {
	menuResponse->addRadialMenuItem(198, 3, "@elevator_text:up");

	//TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, creature);
}

int ElevatorUpMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (creature->getParentID() != sceneObject->getParentID()) {
		//creature->sendSystemMessage("");
		return 0;
	}

	float z = creature->getPositionZ();

	switch (selectedID) {
	case 198: //UP
		z += 10;
		creature->playEffect("clienteffect/elevator_rise.cef", "");
		break;
	default:
		return 0;
	}

	float x = creature->getPositionX();
	float y = creature->getPositionY();

	creature->teleport(x, z, y, sceneObject->getParentID());

	return 0;
}

