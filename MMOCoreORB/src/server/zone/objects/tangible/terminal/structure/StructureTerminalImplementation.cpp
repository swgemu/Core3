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

void StructureTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (controlledObject == NULL || !controlledObject->isStructureObject())
		return;

	StructureObject* structureObject = (StructureObject*) controlledObject.get();

	if (!structureObject->isOnAdminList(player->getFirstName()) && !player->getPlayerObject()->isPrivileged())
		return;

	menuResponse->addRadialMenuItem(118, 3, "@player_structure:management"); //Structure Management
	menuResponse->addRadialMenuItemToRadialID(118, 128, 3, "@player_structure:permission_destroy"); //Destroy Structure

	//CityHalls only have Destroy Structure option
	if (structureObject->isBuildingObject() && ((BuildingObject*) structureObject)->isCityHallBuilding() && !player->getPlayerObject()->isPrivileged())
		return;

	menuResponse->addRadialMenuItemToRadialID(118, 124, 3, "@player_structure:management_status"); //Status
	menuResponse->addRadialMenuItemToRadialID(118, 129, 3, "@player_structure:management_pay"); //Pay Maintenance
	menuResponse->addRadialMenuItemToRadialID(118, 50, 3, "@base_player:set_name"); //Set Name
	menuResponse->addRadialMenuItemToRadialID(118, 127, 3, "@player_structure:management_residence"); //Declare Residence
	menuResponse->addRadialMenuItemToRadialID(118, 125, 3, "@player_structure:management_privacy"); //Privacy
	if (player->hasSkillBox("crafting_artisan_business_03"))
		menuResponse->addRadialMenuItemToRadialID(118, 130, 3, "@player_structure:create_vendor"); //Create Vendor - 130

	//Set Access Fee
	//Change Sign

	//Only on guild halls...
	//menuResponse->addRadialMenuItemToRadialID(118, 200, 3, "@player_structure:withdraw_maintenance"); //Withdraw from Treasury
	//Find lost items
	menuResponse->addRadialMenuItemToRadialID(118, 201, 3, "@player_structure:delete_all_items"); //Delete all items

	menuResponse->addRadialMenuItem(117, 3, "@player_structure:permissions"); //Structure Permissions
	menuResponse->addRadialMenuItemToRadialID(117, 121, 3, "@player_structure:permission_admin"); //Administrator List
	menuResponse->addRadialMenuItemToRadialID(117, 119, 3, "@player_structure:permission_enter"); //Entry List
	menuResponse->addRadialMenuItemToRadialID(117, 120, 3, "@player_structure:permission_banned"); //Ban List
	//menuResponse->addRadialMenuItemToRadialID(118, 122, 3, "@player_structure:permission_vendor"); //Vendor List

}

int StructureTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (controlledObject == NULL || !controlledObject->isStructureObject())
		return 1;

	StructureObject* structureObject = (StructureObject*) controlledObject.get();

	if (!structureObject->isOnAdminList(player->getFirstName()) && !player->getPlayerObject()->isPrivileged())
		return 1;

	if (getZone() == NULL)
		return 1;

	ManagedReference<StructureManager*> structureManager = getZone()->getStructureManager();

	if (structureManager == NULL)
		return 1;

	Locker structureLocker(structureObject, player);

	switch (selectedID) {
	case 118:
		//structureManager->deleteAllItems();
		break;
	case 121:
		structureObject->sendPermissionListTo(player, "ADMIN");
		break;
	case 119:
		structureObject->sendPermissionListTo(player, "ENTRY");
		break;
	case 120:
		structureObject->sendPermissionListTo(player, "BAN");
		break;
	case 128:
		player->executeObjectControllerAction(0x18FC1726, structureObject->getObjectID(), ""); //destroyStructure
		break;
	case 129:
		structureObject->sendManageMaintenanceTo(player);
		break;
	case 124:
		player->executeObjectControllerAction(0x13F7E585, structureObject->getObjectID(), ""); //structureStatus
		break;
	case 127:
		player->executeObjectControllerAction(0xF59E3CE1, 0, ""); //declareResidence
		break;
	case 125:
		player->executeObjectControllerAction(0x786CC38E, structureObject->getObjectID(), ""); //setPrivacy
		break;
	case 50:
		player->executeObjectControllerAction(0xC367B461, structureObject->getObjectID(), ""); //nameStructure
		break;
	case 130:
		structureObject->createVendor(player);
		break;
	}

	return 0;
}
