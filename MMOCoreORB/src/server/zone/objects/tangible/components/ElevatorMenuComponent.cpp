/*
 * ElevatorMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#include "ElevatorMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/cell/CellObject.h"

void ElevatorMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) {
	menuResponse->addRadialMenuItem(198, 3, "@elevator_text:up");
	menuResponse->addRadialMenuItem(199, 3, "@elevator_text:down");
}

int ElevatorMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	ManagedReference<SceneObject*> parent = creature->getParent().get();

	if (parent == NULL || !parent->isCellObject() || parent != sceneObject->getParent().get())
		return 0;

	CellObject* cell = parent.castTo<CellObject*>();

	float x = creature->getPositionX();
	float y = creature->getPositionY();
	float z = sceneObject->getPositionZ();

	Vector<float>* floors = CollisionManager::getCellFloorCollision(x, y, cell);
	int floorCount = floors->size();

	int i = 0;
	for (; i < floorCount; ++i) {
		float f = floors->get(i);

		if (fabs(z - f) < 1.f)
			break; //Almost certainly the same floor.
	}

	switch (selectedID) {
	case 198: //UP
		if (i <= 0) {
			creature->sendSystemMessage("You are already on the highest floor");
			delete floors;
			floors = NULL;
			return 0;
		}

		z = floors->get(i - 1);
		creature->playEffect("clienteffect/elevator_rise.cef", "");
		break;
	case 199: //DOWN
		if (i >= floorCount - 1) {
			creature->sendSystemMessage("You are already on the lowest floor");
			delete floors;
			floors = NULL;
			return 0;
		}

		z = floors->get(i + 1);
		creature->playEffect("clienteffect/elevator_descend.cef", "");
		break;
	default:
		delete floors;
		floors = NULL;
		return 0;
	}

	creature->teleport(x, z, y, sceneObject->getParentID());

	delete floors;
	floors = NULL;

	return 0;
}

