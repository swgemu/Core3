/*
 * StructureTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */

#include "engine/util/u3d/Vector3.h"

#include "StructureTerminal.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/building/BuildingObject.h"

#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"

void StructureTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	if (controlledObject == NULL || !controlledObject->isStructureObject())
		return;

	StructureObject* structureObject = (StructureObject*) controlledObject.get();

	if (!structureObject->isOnAdminList(player) && !player->getPlayerObject()->isPrivileged())
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
	//Create Vendor - 130
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

int StructureTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (controlledObject == NULL || !controlledObject->isStructureObject())
		return 1;

	StructureObject* structureObject = (StructureObject*) controlledObject.get();

	if (!structureObject->isOnAdminList(player) && !player->getPlayerObject()->isPrivileged())
		return 1;

	if (zone == NULL)
		return 1;

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	if (planetManager == NULL)
		return 1;

	ManagedReference<StructureManager*> structureManager = planetManager->getStructureManager();

	if (structureManager == NULL)
		return 1;

	Locker structureLocker(structureObject, player);

	switch (selectedID) {
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
		structureObject->sendDestroyConfirmTo(player);
		break;
	case 129:
		structureObject->sendManageMaintenanceTo(player);
		break;
	case 124:
		structureObject->sendStatusTo(player);
		break;
	case 127:
		structureManager->declareResidence(player, structureObject);
		break;
	case 125:
		structureManager->changePrivacy(player, structureObject);
		break;
	case 50:
		structureObject->sendChangeNamePromptTo(player);
		break;
	}

	return 0;
}
