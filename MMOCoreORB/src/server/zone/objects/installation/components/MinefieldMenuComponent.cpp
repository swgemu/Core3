/*
 * MinefieldMenuComponent.cpp
 *
 *  Created on: Jan 31, 2013
 *  Author: root
 */

#include "MinefieldMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "templates/params/creature/ObjectFlag.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/collision/CollisionManager.h"

void MinefieldMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (sceneObject == nullptr || !sceneObject->isMinefield() || sceneObject->getZone() == nullptr) {
		return;
	}

	if (player == nullptr || !player->isPlayerCreature() || player->isDead() || player->isIncapacitated()) {
		return;
	}

	auto zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	if (player->getFaction() == Factions::FACTIONNEUTRAL) {
		return;
	}

	ManagedReference<InstallationObject*> minefield = cast<InstallationObject*>(sceneObject);

	if (minefield == nullptr) {
		return;
	}

	auto ghost = player->getPlayerObject();
	bool isPrivileged = (ghost != nullptr && ghost->isPrivileged());

	// Allow privileged access to the mine unless the player is the same faction
	if (!isPrivileged) {
		if (player->getFaction() != minefield->getFaction()) {
			return;
		}

		// if minefield is overt and player is not
		if ((minefield->getPvpStatusBitmask() & ObjectFlag::OVERT) && (player->getPvpStatusBitmask() & !(player->getPvpStatusBitmask() & ObjectFlag::OVERT))) {
			return;
		}
	}

	menuResponse->addRadialMenuItem(37, 3, "@player_structure:management_mine_inv"); // Mine Inventory
}

int MinefieldMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || player == nullptr) {
		return 1;
	}

	auto zone = player->getZone();

	if (zone == nullptr) {
		return 1;
	}

	ManagedReference<InstallationObject*> minefield = cast<InstallationObject*>(sceneObject);

	if (minefield == nullptr) {
		return 1;
	}

	if (!CollisionManager::checkLineOfSight(player, minefield)) {
		player->sendSystemMessage("@container_error_message:container18"); // "You can't see that object.  You may have to move closer to it."
		return 1;
	} else if (!player->isInRange(minefield, 7.f)) {
		player->sendSystemMessage("@container_error_message:container09"); // "You are out of range."
		return 1;
	}

	auto ghost = player->getPlayerObject();
	bool isPrivileged = (ghost != nullptr && ghost->isPrivileged());

	switch(selectedID) {
		case 37: {
			if (isPrivileged || minefield->checkContainerPermission(player, ContainerPermissions::OPEN)) {
				minefield->sendWithoutParentTo(player);
				minefield->openContainerTo(player);
				minefield->notifyObservers(ObserverEventType::OPENCONTAINER, player);
			} else {
				player->sendSystemMessage("@error_message:perm_no_open"); // You do not have permission to access this container
			}

			break;
		}
		default:
			break;
	}

	return 0;
}
