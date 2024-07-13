/*
* LairObjectImplementation.cpp
*
*  Created on: 2024/07/13
*  Author: Hakry
*/

#include "server/zone/objects/tangible/LairObject.h"
#include "templates/params/ObserverEventType.h"

void LairObjectImplementation::notifyDissapear(TreeEntry* object) {
	auto sceneO = static_cast<SceneObject*>(object);

	if (sceneO == nullptr) {
		return;
	}

	// info(true) << "LairObjectImplementation::notifyDissapear - Object Exited: " << sceneO->getDisplayedName();

	uint64 scnoID = sceneO->getObjectID();

	if (scnoID == getObjectID() || !sceneO->isPlayerCreature()) {
		return;
	}

	auto player = sceneO->asCreatureObject();

	if (player == nullptr) {
		return;
	}

	int val = numberOfPlayersInRange.decrement();

	if (val > 0) {
		return;
	}

	if (despawnOnNoPlayersInRange) {
		activateDespawnEvent();
	}

	if (!isRepopulated()) {
		notifyObservers(ObserverEventType::NOPLAYERSINRANGE);
	}
}