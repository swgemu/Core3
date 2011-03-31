/*
 * CreateVendorSessionImplementation.cpp
 *
 *  Created on: Mar 20, 2011
 *      Author: polonel
 */

#include "CreateVendorSession.h"
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/vendor/VendorSelectionNode.h"
#include "server/zone/objects/player/sessions/vendor/sui/CreateVendorSuiCallback.h"
#include "server/zone/objects/player/sessions/vendor/sui/NameVendorSuiCallback.h"

#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"

int CreateVendorSessionImplementation::initializeSession() {
	player = NULL;
	vendor = NULL;
	currentNode = NULL;
	suiSelectVendor = NULL;
	suiNameVendor = NULL;

	templatePath = "";

	return 0;
}

void CreateVendorSessionImplementation::initalizeWindow(PlayerCreature* pl) {
	player = pl;

	if (player == NULL)
			return;

	if (player->containsActiveSession(SessionFacadeType::CREATEVENDOR)) {
		player->sendSystemMessage("@player_structure:already_creating");
		return;
	}

	ManagedReference<AuctionManager*> aman = player->getZoneServer()->getAuctionManager();

	if (aman == NULL)
		return;

	ManagedReference<AuctionsMap*> amap = aman->getAuctionMap();

	if (amap == NULL)
		return;

	if (amap->getPlayerVendorCount(player->getObjectID()) >= player->getSkillMod("manage_vendor")) {
		player->sendSystemMessage("@player_structure:full_vendors");
		return;
	}

	currentNode = VendorManager::instance()->getRootNode();

	if (!currentNode->hasChildNode())
		return;

	int hiringMod = player->getSkillMod("hiring");

	suiSelectVendor = new SuiListBox(player, SuiWindowType::STRUCTURE_CREATE_VENDOR);
	suiSelectVendor->setCallback(new CreateVendorSuiCallback(player->getZoneServer()));
	suiSelectVendor->setCancelButton(true, "@cancel");

	suiSelectVendor->setPromptTitle(currentNode->getSuiDisplay() + "t");
	suiSelectVendor->setPromptText(currentNode->getSuiDisplay() + "d");

	currentNode->addChildrenToListBox(suiSelectVendor, hiringMod);

	player->addSuiBox(suiSelectVendor);
	player->sendMessage(suiSelectVendor->generateMessage());

	player->addActiveSession(SessionFacadeType::CREATEVENDOR, _this);
}

void CreateVendorSessionImplementation::handleMenuSelect(byte menuID) {
	int hiringMod = player->getSkillMod("hiring");
	suiSelectVendor->clearOptions();
	suiSelectVendor->removeAllMenuItems();

	VendorSelectionNode* node = currentNode->getNode(menuID);

	// Set the title and text off the parent node.
	suiSelectVendor->setPromptTitle(node->getSuiDisplay() + "t");
	suiSelectVendor->setPromptText(node->getSuiDisplay()+ "d");
	templatePath = templatePath + node->getTemplatePath();

	if (node->hasChildNode()) {
		currentNode = node;
		node->addChildrenToListBox(suiSelectVendor, hiringMod);
		player->sendMessage(suiSelectVendor->generateMessage());
		player->addSuiBox(suiSelectVendor);

	} else {
		SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);
		input->setCallback(new NameVendorSuiCallback(player->getZoneServer()));
		input->setCancelButton(true, "@cancel");
		input->setPromptTitle("@player_structure:name_t");
		input->setPromptText("@player_structure:name_d");

		player->sendMessage(input->generateMessage());
		player->addSuiBox(input);
	}
}

void CreateVendorSessionImplementation::createVendor(String& name) {
	vendor = player->getZoneServer()->createObject(templatePath.hashCode());

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (vendor == NULL || inventory == NULL || !vendor->isVendor()) {
		cancelSession();
		return;
	}

	Locker inventoryLocker(inventory);

	if (vendor->isTerminal()) {
		VendorTerminal* vendorTerminal = dynamic_cast<VendorTerminal*>(vendor.get());
		vendorTerminal->setOwnerID(player->getObjectID());
	} else if (vendor->isCreatureObject()) {
		VendorCreature* vendorCreature = dynamic_cast<VendorCreature*>(vendor.get());
		vendorCreature->setOwnerID(player->getObjectID());
	} else {
		player->sendSystemMessage("Invalid vendor object during createVendor()");
		return;
	}

	ManagedReference<AuctionManager*> aman = player->getZoneServer()->getAuctionManager();

	if (aman == NULL) {
		cancelSession();
		return;
	}

	ManagedReference<AuctionsMap*> amap = aman->getAuctionMap();

	if (amap == NULL) {
		cancelSession();
		return;
	}

	amap->increasePlayerVendorCount(player->getObjectID());

	vendor->setCustomObjectName("Vendor: " + name, true);

	inventory->addObject(vendor, -1);
	vendor->sendTo(player, true);

	player->sendSystemMessage("@player_structure:create_success");
	cancelSession();

}
