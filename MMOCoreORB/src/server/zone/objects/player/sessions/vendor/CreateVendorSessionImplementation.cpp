/*
 * CreateVendorSessionImplementation.cpp
 *
 *  Created on: May 20, 2012
 *      Author: Kyle
 */

#include "CreateVendorSession.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/vendor/VendorSelectionNode.h"
#include "server/zone/objects/player/sessions/vendor/sui/CreateVendorSuiCallback.h"
#include "server/zone/objects/player/sessions/vendor/sui/NameVendorSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

int CreateVendorSessionImplementation::initializeSession() {

	ManagedReference<CreatureObject*> player = this->player.get();

	if (player == NULL)
		return 0;

	if (player->containsActiveSession(SessionFacadeType::CREATEVENDOR)) {
		player->sendSystemMessage("@player_structure:already_creating");
		return 0;

	}

	if (player->getPlayerObject()->getVendorCount() >= player->getSkillMod("manage_vendor")) {
		player->sendSystemMessage("@player_structure:full_vendors");
		cancelSession();
		return 0;
	}

	currentNode = VendorManager::instance()->getRootNode();
	templatePath = "";

	if (!currentNode->hasChildNode()) {
		cancelSession();
		error("Vendor Root node has no children");
		return 0;
	}

	int hiringMod = player->getSkillMod("hiring");

	suiSelectVendor = new SuiListBox(player, SuiWindowType::STRUCTURE_CREATE_VENDOR);
	suiSelectVendor->setCallback(new CreateVendorSuiCallback(player->getZoneServer()));
	suiSelectVendor->setCancelButton(true, "@cancel");

	suiSelectVendor->setPromptTitle(currentNode->getSuiDisplay() + "t");
	suiSelectVendor->setPromptText(currentNode->getSuiDisplay() + "d");

	currentNode->addChildrenToListBox(suiSelectVendor, hiringMod);

	player->getPlayerObject()->addSuiBox(suiSelectVendor);
	player->sendMessage(suiSelectVendor->generateMessage());

	player->addActiveSession(SessionFacadeType::CREATEVENDOR, _this.get());

	return 0;
}

void CreateVendorSessionImplementation::handleVendorSelection(byte menuID) {
	ManagedReference<CreatureObject*> player = this->player.get();

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
		player->getPlayerObject()->addSuiBox(suiSelectVendor);

	} else {
		SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);
		input->setCallback(new NameVendorSuiCallback(player->getZoneServer()));
		input->setCancelButton(true, "@cancel");
		input->setPromptTitle("@player_structure:name_t");
		input->setPromptText("@player_structure:name_d");

		player->sendMessage(input->generateMessage());
		player->getPlayerObject()->addSuiBox(input);
	}
}

void CreateVendorSessionImplementation::createVendor(String& name) {
	ManagedReference<CreatureObject*> player = this->player.get();

	if (!VendorManager::instance()->isValidVendorName(name)) {
		player->sendSystemMessage("@player_structure:obscene");
		SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);
		input->setCallback(new NameVendorSuiCallback(player->getZoneServer()));
		input->setCancelButton(true, "@cancel");
		input->setPromptTitle("@player_structure:name_t");
		input->setPromptText("@player_structure:name_d");

		player->sendMessage(input->generateMessage());
		player->getPlayerObject()->addSuiBox(input);
		return;
	}

	vendor = cast<TangibleObject*>(player->getZoneServer()->createObject(templatePath.hashCode()));

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (vendor == NULL || inventory == NULL || !vendor.get()->isVendor()) {
		cancelSession();
		return;
	}

	vendor.get()->createChildObjects();

	Locker inventoryLocker(inventory);

	if (inventory->hasFullContainerObjects()) {
		player->sendSystemMessage("@player_structure:create_failed");
		cancelSession();
		return;
	}

	DataObjectComponentReference* data = vendor.get()->getDataObjectComponent();
	if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
		error("Invalid vendor, no data component: " + templatePath);
		player->sendSystemMessage("@player_structure:create_failed");
		cancelSession();
		return;
	}

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
	if(vendorData == NULL) {
		error("Invalid vendor, no data component: " + templatePath);
		player->sendSystemMessage("@player_structure:create_failed");
		cancelSession();
		return ;
	}

	vendorData->setOwnerId(player->getObjectID());
	vendorData->setVendor(vendor.get());

	vendor.get()->setCustomObjectName("Vendor: " + name, false);
	vendor.get()->setContainerOwnerID(player->getObjectID());

	if(!inventory->transferObject(vendor.get(), -1, false)) {
		player->sendSystemMessage("@player_structure:create_failed");
		cancelSession();
		return;
	}

	inventory->broadcastObject(vendor.get(), true);
	player->getPlayerObject()->addVendor(vendor.get());

	player->sendSystemMessage("@player_structure:create_success");
	cancelSession();
}
