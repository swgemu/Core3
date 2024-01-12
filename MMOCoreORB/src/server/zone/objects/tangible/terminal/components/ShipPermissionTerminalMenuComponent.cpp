/*
 * ShipPermissionTerminalMenuComponent.cpp
 *
 *	Created on: June 7, 2023
 *	Author: hakry
 */

#include "ShipPermissionTerminalMenuComponent.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/managers/ship/ShipManager.h"

void ShipPermissionTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (sceneObject == nullptr || !sceneObject->isTerminal())
		return;

	if (player == nullptr || !player->isPlayerCreature())
		return;

	ManagedReference<Terminal*> terminal = cast<Terminal*>(sceneObject);

	if (terminal == nullptr)
		return;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	ManagedReference<SceneObject*> controlledObj = terminal->getControlledObject();

	if (controlledObj == nullptr || !controlledObj->isPobShip())
		return;

	auto pobShip = controlledObj->asPobShip();

	if (pobShip == nullptr)
		return;

	if (!pobShip->isOnAdminList(player) && !ghost->isPrivileged()) {
		return;
	}

	menuResponse->addRadialMenuItem(118, 3, "@player_structure:management"); //Structure Management
	menuResponse->addRadialMenuItemToRadialID(118, 124, 3, "@player_structure:management_status"); //Status
	menuResponse->addRadialMenuItemToRadialID(118, 201, 3, "@player_structure:delete_all_items"); //Delete all items
	menuResponse->addRadialMenuItemToRadialID(118, 202, 3, "@player_structure:move_first_item"); //Find Lost Items
	menuResponse->addRadialMenuItemToRadialID(118, 203, 3, "Activate Plasma Alarms"); //Find Lost Items

	menuResponse->addRadialMenuItem(117, 3, "@player_structure:permissions"); //Structure Permissions
	menuResponse->addRadialMenuItemToRadialID(117, 121, 3, "@player_structure:permission_admin"); //Administrator List
}

int ShipPermissionTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || player == nullptr || !player->isPlayerCreature())
		return 1;

	ManagedReference<Terminal*> terminal = cast<Terminal*>(sceneObject);

	if (terminal == nullptr)
		return 1;

	ManagedReference<SceneObject*> rootSceneO = terminal->getRootParent();

	if (rootSceneO == nullptr || !rootSceneO->isPobShip()) {
		return 1;
	}

	PobShipObject* pobShip = cast<PobShipObject*>(rootSceneO.get());

	if (pobShip == nullptr)
		return 1;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return 1;

	Locker lock(pobShip, player);

	if (pobShip->isOnAdminList(player) || ghost->isPrivileged()) {
		ShipManager* shipManager = ShipManager::instance();

		if (shipManager == nullptr)
			return 1;

		switch (selectedID) {
		case 201:
			shipManager->promptDeleteAllItems(player, pobShip);
			break;
		case 202:
			shipManager->promptFindLostItems(player, pobShip);
			break;
		case 203: {
			Locker clock(player, pobShip);

			pobShip->togglePlasmaAlarms();
			break;
		}
		case 121:
			pobShip->sendPermissionListTo(player, "ADMIN");
			break;
		case 124:
			player->executeObjectControllerAction(0x13F7E585, pobShip->getObjectID(), ""); // structureStatus
			break;
		default:
			break;
		}
	}

	return 0;
}
