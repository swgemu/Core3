/*
 * StructureTerminalMenuComponent.cpp
 *
 *  Created on: Feb 26, 2012
 *      Author: swgemu
 */

#include "StructureTerminalMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/managers/structure/StructureManager.h"

void StructureTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) {

	if(!sceneObject->isTerminal())
		return;

	ManagedReference<Terminal*> terminal = cast<Terminal*>(sceneObject);
	if(terminal == NULL)
		return;

	ManagedReference<StructureObject*> structureObject = cast<StructureObject*>(terminal->getControlledObject());

	if (structureObject == NULL)
		return;

	if (structureObject->isOnAdminList(creature)) {
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

int StructureTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	ManagedReference<StructureObject*> structureObject = NULL;

	if (!sceneObject->isStructureObject()) {
		ManagedReference<SceneObject*> parent = sceneObject->getRootParent();

		if (parent != NULL && parent->isStructureObject()) {
			structureObject = cast<StructureObject*>(parent.get());
		} else {
			return 1;
		}
	} else {
		structureObject = cast<StructureObject*>(sceneObject);
	}

	ManagedReference<Zone*> zone = structureObject->getZone();

	if (zone == NULL)
		return 1;

	if (!structureObject->isOnAdminList(creature))
		return 1;

	ManagedReference<StructureManager*> structureManager = zone->getStructureManager();

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
		creature->executeObjectControllerAction(0xE7E35B30, structureObject->getObjectID(), ""); //payMaintenance
		break;
	case 124:
		creature->executeObjectControllerAction(0x13F7E585, structureObject->getObjectID(), ""); //structureStatus
		break;
	case 127:
		creature->executeObjectControllerAction(0xF59E3CE1, structureObject->getObjectID(), ""); //declareResidence
		break;
	case 125:
		creature->executeObjectControllerAction(0x786CC38E, structureObject->getObjectID(), ""); //setPrivacy
		break;
	case 50:
		structureManager->promptNameStructure(creature, structureObject, NULL);
		//creature->executeObjectControllerAction(0xC367B461, structureObject->getObjectID(), ""); //nameStructure
		break;
	case 130:
		structureObject->createVendor(creature);
		break;
	}

	return 0;
}
