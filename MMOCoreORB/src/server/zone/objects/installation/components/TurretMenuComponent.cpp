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
#include "server/zone/objects/installation/InstallationObject.h"
#include "templates/params/creature/ObjectFlag.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/PlayerObject.h"

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

	if (player->getFaction() == Factions::FACTIONNEUTRAL) {
		return;
	}

	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);

	if (installation == nullptr) {
		return;
	}

	auto ghost = player->getPlayerObject();
	bool isPrivileged = (ghost != nullptr && ghost->isPrivileged());

	// Allow privileged access to the turret unless the player is the same faction
	if (!isPrivileged) {
		if (player->getFaction() != installation->getFaction()) {
			return;
		}

		// if turret is overt and player is not
		if ((installation->getPvpStatusBitmask() & ObjectFlag::OVERT) && (player->getPvpStatusBitmask() & !(player->getPvpStatusBitmask() & ObjectFlag::OVERT))) {
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

	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);

	if (installation == nullptr) {
		return 1;
	}

	auto ghost = player->getPlayerObject();
	bool isPrivileged = (ghost != nullptr && ghost->isPrivileged());

	switch(selectedID) {
		case 37: {
			if (isPrivileged || installation->checkContainerPermission(player, ContainerPermissions::OPEN)) {
				installation->sendWithoutParentTo(player);
				installation->openContainerTo(player);
				installation->notifyObservers(ObserverEventType::OPENCONTAINER, player);
			} else {
				player->sendSystemMessage("@error_message:perm_no_open"); // You do not have permission to access this container
			}
		}
		default:
			break;
	}

	return 0;
}
