/*
 * CreateVendorSessionImplementation.cpp
 *
 *  Created on: May 20, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/player/sessions/vendor/CreateVendorSession.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/vendor/VendorSelectionNode.h"
#include "server/zone/objects/player/sessions/vendor/sui/CreateVendorSuiCallback.h"
#include "server/zone/objects/player/sessions/vendor/sui/NameVendorSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/transaction/TransactionLog.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

int CreateVendorSessionImplementation::initializeSession() {
	ManagedReference<CreatureObject*> player = this->player.get();

	if (player == nullptr)
		return 0;

	if (player->containsActiveSession(SessionFacadeType::CREATEVENDOR)) {
		player->sendSystemMessage("@player_structure:already_creating"); // You are already creating a vendor.
		return 0;

	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		cancelSession();
		return 0;
	}

	if (ghost->getVendorCount() >= player->getSkillMod("manage_vendor")) {
		player->sendSystemMessage("@player_structure:full_vendors"); // You are already managing your maximum number of vendors. Fire someone or remove a terminal first!
		cancelSession();
		return 0;
	}

	const SortedVector<unsigned long long>* ownedVendors = ghost->getOwnedVendors();
	for (int i = 0; i < ownedVendors->size(); i++) {
		ManagedReference<SceneObject*> vendor = player->getZoneServer()->getObject(ownedVendors->elementAt(i));

		if (vendor == nullptr)
			continue;

		DataObjectComponentReference* data = vendor->getDataObjectComponent();
		if(data == nullptr || data->get() == nullptr || !data->get()->isVendorData())
			continue;

		VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
		if(vendorData == nullptr)
			continue;

		if (!vendorData->isInitialized()) {
			player->sendSystemMessage("@player_structure:already_creating"); // You are already creating a vendor.
			cancelSession();
			return 0;
		}
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

	player->addActiveSession(SessionFacadeType::CREATEVENDOR, _this.getReferenceUnsafeStaticCast());

	return 0;
}

void CreateVendorSessionImplementation::handleVendorSelection(byte menuID) {
	ManagedReference<CreatureObject*> player = this->player.get();

	if (player == nullptr)
		return;

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

		/// If there are selections available for vendors
		if(suiSelectVendor->getMenuSize() != 0) {
			player->sendMessage(suiSelectVendor->generateMessage());
			player->getPlayerObject()->addSuiBox(suiSelectVendor);
			return;
		}

		templatePath = templatePath + node->getRandomTemplate(hiringMod);
		const char* path = templatePath.toCharArray();
		if (path[strlen(path) - 1] == '_')
			templatePath = templatePath + (System::random(1) == 0 ? "male.iff" : "female.iff");
	}
	SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);
	input->setCallback(new NameVendorSuiCallback(player->getZoneServer()));
	input->setCancelButton(true, "@cancel");
	input->setPromptTitle("@player_structure:name_t");
	input->setPromptText("@player_structure:name_d");

	player->sendMessage(input->generateMessage());
	player->getPlayerObject()->addSuiBox(input);

}

void CreateVendorSessionImplementation::createVendor(String& name) {
	ManagedReference<CreatureObject*> player = this->player.get();

	if (player == nullptr) {
		return;
	}

	Locker locker(player);

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr) {
		cancelSession();
		return;
	}

	if (!VendorManager::instance()->isValidVendorName(name)) {
		player->sendSystemMessage("@player_structure:obscene");
		SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);
		input->setCallback(new NameVendorSuiCallback(zoneServer));
		input->setCancelButton(true, "@cancel");
		input->setPromptTitle("@player_structure:name_t");
		input->setPromptText("@player_structure:name_d");

		player->sendMessage(input->generateMessage());
		player->getPlayerObject()->addSuiBox(input);
		return;
	}

	ManagedReference<SceneObject*> inventory = player->getInventory();

	if (inventory == nullptr) {
		cancelSession();
		return;
	}

	ManagedReference<TangibleObject*> vendor = nullptr;

	try {
		vendor = (zoneServer->createObject(templatePath.hashCode())).castTo<TangibleObject*>();
	} catch (Exception& e) {
		error(e.getMessage());
	}

	if (vendor == nullptr) {
		error() << "createVendor - Failed to create Vendor Template: " << templatePath;
		cancelSession();
		return;
	}

	Locker clocker(vendor, player);

	if (!vendor->isVendor()) {
		error() << "createVendor - Tangible Object is not a Vendor! Template: " << templatePath;

		vendor->destroyObjectFromDatabase(true);
		cancelSession();

		return;
	}

	vendor->createChildObjects();

	if (inventory->isContainerFullRecursive()) {
		player->sendSystemMessage("@player_structure:create_failed");
		vendor->destroyObjectFromDatabase(true);
		cancelSession();
		return;
	}

	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data == nullptr || data->get() == nullptr || !data->get()->isVendorData()) {
		error("Invalid vendor, no data component: " + templatePath);
		player->sendSystemMessage("@player_structure:create_failed");
		vendor->destroyObjectFromDatabase(true);
		cancelSession();
		return;
	}

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
	if(vendorData == nullptr) {
		error("Invalid vendor, no data component: " + templatePath);
		player->sendSystemMessage("@player_structure:create_failed");
		vendor->destroyObjectFromDatabase(true);
		cancelSession();
		return ;
	}

	vendorData->setOwnerId(player->getObjectID());

	vendor->setCustomObjectName("Vendor: " + name, false);
	vendor->setContainerOwnerID(player->getObjectID());

	vendor->setMaxCondition(1000, false);
	vendor->setConditionDamage(0, false);

	if (vendor->isCreatureObject()) {
		VendorManager::instance()->randomizeVendorLooks(cast<CreatureObject*>(vendor.get()));
	}

	TransactionLog trx(TrxCode::VENDORLIFECYCLE, player, vendor);

	if(!inventory->transferObject(vendor, -1, false)) {
		trx.abort() << "transferObject failed.";
		player->sendSystemMessage("@player_structure:create_failed");
		vendor->destroyObjectFromDatabase(true);
		cancelSession();
		return;
	}

	inventory->broadcastObject(vendor, true);
	player->getPlayerObject()->addVendor(vendor);

	player->sendSystemMessage("@player_structure:create_success");
	cancelSession();
}
