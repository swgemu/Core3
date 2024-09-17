/*
 * TheaterObjectImplementation.cpp
 *
 * Created on: 2024-09-17
 * Author: Hakry
 */

#include "server/zone/objects/intangible/TheaterObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"

void TheaterObjectImplementation::notifyInsert(TreeEntry* entry) {
	auto sceneO = static_cast<SceneObject*>(entry);
	uint64 scnoID = sceneO->getObjectID();

	if (sceneO == nullptr) {
		return;
	}

	if ((!sceneO->isPlayerCreature() && !sceneO->isShipObject()) || sceneO->isShipAiAgent()) {
		return;
	}

	auto tangibleObject = sceneO->asTangibleObject();

	if (tangibleObject == nullptr || tangibleObject->isInvisible()) {
		return;
	}

	numberOfPlayersInRange.increment();
	clearDespawnEvent();
}

void TheaterObjectImplementation::notifyDissapear(TreeEntry* entry) {
	auto sceneO = static_cast<SceneObject*>(entry);
	uint64 scnoID = sceneO->getObjectID();

	if (sceneO == nullptr) {
		return;
	}

	if ((!sceneO->isPlayerCreature() && !sceneO->isShipObject()) || sceneO->isShipAiAgent()) {
		return;
	}

	auto tangibleObject = sceneO->asTangibleObject();

	if (tangibleObject == nullptr || tangibleObject->isInvisible()) {
		return;
	}

	int val = numberOfPlayersInRange.decrement();

	if (val <= 0 && despawnOnNoPlayersInRange) {
		activateDespawnEvent();
	}
}