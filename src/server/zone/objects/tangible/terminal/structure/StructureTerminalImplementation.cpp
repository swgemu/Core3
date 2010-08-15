/*
 * StructureTerminalImplementation.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "StructureTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/building/BuildingObject.h"

void StructureTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	if (buildingObject == NULL)
		return;

	if (buildingObject->isOnAdminList(player)) {
		menuResponse->addRadialMenuItem(118, 3, "@player_structure:management"); //Structure Management
		menuResponse->addRadialMenuItemToRadialID(118, 128, 3, "@player_structure:permission_destroy"); //Destroy Structure
		menuResponse->addRadialMenuItemToRadialID(118, 124, 3, "@player_structure:management_status"); //Status
		menuResponse->addRadialMenuItemToRadialID(118, 129, 3, "@player_structure:management_pay"); //Pay Maintenance
		menuResponse->addRadialMenuItemToRadialID(118, 50, 3, "@base_player:set_name"); //Set Name
		menuResponse->addRadialMenuItemToRadialID(118, 127, 3, "@player_structure:management_residence"); //Declare Residence
		menuResponse->addRadialMenuItemToRadialID(118, 125, 3, "@player_structure:management_privacy"); //Privacy
		menuResponse->addRadialMenuItemToRadialID(118, 200, 3, "@player_structure:withdraw_maintenance"); //Withdraw from Treasury
		menuResponse->addRadialMenuItemToRadialID(118, 201, 3, "@player_structure:delete_all_items"); //Delete all items

		menuResponse->addRadialMenuItem(117, 3, "@player_structure:permissions"); //Structure Permissions
		menuResponse->addRadialMenuItemToRadialID(117, 121, 3, "@player_structure:admin_permissions_list"); //Administrators List
		menuResponse->addRadialMenuItemToRadialID(117, 119, 3, "@player_structure:permission_enter"); //Entry List
		menuResponse->addRadialMenuItemToRadialID(117, 120, 3, "@player_structure:ban_list"); //Ban List
		//menuResponse->addRadialMenuItemToRadialID(118, 122, 3, "@player_structure:permission_vendor"); //Vendor List
	}
}

int StructureTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {

	switch (selectedID) {
	case 121:
		buildingObject->sendPermissionListTo(player, "ADMIN");
		break;
	case 119:
		buildingObject->sendPermissionListTo(player, "ENTRY");
		break;
	case 120:
		buildingObject->sendPermissionListTo(player, "BAN");
		break;
	case 128:
		//Destroy Structure
		buildingObject->handleStructureDestroyRequest(player);
		break;
	case 129:
		//Pay Maintenance
		buildingObject->handlePayMaintenance(player);
		break;
	case 124:
		//Structure Status
		buildingObject->handleStructureStatus(player);
		break;
	case 127:
		buildingObject->handleDeclareResidency(player);
		break;
	case 125:
		buildingObject->handlePrivacyChange(player);
		break;
	case 50:
		buildingObject->handleSetObjectName(player);
		break;
	}

	return 0;
}
