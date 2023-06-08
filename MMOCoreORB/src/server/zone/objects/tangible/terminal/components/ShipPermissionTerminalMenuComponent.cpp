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

/*
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/player/sessions/StructureSetAccessFeeSession.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"
*/

void ShipPermissionTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	info(true) << "ShipPermissionTerminalMenuComponent::fillObjectMenuResponse ";

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

	if (controlledObj == nullptr || !controlledObj->isPobShipObject())
		return;

	auto pobShip = controlledObj->asPobShipObject();

	if (pobShip == nullptr)
		return;

	auto shipOwner = pobShip->getOwner().get();

	if (shipOwner == nullptr && !ghost->isPrivileged())
		return;

	// TODO: Admin list check?

	menuResponse->addRadialMenuItem(118, 3, "@player_structure:management"); //Structure Management
	menuResponse->addRadialMenuItemToRadialID(118, 124, 3, "@player_structure:management_status"); //Status
	menuResponse->addRadialMenuItemToRadialID(118, 201, 3, "@player_structure:delete_all_items"); //Delete all items
	menuResponse->addRadialMenuItemToRadialID(118, 202, 3, "@player_structure:move_first_item"); //Find Lost Items


	menuResponse->addRadialMenuItem(117, 3, "@player_structure:permissions"); //Structure Permissions
	menuResponse->addRadialMenuItemToRadialID(117, 121, 3, "@player_structure:permission_admin"); //Administrator List
}

int ShipPermissionTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || player == nullptr || !player->isPlayerCreature())
		return 1;

	ManagedReference<Terminal*> terminal = cast<Terminal*>(sceneObject);

	if (terminal == nullptr)
		return 1;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return 1;

	player->sendSystemMessage("Hakrys TODO");

	return 0;
}
