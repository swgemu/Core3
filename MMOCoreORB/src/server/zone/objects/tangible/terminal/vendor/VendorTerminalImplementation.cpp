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
#include "server/zone/managers/vendor/VendorManager.h"

#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"

void VendorTerminalImplementation::initializeTransientMembers() {
	TerminalImplementation::initializeTransientMembers();

	if (vendor.isInitialized())
		vendor.rescheduleEvent();

	VendorManager::instance()->addVendor(getObjectID(), &vendor);

}

void VendorTerminalImplementation::finalize() {
	VendorManager::instance()->dropVendor(getObjectID());
}

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
			return;

		if (vendor.getOwnerID() == player->getObjectID()) {
			menuResponse->addRadialMenuItem(240, 3, "@player_structure:vendor_control");

			if (!vendor.isInitialized())
				menuResponse->addRadialMenuItemToRadialID(240, 242, 3, "@player_structure:vendor_init");

			else {
				menuResponse->addRadialMenuItemToRadialID(240, 241, 3, "@player_structure:vendor_status");
				menuResponse->addRadialMenuItemToRadialID(240, 246, 3, "@player_structure:change_name");

				if (vendor.isVendorSearchEnabled())
					menuResponse->addRadialMenuItemToRadialID(240, 243, 3, "@player_structure:disable_vendor_search");
				else
					menuResponse->addRadialMenuItemToRadialID(240, 243, 3, "@player_structure:enable_vendor_search");

				if (vendor.isRegistered())
					menuResponse->addRadialMenuItemToRadialID(240, 244, 3, "@player_structure:register_vendor");
				else
					menuResponse->addRadialMenuItemToRadialID(240, 244, 3, "@player_structure:unregister_vendor");
			}

			menuResponse->addRadialMenuItemToRadialID(240, 245, 3, "@player_structure:remove_vendor");

		}

}

int VendorTerminalImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	switch (selectedID) {
	case 241: {
		VendorManager::instance()->handleDisplayStatus(player, getVendor());
		return 0;
	}

	case 242: {
		if (player->getRootParent() != getRootParent()) {
			player->sendSystemMessage("@player_structure:vendor_not_in_same_building");
			return 0;
		}

		player->sendSystemMessage("@player_structure:vendor_initialized");
		vendor.setInitialized(true);
		vendor.runVendorCheck();

		return 0;
	}

	case 243: {
		if (vendor.isVendorSearchEnabled()) {
			vendor.setVendorSearchEnabled(false);
			player->sendSystemMessage("@player_structure:vendor_search_disabled");
		} else {
			vendor.setVendorSearchEnabled(true);
			player->sendSystemMessage("@player_structure:vendor_search_enabled");
		}

		return 0;
	}

	case 244: {
		VendorManager::instance()->handleRegisterVendor(player, getVendor());
		return 0;
	}

	case 245: {
		VendorManager::instance()->sendDestoryTo(player, getVendor());
		return 0;
	}

	case 246: {
		VendorManager::instance()->sendRenameVendorTo(player, _this);
		return 0;
	}

	default:
		return TerminalImplementation::handleObjectMenuSelect(player, selectedID);
	};

	return TerminalImplementation::handleObjectMenuSelect(player, selectedID);
}

void VendorTerminalImplementation::addVendorToMap() {
	VendorManager::instance()->addVendor(getObjectID(), &vendor);
}

void VendorTerminalImplementation::destroyObjectFromDatabase(bool destroyContainedObject) {
	VendorManager::instance()->dropVendor(getObjectID());

	ManagedReference<AuctionManager*> aman = getZoneServer()->getAuctionManager();
	if (aman == NULL)
		return;

	ManagedReference<AuctionsMap*> amap = aman->getAuctionMap();
	if (amap == NULL)
		return;

	amap->decreasePlayerVendorCount(vendor.getOwnerID());

	TerminalImplementation::destroyObjectFromDatabase(destroyContainedObject);
}
