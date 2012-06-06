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
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

#include "server/zone/templates/tangible/VendorCreatureTemplate.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/vendor/VendorManager.h"

#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"

#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/vendor/VendorOutfitManager.h"
#include "server/zone/managers/vendor/Outfit.h"

#include "server/zone/Zone.h"

void VendorCreatureImplementation::initializeTransientMembers() {
	CreatureObjectImplementation::initializeTransientMembers();

	if (vendor.isInitialized())
		vendor.rescheduleEvent();

	VendorManager::instance()->addVendor(getObjectID(), &vendor);

}

void VendorCreatureImplementation::finalize() {
	VendorManager::instance()->dropVendor(getObjectID());
}

void VendorCreatureImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	CreatureObjectImplementation::loadTemplateData(templateData);

	optionsBitmask = 0x182; // NPC and Vendor Flag
	pvpStatusBitmask = 0;

	vendor.setVendor(_this.get());
	vendor.setVendorType(Vendor::NPCVENDOR);

}

void VendorCreatureImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
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

			if (!vendor.isRegistered())
				menuResponse->addRadialMenuItemToRadialID(240, 244, 3, "@player_structure:register_vendor");
			else
				menuResponse->addRadialMenuItemToRadialID(240, 244, 3, "@player_structure:unregister_vendor");
		}

		menuResponse->addRadialMenuItemToRadialID(240, 245, 3, "@player_structure:remove_vendor");

	}

}

int VendorCreatureImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	switch (selectedID) {
	case 241: {
		VendorManager::instance()->handleDisplayStatus(player, &vendor);
		return 0;
	}

	case 242: {
		if (player->getRootParent().get() != getRootParent().get()) {
			player->sendSystemMessage("@player_structure:vendor_not_in_same_building");
			return 0;
		}

		if (vendor.isInitialized())
			return 0;

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
		if (!vendor.isRegistered())
			VendorManager::instance()->sendRegisterVendorTo(player, &vendor);
		else
			VendorManager::instance()->handleUnregisterVendor(player, &vendor);
		return 0;
	}

	case 245: {
		VendorManager::instance()->sendDestoryTo(player, &vendor);
		return 0;
	}

	case 246: {
		VendorManager::instance()->sendRenameVendorTo(player, _this.get());
		return 0;
	}

	default:
		return CreatureObjectImplementation::handleObjectMenuSelect(player, selectedID);
	};

	return CreatureObjectImplementation::handleObjectMenuSelect(player, selectedID);

}

void VendorCreatureImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

}

void VendorCreatureImplementation::addClothingItem(CreatureObject* player, TangibleObject* clothing) {
	if (!clothing->isWearableObject() && !clothing->isWeaponObject())
		return;

	if (player->getObjectID() != vendor.getOwnerID())
		return;

	SharedTangibleObjectTemplate* tanoData = dynamic_cast<SharedTangibleObjectTemplate*>(clothing->getObjectTemplate());
	Vector<uint32>* races = tanoData->getPlayerRaces();
	String race = getObjectTemplate()->getFullTemplateString();

	if (!races->contains(race.hashCode())) {
		//TODO: Change this so the vendor speaks it can't wear that item. like live.
		player->sendSystemMessage("That vendor lacks the necessary requirements to wear this object");
		return;
	}

	ManagedReference<SceneObject*> clothingParent = clothing->getParent();

	if (clothingParent == NULL)
		return;

	//clothingParent->removeObject(clothing, true);
	//clothing->destroyObjectFromWorld(true);

	for (int i = 0; i < clothing->getArrangementDescriptorSize(); ++i) {
		String arrangementDescriptor = clothing->getArrangementDescriptor(i);
		ManagedReference<SceneObject*> slot = getSlottedObject(arrangementDescriptor);

		if (slot != NULL) {
			slot->destroyObjectFromWorld(true);

			slot->destroyObjectFromDatabase(true);
		}
	}

	transferObject(clothing, 4, false);
	doAnimation("pose_proudly");
	broadcastObject(clothing, true);
	//TODO: Add Chat message from vendor when item is added.

}

void VendorCreatureImplementation::createChildObjects() {
	CreatureObjectImplementation::createChildObjects();

	VendorCreatureTemplate* vendorTempl = dynamic_cast<VendorCreatureTemplate*> (getObjectTemplate());

	if (vendorTempl == NULL)
		return;

	String randomOutfit = vendorTempl->getOutfitName(System::random(vendorTempl->getOutfitsSize() -1));
	if (randomOutfit.isEmpty())
		return;

	Outfit* outfit = VendorOutfitManager::instance()->getOutfit(randomOutfit);

	if (outfit == NULL)
		return;

	String hairFile = vendorTempl->getHairFile(System::random(vendorTempl->getHairSize() - 1));
	SceneObject* hairSlot = getSlottedObject("hair");

	if (hairSlot == NULL && !hairFile.isEmpty()) {
		String hairCustomization;
		ManagedReference<PlayerManager*> pman = getZoneServer()->getPlayerManager();
		TangibleObject* hair = pman->createHairObject(hairFile, hairCustomization);

		if (hair != NULL)
			transferObject(hair, 4);
	}

	Vector<uint32>* clothing = outfit->getClothing();

	for (int i = 0; i < clothing->size(); ++i) {
		ManagedReference<SceneObject*> obj = getZoneServer()->createObject(clothing->get(i), 1);
		if (obj == NULL)
			continue;

		for (int k = 0; k < obj->getArrangementDescriptorSize(); ++k) {
			String arrangementDescriptor = obj->getArrangementDescriptor(k);
			ManagedReference<SceneObject*> slot = getSlottedObject(arrangementDescriptor);
			if (slot != NULL) {
				slot->destroyObjectFromWorld(true);

				slot->destroyObjectFromDatabase(true);
			}
		}

		transferObject(obj, 4);
	}

	// Customization Variables -- TESTING
	//setCustomizationVariable("index_color_skin", 230);
	//setCustomizationVariable("blend_skinny", 0);
	//setCustomizationVariable("blend_fat", (((1 - .5f) / .5f) * 255));

}

void VendorCreatureImplementation::addVendorToMap() {
	VendorManager::instance()->addVendor(getObjectID(), &vendor);
}

void VendorCreatureImplementation::destroyObjectFromDatabase(bool destroyContainedObject) {
	VendorManager::instance()->dropVendor(getObjectID());

	ManagedReference<AuctionManager*> aman = getZoneServer()->getAuctionManager();
	if (aman == NULL)
		return;

	ManagedReference<AuctionsMap*> amap = aman->getAuctionMap();
	if (amap == NULL)
		return;

	amap->decreasePlayerVendorCount(vendor.getOwnerID());

	CreatureObjectImplementation::destroyObjectFromDatabase(destroyContainedObject);
}
