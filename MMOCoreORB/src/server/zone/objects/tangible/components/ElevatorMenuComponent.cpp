/*
 * ElevatorMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#include "ElevatorMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/cell/CellObject.h"

void ElevatorMenuComponent::fillObjectMenuResponse(SceneObject* terminal, ObjectMenuResponse* menuResponse, CreatureObject* playerCreo) const {
	menuResponse->addRadialMenuItem(198, 3, "@elevator_text:up");
	menuResponse->addRadialMenuItem(199, 3, "@elevator_text:down");
}

int ElevatorMenuComponent::handleObjectMenuSelect(SceneObject* terminal, CreatureObject* playerCreo, byte selectedID) const {
	ManagedReference<SceneObject*> parent = playerCreo->getParent().get();

	if (parent == nullptr || !parent->isCellObject())
		return 0;

	if (parent != terminal->getParent().get()) {
		playerCreo->sendSystemMessage("@elevator_text:too_far"); // You are too far away to use that.
		return 0;
	}

	CellObject* cell = parent.castTo<CellObject*>();

	float newX = playerCreo->getPositionX();
	float newY = playerCreo->getPositionY();
	float newZ = playerCreo->getPositionZ();

	Vector<float>* floors = CollisionManager::getCellFloorCollision(newX, newY, cell);
	int floorCount = floors->size();

	int i = 0;
	for (; i < floorCount; ++i) {
		float f = floors->get(i);

		if (fabs(newZ - f) < 1.f)
			break; //Almost certainly the same floor.
	}

	switch (selectedID) {
	case 198: //UP
		if (i <= 0) {
			playerCreo->sendSystemMessage("@elevator_text:highest_floor"); // You are already on the highest floor.
			delete floors;
			floors = nullptr;
			return 0;
		}

		newZ = floors->get(i - 1);
		playerCreo->playEffect("clienteffect/elevator_rise.cef", "");
		break;
	case 199: //DOWN
		if (i >= floorCount - 1) {
			playerCreo->sendSystemMessage("@elevator_text:lowest_floor"); // You are already on the lowest floor.
			delete floors;
			floors = nullptr;
			return 0;
		}

		newZ = floors->get(i + 1);
		playerCreo->playEffect("clienteffect/elevator_descend.cef", "");
		break;
	default:
		delete floors;
		floors = nullptr;
		return 0;
	}

	delete floors;
	floors = nullptr;

	playerCreo->teleport(newX, newZ, newY, parent->getObjectID());

	parent->broadcastObject(playerCreo, true);

	PlayerObject* ghost = playerCreo->getPlayerObject();

	if (ghost == nullptr)
		return 0;

	// Pets
	for (int i = 0; i < ghost->getActivePetsSize(); i++) {
		ManagedReference<AiAgent*> pet = ghost->getActivePet(i);

		if (pet != nullptr) {
			if (pet->isDead() || pet->isIncapacitated() || !pet->isInRange(playerCreo, 7.f))
				continue;

			pet->teleport(newX, newZ, newY, parent->getObjectID());

			parent->broadcastObject(pet, true);
		}
	}

	return 0;
}
