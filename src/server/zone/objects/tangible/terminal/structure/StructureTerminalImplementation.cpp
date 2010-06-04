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
		menuResponse->addRadialMenuItem(51, 3, "@player_structure:management"); //Structure Management
		menuResponse->addRadialMenuItemToRadialID(51, 52, 3, "@player_structure:permission_destroy"); //Destroy Structure
		menuResponse->addRadialMenuItemToRadialID(51, 52, 3, "@player_structure:management_status"); //Status
	}
}

int StructureTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {

	switch (selectedID) {
	case 52:
		buildingObject->sendPermissionListTo(player, "ADMIN");
		break;
	}

	return 0;
}
