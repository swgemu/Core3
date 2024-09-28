/*
 * SpaceSpawnerImplementation.cpp
 *
 * Created on: 2024-09-26
 * Author: Hakry
 */

#include "server/zone/objects/tangible/space/content_infrastructure/SpaceSpawner.h"
#include "server/zone/objects/tangible/TangibleObject.h"

void SpaceSpawnerImplementation::notifyInsert(TreeEntry* entry) {
	auto sceneO = static_cast<SceneObject*>(entry);
	uint64 scnoID = sceneO->getObjectID();

	if (sceneO == nullptr) {
		return;
	}

	if (!sceneO->isShipObject() || sceneO->isShipAiAgent()) {
		return;
	}

	auto tangibleObject = sceneO->asTangibleObject();

	if (tangibleObject == nullptr || tangibleObject->isInvisible()) {
		return;
	}

	numberOfPlayersInRange.increment();
	clearDespawnEvent();
}

void SpaceSpawnerImplementation::notifyDissapear(TreeEntry* entry) {
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