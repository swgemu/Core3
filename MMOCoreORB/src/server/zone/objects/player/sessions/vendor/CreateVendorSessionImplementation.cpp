/*
 * CreateVendorSessionImplementation.cpp
 *
 *  Created on: May 20, 2012
 *      Author: Kyle
 */

#include "CreateVendorSession.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/player/PlayerManager.h"

#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/vendor/VendorSelectionNode.h"
#include "server/zone/objects/player/sessions/vendor/sui/CreateVendorSuiCallback.h"
#include "server/zone/objects/player/sessions/vendor/sui/NameVendorSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/templates/tangible/VendorCreatureTemplate.h"
#include "server/zone/templates/customization/AssetCustomizationManagerTemplate.h"


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

	ManagedReference<TangibleObject*> vendor = cast<TangibleObject*>(player->getZoneServer()->createObject(templatePath.hashCode()));

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (vendor == NULL || inventory == NULL || !vendor->isVendor()) {
		cancelSession();
		return;
	}

	vendor->createChildObjects();

	Locker inventoryLocker(inventory);

	if (inventory->hasFullContainerObjects()) {
		player->sendSystemMessage("@player_structure:create_failed");
		cancelSession();
		return;
	}

	DataObjectComponentReference* data = vendor->getDataObjectComponent();
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

	vendor->setCustomObjectName("Vendor: " + name, false);
	vendor->setContainerOwnerID(player->getObjectID());

	if(vendor->isCreatureObject()) {
		randomizeVendorLooks(cast<CreatureObject*>(vendor.get()));
	}

	if(!inventory->transferObject(vendor, -1, false)) {
		player->sendSystemMessage("@player_structure:create_failed");
		cancelSession();
		return;
	}

	inventory->broadcastObject(vendor, true);
	player->getPlayerObject()->addVendor(vendor);

	player->sendSystemMessage("@player_structure:create_success");
	cancelSession();
}

void CreateVendorSessionImplementation::randomizeVendorLooks(CreatureObject* vendor) {

	VendorCreatureTemplate* vendorTempl = dynamic_cast<VendorCreatureTemplate*> (vendor->getObjectTemplate());

	if (vendorTempl == NULL)
		return;

	String randomOutfit = vendorTempl->getOutfitName(System::random(vendorTempl->getOutfitsSize() -1));
	if (randomOutfit.isEmpty())
		return;

	Reference<Outfit*> outfit = VendorOutfitManager::instance()->getOutfit(randomOutfit);

	if (outfit == NULL)
		return;

	String hairFile = vendorTempl->getHairFile(System::random(vendorTempl->getHairSize() - 1));
	ManagedReference<SceneObject*> hairSlot = vendor->getSlottedObject("hair");

	if (hairSlot == NULL && !hairFile.isEmpty()) {
		String hairCustomization;
		ManagedReference<PlayerManager*> pman = player->getZoneServer()->getPlayerManager();
		TangibleObject* hair = pman->createHairObject(hairFile, hairCustomization);

		if (hair != NULL)
			vendor->transferObject(hair, 4);
	}

	Vector<uint32>* clothing = outfit->getClothing();

	for (int i = 0; i < clothing->size(); ++i) {
		ManagedReference<SceneObject*> obj = player->getZoneServer()->createObject(clothing->get(i), 1);
		if (obj == NULL)
			continue;

		for (int k = 0; k < obj->getArrangementDescriptorSize(); ++k) {
			String arrangementDescriptor = obj->getArrangementDescriptor(k);
			ManagedReference<SceneObject*> slot = vendor->getSlottedObject(arrangementDescriptor);
			if (slot != NULL) {
				slot->destroyObjectFromWorld(true);

				slot->destroyObjectFromDatabase(true);
			}
		}

		vendor->transferObject(obj, 4);
	}

//	VectorMap<String, Reference<CustomizationVariable*> > variables;
//
//	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(vendorTempl->getAppearanceFilename().hashCode(), variables, true);
//	Reference<RangedIntCustomizationVariable*> color = cast<RangedIntCustomizationVariable*>(variables.get("index_color_skin"));
//	Reference<RangedIntCustomizationVariable*> skinny = cast<RangedIntCustomizationVariable*>(variables.get("blend_skinny"));
//	Reference<RangedIntCustomizationVariable*> fat = cast<RangedIntCustomizationVariable*>(variables.get("blend_fat"));
//
//	if(color != NULL) {
//		int value = color->g
//	}
//
//	// Customization Variables -- TESTING
//	vendor->setCustomizationVariable("index_color_skin", 230);
//	vendor->setCustomizationVariable("blend_skinny", 0);
//	vendor->setCustomizationVariable("blend_fat", (((1 - .5f) / .5f) * 255));
}
