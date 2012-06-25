/*
 * ElevatorDownMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#include "ElevatorDownMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"

void ElevatorDownMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) {
	menuResponse->addRadialMenuItem(198, 3, "@elevator_text:down");

	//TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, creature);
}

int ElevatorDownMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (creature->getParentID() != sceneObject->getParentID()) {
		//creature->sendSystemMessage("");
		return 0;
	}

	float z = creature->getPositionZ();

	switch (selectedID) {
	case 199: //DOWN
		z -= 10;
		creature->playEffect("clienteffect/elevator_descend.cef", "");
		break;
	default:
		return 0;
	}

	float x = creature->getPositionX();
	float y = creature->getPositionY();

	creature->teleport(x, z, y, sceneObject->getParentID());

	return 0;
}

