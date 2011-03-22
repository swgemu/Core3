/*
 * VendorTerminalImplementation.cpp
 *
 *  Created on: Mar 13, 2011
 *      Author: polonel
 */

#include "VendorTerminal.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"

void VendorTerminalImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TerminalImplementation::loadTemplateData(templateData);
	optionsBitmask = 0x108;
	pvpStatusBitmask = 0;

	vendor.setVendor(_this);
	vendor.setVendorType(Vendor::VENDORTERMINAL);

}

void VendorTerminalImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	if (!vendor.isInitialized())
		TerminalImplementation::fillObjectMenuResponse(menuResponse, player);

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		if (inventory == NULL)
			return;

		if (inventory->hasObjectInContainer(getObjectID()))
			menuResponse->addRadialMenuItem(14, 3, "@ui:destroy");

		else if (vendor.getOwnerID() == player->getObjectID()) {
			menuResponse->addRadialMenuItem(240, 3, "@player_structure:vendor_control");
			menuResponse->addRadialMenuItemToRadialID(240, 241, 3, "Pack Vendor"); // This was in CU but could use it here.
			menuResponse->addRadialMenuItemToRadialID(240, 242, 3, "@player_structure:remove_vendor");

			if (!vendor.isInitialized())
				menuResponse->addRadialMenuItemToRadialID(240, 243, 3, "@player_structure:vendor_init");

		}
}

int VendorTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID == 243) {
		if (player->getRootParent() != getRootParent()) {
			player->sendSystemMessage("@player_structure:vendor_not_in_same_building");
			return 0;
		}

		player->sendSystemMessage("@player_structure:vendor_initialized");
		vendor.setInitialized(true);

	}

	return TerminalImplementation::handleObjectMenuSelect(player, selectedID);
}
