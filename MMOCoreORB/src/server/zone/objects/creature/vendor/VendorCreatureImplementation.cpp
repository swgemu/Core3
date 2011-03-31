/*
 * NpcVendorCreatureImplementation.cpp
 *
 *  Created on: Mar 17, 2011
 *      Author: polonel
 */

#include "engine/engine.h"
#include "VendorCreature.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/building/BuildingObject.h"

#include "server/zone/templates/tangible/VendorCreatureTemplate.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/vendor/VendorManager.h"

#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"

void VendorCreatureImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	CreatureObjectImplementation::loadTemplateData(templateData);

	optionsBitmask = 0x182; // NPC and Vendor Flag
	pvpStatusBitmask = 0;

	vendor.setVendor(_this);
	vendor.setVendorType(Vendor::NPCVENDOR);

	VendorCreatureTemplate* vendorTempl = dynamic_cast<VendorCreatureTemplate*> (templateData);

	if (vendorTempl == NULL)
		return;

	String hairFile = vendorTempl->getHairFile();
	SceneObject* hairSlot = getSlottedObject("hair");

	if (hairSlot == NULL || !hairFile.isEmpty()) {
		String hairCustomization;
		ManagedReference<PlayerManager*> pman = Core::lookupObject<ZoneServer>("ZoneServer")->getPlayerManager();
		TangibleObject* hair = pman->createHairObject(hairFile, hairCustomization);

		addObject(hair, 4);
	}

	Vector<uint32>* clothes = vendorTempl->getClothes();

	for (int i = 0; i < clothes->size(); ++i) {
		uint32 templateCRC = clothes->get(i);

		ManagedReference<SceneObject*> obj = Core::lookupObject<ZoneServer>("ZoneServer")->createObject(templateCRC, 0);

		if (obj != NULL) {
			addObject(obj, 4);
		}

	}

}

void VendorCreatureImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
if (!vendor.isInitialized())
	CreatureObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == NULL)
		return;

	if (inventory->hasObjectInContainer(getObjectID())) {
		menuResponse->addRadialMenuItem(14, 3, "@ui:destroy");
		return;
	}

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

int VendorCreatureImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
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
		return CreatureObjectImplementation::handleObjectMenuSelect(player, selectedID);
	};

	return CreatureObjectImplementation::handleObjectMenuSelect(player, selectedID);

}

void VendorCreatureImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

}

void VendorCreatureImplementation::addClothingItem(WearableObject* clothing) {

}

void VendorCreatureImplementation::destroyObjectFromDatabase(bool destroyContainedObject) {
	ManagedReference<AuctionManager*> aman = getZoneServer()->getAuctionManager();
	if (aman == NULL)
		return;

	ManagedReference<AuctionsMap*> amap = aman->getAuctionMap();
	if (amap == NULL)
		return;

	amap->decreasePlayerVendorCount(vendor.getOwnerID());

	CreatureObjectImplementation::destroyObjectFromDatabase(destroyContainedObject);
}
