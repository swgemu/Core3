/*
 * VendorManager.cpp
 *
 *  Created on: Mar 23, 2011
 *      Author: polonel
 */

#include "VendorManager.h"
#include "VendorSelectionNode.h"
#include "server/zone/managers/vendor/sui/DestroyVendorSuiCallback.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/auction/Vendor.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/managers/vendor/sui/RenameVendorSuiCallback.h"

#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"
#include "server/zone/managers/planet/PlanetManager.h"

VendorManager::VendorManager() {
	setLoggingName("VendorManager");

}

void VendorManager::loadLuaVendors() {
	info("Loading Vendor Options...");

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/vendor_manager.lua");

	LuaObject menu = lua->getGlobalObject("VendorMenu");

	rootNode.parseFromLua(menu);

	menu.pop();

}

void VendorManager::handleDisplayStatus(PlayerCreature* player, Vendor* vendor) {
	uint32 itemsForSaleCount = 0;

	ManagedReference<SuiListBox*> statusBox = new SuiListBox(player, SuiWindowType::STRUCTURE_VENDOR_STATUS);
	statusBox->setUsingObject(vendor->getVendor());
	statusBox->setPromptTitle("@player_structure:vendor_status");
	statusBox->setPromptText("Vendor Status");

	//TODO: Fix this to pull off the real condition of the vendor
	statusBox->addMenuItem("Condition: 100%");

	VectorMap<uint64, ManagedReference<AuctionItem*> >* vendorItems = vendor->getVendorItems();

	for (int i = 0; i < vendorItems->size(); ++i) {
		AuctionItem* item = vendorItems->get(i);
		if (!item->isOfferToVendor() && !item->isInStockroom() && !item->isSold())
			itemsForSaleCount++;

	}
	statusBox->addMenuItem("Number of Items For Sale: " + String::valueOf(itemsForSaleCount));

	if (vendor->isVendorSearchEnabled())
		statusBox->addMenuItem("@player_structure:vendor_search_enabled");
	else
		statusBox->addMenuItem("@player_structure:vendor_search_disabled");

	statusBox->addMenuItem("\\#32CD32Vendor Operating Normally\\#.");

	player->addSuiBox(statusBox);
	player->sendMessage(statusBox->generateMessage());

}

void VendorManager::sendDestoryTo(PlayerCreature* player, Vendor* vendor) {
	if (vendor->getOwnerID() != player->getObjectID())
		return;

	SuiMessageBox* destroyBox = new SuiMessageBox(player, SuiWindowType::STRUCTURE_DESTROY_VENDOR_CONFIRM);
	destroyBox->setCallback(new DestroyVendorSuiCallback(player->getZoneServer()));
	destroyBox->setUsingObject(vendor->getVendor());
	destroyBox->setPromptTitle("@player_structure:destroy_vendor_t"); //DestroyVendor?
	destroyBox->setPromptText("@player_structure:destroy_vendor_d");
	destroyBox->setOkButton(true, "@yes");
	destroyBox->setCancelButton(true, "@no");

	player->addSuiBox(destroyBox);
	player->sendMessage(destroyBox->generateMessage());

}

void VendorManager::sendRenameVendorTo(PlayerCreature* player, TangibleObject* vendor) {
	SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);
	input->setCallback(new RenameVendorSuiCallback(player->getZoneServer()));
	input->setUsingObject(vendor);
	input->setCancelButton(true, "@cancel");
	input->setPromptTitle("@player_structure:name_t");
	input->setPromptText("@player_structure:name_d");

	player->sendMessage(input->generateMessage());
	player->addSuiBox(input);
}

void VendorManager::handleDestoryCallback(PlayerCreature* player, Vendor* vendor) {
	ManagedReference<SceneObject*> vendorObj= vendor->getVendor();

	if (vendorObj == NULL)
		return;

	vendorObj->removeFromZone();
	vendorObj->destroyObjectFromDatabase(true);

}

void VendorManager::handleRegisterVendor(PlayerCreature* player, Vendor* vendor) {

}

void VendorManager::handleRenameVendor(TangibleObject* vendor, String& name) {
	if (vendor == NULL)
		return;

	Locker _locker(vendor);

	vendor->setCustomObjectName("Vendor: " + name, true);

	_locker.release();

	Vendor* vendo = NULL;
	if (vendor->isTerminal()) {
		VendorTerminal* terminal = dynamic_cast<VendorTerminal*>(vendor);
		vendo = terminal->getVendor();
	} else if (vendor->isCreatureObject()) {
		VendorCreature* vendorCreature = dynamic_cast<VendorCreature*>(vendor);
		vendo = vendorCreature->getVendor();
	}

	if (vendo == NULL)
		return;

	vendo->setRegistered(false);
	//TODO: unregister from the planetary map.

}
