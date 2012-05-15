/*
 * InstallationObjectMenuComponent.cpp
 *
 *  Created on: Feb 27, 2012
 *      Author: xyborn
 */

#include "InstallationObjectMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/managers/structure/StructureManager.h"

void InstallationObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!sceneObject->isInstallationObject())
		return;

	InstallationObject* installation = cast<InstallationObject*>(sceneObject);

	if (!installation->isOnAdminList(player))
		return;

	menuResponse->addRadialMenuItem(118, 3, "@player_structure:management");
	menuResponse->addRadialMenuItemToRadialID(118, 128, 3, "@player_structure:permission_destroy"); //Destroy Structure
	menuResponse->addRadialMenuItemToRadialID(118, 124, 3, "@player_structure:management_status"); //Status
	menuResponse->addRadialMenuItemToRadialID(118, 129, 3, "@player_structure:management_pay"); //Pay Maintenance
	menuResponse->addRadialMenuItemToRadialID(118, 50, 3, "@base_player:set_name"); //Set Name

	if (!installation->isGeneratorObject()) {
		menuResponse->addRadialMenuItemToRadialID(118, 51, 3, "@player_structure:management_power"); //Deposit Power
	}

	menuResponse->addRadialMenuItem(117, 3, "@player_structure:permissions"); //Structure Permissions
	menuResponse->addRadialMenuItemToRadialID(117, 121, 3, "@player_structure:permission_admin"); //Administrator List
	menuResponse->addRadialMenuItemToRadialID(117, 123, 3, "@player_structure:permission_hopper"); //Hopper List
}

int InstallationObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isInstallationObject())
		return 1;

	InstallationObject* installation = cast<InstallationObject*>(sceneObject);

	ManagedReference<Zone*> zone = installation->getZone();

	if (zone == NULL)
		return 1;

	if (!installation->isOnAdminList(player))
		return 1;

	ManagedReference<StructureManager*> structureManager = zone->getStructureManager();

	if (structureManager == NULL)
		return 1;

	switch (selectedID) {
	case 124:
		player->executeObjectControllerAction(0x13F7E585, installation->getObjectID(), ""); //structureStatus
		break;

	case 129:
		player->executeObjectControllerAction(0xE7E35B30, installation->getObjectID(), ""); //payMaintenance
		break;

	case 128:
		player->executeObjectControllerAction(0x18FC1726, installation->getObjectID(), ""); //destroyStructure command
		break;

	case 50:
		structureManager->promptNameStructure(player, installation, installation);
		//player->executeObjectControllerAction(0xC367B461, installation->getObjectID(), ""); //nameStructure
		break;

	case 51:
		//TODO: Move to structure manager.
		if (!installation->isGeneratorObject()) {
			installation->handleStructureAddEnergy(player);
		}
		break;

	case 121:
		installation->sendPermissionListTo(player, "ADMIN");
		break;

	case 123:
		installation->sendPermissionListTo(player, "HOPPER");
		break;

	default:
		break;
	}

	return 0;
}
