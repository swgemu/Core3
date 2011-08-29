/*
 * StructureTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */

#include "engine/util/u3d/Vector3.h"

#include "StructureTerminal.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/building/BuildingObject.h"

#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"

void StructureTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* creature) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	if (controlledObject != NULL && controlledObject->isStructureObject()) {
		StructureObject* structureObject = (StructureObject*) controlledObject.get();

		if (structureObject->isOnAdminList(creature->getFirstName())) {
			menuResponse->addRadialMenuItem(118, 3, "@player_structure:management"); //Structure Management
			menuResponse->addRadialMenuItemToRadialID(118, 128, 3, "@player_structure:permission_destroy"); //Destroy Structure
			menuResponse->addRadialMenuItemToRadialID(118, 124, 3, "@player_structure:management_status"); //Status
			menuResponse->addRadialMenuItemToRadialID(118, 129, 3, "@player_structure:management_pay"); //Pay Maintenance
			menuResponse->addRadialMenuItemToRadialID(118, 50, 3, "@player_structure:management_name_structure"); //Name Structure
			menuResponse->addRadialMenuItemToRadialID(118, 127, 3, "@player_structure:management_residence"); //Declare Residence
			menuResponse->addRadialMenuItemToRadialID(118, 125, 3, "@player_structure:management_privacy"); //Privacy

			if (creature->hasSkill("crafting_artisan_business_03"))
				menuResponse->addRadialMenuItemToRadialID(118, 130, 3, "@player_structure:create_vendor"); //Create Vendor

			//menuResponse->addRadialMenuItemToRadialID(118, 68, 3, "@player_structure:management_add_turnstile"); //Set Access Fee
			//menuResponse->addRadialMenuItemToRadialID(118, 69, 3, "@player_structure:management_change_sign"); //Change Sign
			//menuResponse->addRadialMenuItemToRadialID(118, 200, 3, "@player_structure:withdraw_maintenance"); //Withdraw from Treasury
			menuResponse->addRadialMenuItemToRadialID(118, 201, 3, "@player_structure:delete_all_items"); //Delete all items
			menuResponse->addRadialMenuItemToRadialID(118, 202, 3, "@player_structure:move_first_item"); //Find Lost Items

			menuResponse->addRadialMenuItem(117, 3, "@player_structure:permissions"); //Structure Permissions
			menuResponse->addRadialMenuItemToRadialID(117, 121, 3, "@player_structure:permission_admin"); //Administrator List
			menuResponse->addRadialMenuItemToRadialID(117, 119, 3, "@player_structure:permission_enter"); //Entry List
			menuResponse->addRadialMenuItemToRadialID(117, 120, 3, "@player_structure:permission_banned"); //Ban List
			menuResponse->addRadialMenuItemToRadialID(117, 122, 3, "@player_structure:permission_vendor"); //Vendor List
		}
	}

	if (ghost->isPrivileged()) {
		menuResponse->addRadialMenuItem(240, 1, "Admin Options");
		menuResponse->addRadialMenuItemToRadialID(240, 241, 3, "Link Terminal to Building");
	}
}

int StructureTerminalImplementation::handleObjectMenuSelect(CreatureObject* creature, byte selectedID) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return 1;

	if (ghost->isPrivileged() && selectedID == 241) {
		linkTerminal(creature);
		return 1;
	}

	if (controlledObject == NULL || !controlledObject->isStructureObject())
		return 1;

	StructureObject* structureObject = (StructureObject*) controlledObject.get();

	if (!structureObject->isOnAdminList(creature->getFirstName()) && !ghost->isPrivileged())
		return 1;

	if (getZone() == NULL)
		return 1;

	ManagedReference<StructureManager*> structureManager = getZone()->getStructureManager();

	if (structureManager == NULL)
		return 1;

	Locker structureLocker(structureObject, creature);

	switch (selectedID) {
	case 201:
		structureManager->promptDeleteAllItems(creature, structureObject);
		break;
	case 202:
		structureManager->promptFindLostItems(creature, structureObject);
		break;
	case 121:
		structureObject->sendPermissionListTo(creature, "ADMIN");
		break;
	case 119:
		structureObject->sendPermissionListTo(creature, "ENTRY");
		break;
	case 120:
		structureObject->sendPermissionListTo(creature, "BAN");
		break;
	case 122:
		structureObject->sendPermissionListTo(creature, "VENDOR");
		break;
	case 128:
		creature->executeObjectControllerAction(0x18FC1726, structureObject->getObjectID(), ""); //destroyStructure
		break;
	case 129:
		structureManager->promptManageMaintenance(creature, structureObject);
		break;
	case 124:
		creature->executeObjectControllerAction(0x13F7E585, structureObject->getObjectID(), ""); //structureStatus
		break;
	case 127:
		creature->executeObjectControllerAction(0xF59E3CE1, 0, ""); //declareResidence
		break;
	case 125:
		creature->executeObjectControllerAction(0x786CC38E, structureObject->getObjectID(), ""); //setPrivacy
		break;
	case 50:
		structureManager->promptNameStructure(creature, structureObject);
		break;
	case 130:
		structureObject->createVendor(creature);
		break;
	}

	return 0;
}
