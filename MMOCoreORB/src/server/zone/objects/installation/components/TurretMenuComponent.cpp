/*
 * TurretMenuComponent.cpp
 *
 * Created on: 2024-07-27
 * Author: Hakry
 *
 */

#include "TurretMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/TurretObject.h"
#include "templates/params/creature/ObjectFlag.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/collision/CollisionManager.h"

void TurretMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (sceneObject == nullptr || !sceneObject->isTurret() || sceneObject->getZone() == nullptr) {
		return;
	}

	if (player == nullptr || !player->isPlayerCreature() || player->isDead() || player->isIncapacitated()) {
		return;
	}

	auto zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	ManagedReference<TurretObject*> turret = cast<TurretObject*>(sceneObject);

	if (turret == nullptr) {
		return;
	}

	auto ghost = player->getPlayerObject();
	bool isPrivileged = (ghost != nullptr && ghost->isPrivileged());

	// Allow privileged access to the turret unless the player is the same faction
	if (!isPrivileged) {
		if (player->getFaction() != turret->getFaction()) {
			return;
		}

		// if turret is overt and player is not
		if ((turret->getPvpStatusBitmask() & ObjectFlag::OVERT) && (player->getPvpStatusBitmask() & !(player->getPvpStatusBitmask() & ObjectFlag::OVERT))) {
			return;
		}
	}

	menuResponse->addRadialMenuItem(37, 3, "@player_structure:management_mine_inv"); // Mine Inventory
}

int TurretMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || player == nullptr) {
		return 1;
	}

	auto zone = player->getZone();

	if (zone == nullptr) {
		return 1;
	}

	ManagedReference<TurretObject*> turret = cast<TurretObject*>(sceneObject);

	if (turret == nullptr) {
		return 1;
	}

	if (!CollisionManager::checkLineOfSight(player, turret)) {
		player->sendSystemMessage("@container_error_message:container18"); // "You can't see that object.  You may have to move closer to it."
		return 1;
	} else if (!player->isInRange(turret, 7.f)) {
		player->sendSystemMessage("@container_error_message:container09"); // "You are out of range."
		return 1;
	}

	auto ghost = player->getPlayerObject();
	bool isPrivileged = (ghost != nullptr && ghost->isPrivileged());

	switch(selectedID) {
		case 37: {
			if (isPrivileged || turret->checkContainerPermission(player, ContainerPermissions::OPEN)) {
				turret->sendWithoutParentTo(player);
				turret->openContainerTo(player);
				turret->notifyObservers(ObserverEventType::OPENCONTAINER, player);
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
