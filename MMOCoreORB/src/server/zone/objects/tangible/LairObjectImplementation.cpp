/*
* LairObjectImplementation.cpp
*
*  Created on: 2024/07/13
*  Author: Hakry
*/

#include "server/zone/objects/tangible/LairObject.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/objects/creature/CreatureObject.h"

void LairObjectImplementation::notifyDissapear(TreeEntry* object) {
	auto sceneO = static_cast<SceneObject*>(object);

	if (sceneO == nullptr) {
		return;
	}

	// info(true) << "LairObjectImplementation::notifyDissapear -- Lair: " << getDisplayedName() << " ID: " << getObjectID() << " Object Exited: " << sceneO->getDisplayedName();

	uint64 scnoID = sceneO->getObjectID();

	if (scnoID == getObjectID() || !sceneO->isPlayerCreature()) {
		return;
	}

	auto player = sceneO->asCreatureObject();

	if (player == nullptr || player->isInvisible()) {
		return;
	}

	int totalPlayers = numberOfPlayersInRange.decrement();

	// info(true) << "notifyDissapear -- Lair: " << getDisplayedName() << " ID: " << getObjectID() << " Total Players in Range: " << totalPlayers;

	if (totalPlayers > 0) {
		return;
	}

	if (despawnOnNoPlayersInRange) {
		activateDespawnEvent();
	}

	if (!isRepopulated()) {
		notifyObservers(ObserverEventType::NOPLAYERSINRANGE);
	}
}