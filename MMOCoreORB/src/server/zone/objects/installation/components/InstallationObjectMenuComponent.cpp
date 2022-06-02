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
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/radial/RadialOptions.h"

void InstallationObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (!sceneObject->isInstallationObject())
		return;

	InstallationObject* installation = cast<InstallationObject*>(sceneObject);

	if (!installation->isOnAdminList(player))
		return;

	menuResponse->addRadialMenuItem(RadialOptions::SERVER_TERMINAL_MANAGEMENT, 3, "@player_structure:management");
	menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_TERMINAL_MANAGEMENT, RadialOptions::SERVER_TERMINAL_MANAGEMENT_DESTROY, 3, "@player_structure:permission_destroy"); // Destroy Structure

	if (installation->isMinefield())
		return;

	menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_TERMINAL_MANAGEMENT, RadialOptions::SERVER_TERMINAL_MANAGEMENT_STATUS, 3, "@player_structure:management_status"); // Status
	menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_TERMINAL_MANAGEMENT, RadialOptions::SERVER_TERMINAL_MANAGEMENT_PAY, 3, "@player_structure:management_pay"); // Pay Maintenance

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if(datapad != nullptr) {
		for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

			if (object != nullptr && object->isPetControlDevice()) {
				PetControlDevice* device = cast<PetControlDevice*>( object.get());

				if (device->getPetType() == PetManager::DROIDPET) {
					menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_TERMINAL_MANAGEMENT, RadialOptions::SERVER_MENU5, 3, "@player_structure:assign_droid"); // Assign Droid
					break;
				}
			}
		}
	}

	if (!installation->isTurretInstallation()) {
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_TERMINAL_MANAGEMENT, RadialOptions::SERVER_MENU1, 3, "@base_player:set_name"); // Set Name

		if (installation->getGameObjectType() != SceneObjectType::GENERATOR) {
			menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_TERMINAL_MANAGEMENT, RadialOptions::SERVER_MENU6, 3, "@player_structure:management_power"); // Deposit Power
		}

		menuResponse->addRadialMenuItem(RadialOptions::SERVER_TERMINAL_PERMISSIONS, 3, "@player_structure:permissions"); //Structure Permissions
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_TERMINAL_PERMISSIONS, RadialOptions::SERVER_TERMINAL_PERMISSIONS_ADMIN, 3, "@player_structure:permission_admin"); // Administrator List
		menuResponse->addRadialMenuItemToRadialID(RadialOptions::SERVER_TERMINAL_PERMISSIONS, RadialOptions::SERVER_TERMINAL_PERMISSIONS_HOPPER, 3, "@player_structure:permission_hopper"); // Hopper List
	}

}

int InstallationObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isInstallationObject())
		return 1;

	InstallationObject* installation = cast<InstallationObject*>(sceneObject);

	ManagedReference<Zone*> zone = installation->getZone();

	if (zone == nullptr)
		return 1;

	if (!installation->isOnAdminList(player))
		return 1;

	StructureManager* structureManager = StructureManager::instance();

	switch (selectedID) {
	case RadialOptions::SERVER_TERMINAL_MANAGEMENT:
	case RadialOptions::SERVER_TERMINAL_MANAGEMENT_STATUS:
		player->sendCommand(STRING_HASHCODE("structureStatus"), "");
		break;

	case 129:
		player->executeObjectControllerAction(0xE7E35B30, installation->getObjectID(), ""); //payMaintenance
		break;

	case 128:
		player->executeObjectControllerAction(0x18FC1726, installation->getObjectID(), ""); //destroyStructure command
		break;

	case 131:
		structureManager->promptMaintenanceDroid(installation,player);
		break;
	case 50:
		structureManager->promptNameStructure(player, installation, installation);
		//player->executeObjectControllerAction(0xC367B461, installation->getObjectID(), ""); //nameStructure
		break;

	case 51:
		//TODO: Move to structure manager.
		if (installation->getGameObjectType() != SceneObjectType::GENERATOR) {
			//installation->handleStructureAddEnergy(player);
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


