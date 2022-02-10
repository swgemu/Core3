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

void ElevatorMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) const {
	menuResponse->addRadialMenuItem(198, 3, "@elevator_text:up");
	menuResponse->addRadialMenuItem(199, 3, "@elevator_text:down");
}

int ElevatorMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) const {
	ManagedReference<SceneObject*> parent = creature->getParent().get();

	if (parent == nullptr || !parent->isCellObject())
		return 0;

	if (parent != sceneObject->getParent().get()) {
		creature->sendSystemMessage("@elevator_text:too_far"); // You are too far away to use that.
		return 0;
	}

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
			creature->sendSystemMessage("@elevator_text:highest_floor"); // You are already on the highest floor.
			delete floors;
			floors = nullptr;
			return 0;
		}

		z = floors->get(i - 1);
		creature->playEffect("clienteffect/elevator_rise.cef", "");
		break;
	case 199: //DOWN
		if (i >= floorCount - 1) {
			creature->sendSystemMessage("@elevator_text:lowest_floor"); // You are already on the lowest floor.
			delete floors;
			floors = nullptr;
			return 0;
		}

		z = floors->get(i + 1);
		creature->playEffect("clienteffect/elevator_descend.cef", "");
		break;
	default:
		delete floors;
		floors = nullptr;
		return 0;
	}

	delete floors;
	floors = nullptr;

	creature->teleport(x, z, y, sceneObject->getParentID());

	CloseObjectsVector* closeObjectsVector = creature->getCloseObjects();
	if (closeObjectsVector == nullptr || closeObjectsVector->size() == 0) {
		return 0;
	}

	Vector<QuadTreeEntry*> closeObjects(closeObjectsVector->size(), 10);
	closeObjectsVector->safeCopyReceiversTo(closeObjects, CloseObjectsVector::PLAYERTYPE);

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* scno = static_cast<SceneObject*>(closeObjects.get(i));
		if (scno == nullptr || scno == creature) {
			continue;
		}

		creature->sendWithoutContainerObjectsTo(scno);
	}

	return 0;
}

