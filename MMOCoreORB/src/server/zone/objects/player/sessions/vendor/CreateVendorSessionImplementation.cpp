/*
 * CreateVendorSessionImplementation.cpp
 *
 *  Created on: May 20, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/player/sessions/vendor/CreateVendorSession.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/managers/auction/AuctionManager.h"

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
		player->sendSystemMessage("@player_structure:already_creating"); // You are already creating a vendor.
		return 0;

	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == NULL) {
		cancelSession();
		return 0;
	}

	if (ghost->getVendorCount() >= player->getSkillMod("manage_vendor")) {
		player->sendSystemMessage("@player_structure:full_vendors"); // You are already managing your maximum number of vendors. Fire someone or remove a terminal first!
		cancelSession();
		return 0;
	}

	SortedVector<unsigned long long>* ownedVendors = ghost->getOwnedVendors();
	for (int i = 0; i < ownedVendors->size(); i++) {
		ManagedReference<SceneObject*> vendor = player->getZoneServer()->getObject(ownedVendors->elementAt(i));

		if (vendor == NULL)
			continue;

		DataObjectComponentReference* data = vendor->getDataObjectComponent();
		if(data == NULL || data->get() == NULL || !data->get()->isVendorData())
			continue;

		VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
		if(vendorData == NULL)
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

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	if (inventory == NULL) {
		cancelSession();
		return;
	}

	ManagedReference<TangibleObject*> vendor;

	try {
		vendor = (player->getZoneServer()->createObject(templatePath.hashCode())).castTo<TangibleObject*>();
	} catch (Exception& e) {
		error(e.getMessage());
	}

	if (vendor == NULL) {
		error("could not create vendor " + templatePath);
		cancelSession();
		return;
	}

	if (!vendor->isVendor()) {
		error("could not create vendor " + templatePath);
		vendor->destroyObjectFromDatabase(true);
		cancelSession();
		return;
	}

	vendor->createChildObjects();

	Locker inventoryLocker(inventory);

	if (inventory->hasFullContainerObjects()) {
		player->sendSystemMessage("@player_structure:create_failed");
		vendor->destroyObjectFromDatabase(true);
		cancelSession();
		return;
	}

	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
		error("Invalid vendor, no data component: " + templatePath);
		player->sendSystemMessage("@player_structure:create_failed");
		vendor->destroyObjectFromDatabase(true);
		cancelSession();
		return;
	}

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
	if(vendorData == NULL) {
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

	if(vendor->isCreatureObject()) {
		randomizeVendorLooks(cast<CreatureObject*>(vendor.get()));
	}

	if(!inventory->transferObject(vendor, -1, false)) {
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

void CreateVendorSessionImplementation::randomizeVendorLooks(CreatureObject* vendor) {

	VendorCreatureTemplate* vendorTempl = dynamic_cast<VendorCreatureTemplate*> (vendor->getObjectTemplate());
	if (vendorTempl == NULL)
		return;

	randomizeVendorClothing( vendor, vendorTempl );
	randomizeVendorHair( vendor, vendorTempl );
	randomizeVendorFeatures( vendor, vendorTempl );
	randomizeVendorHeight( vendor, vendorTempl );

}

void CreateVendorSessionImplementation::randomizeVendorClothing(CreatureObject* vendor, VendorCreatureTemplate* vendorTempl) {

	String randomOutfit = vendorTempl->getOutfitName(System::random(vendorTempl->getOutfitsSize() -1));
	if (randomOutfit.isEmpty())
		return;

	Reference<Outfit*> outfit = VendorOutfitManager::instance()->getOutfit(randomOutfit);
	if (outfit == NULL)
		return;

	Vector<uint32>* clothing = outfit->getClothing();

	for (int i = 0; i < clothing->size(); ++i) {
		ManagedReference<SceneObject*> obj = player->getZoneServer()->createObject(clothing->get(i), 1);
		if (obj == NULL)
			continue;

		for (int j = 0; j < obj->getArrangementDescriptorSize(); ++j) {
			Vector<String> descriptors = obj->getArrangementDescriptor(j);

			for (int k = 0; k < descriptors.size(); ++k) {
				ManagedReference<SceneObject*> slot = vendor->getSlottedObject(descriptors.get(k));

				if (slot != NULL) {
					slot->destroyObjectFromWorld(true);
					slot->destroyObjectFromDatabase(true);
				}
			}
		}

		if (!vendor->transferObject(obj, 4)) {
			obj->destroyObjectFromDatabase(true);
		}
	}

}

void CreateVendorSessionImplementation::randomizeVendorHair(CreatureObject* vendor, VendorCreatureTemplate* vendorTempl) {

	String hairFile = vendorTempl->getHairFile(System::random(vendorTempl->getHairSize() - 1));
	ManagedReference<SceneObject*> hairSlot = vendor->getSlottedObject("hair");

	if (hairSlot == NULL && !hairFile.isEmpty()) {

		Reference<TangibleObject*> hair = player->getZoneServer()->createObject(hairFile.hashCode(), 1).castTo<TangibleObject*>();

		if (hair != NULL) {
			if (hair->getGameObjectType() != SceneObjectType::GENERICITEM || hair->getArrangementDescriptor(0).get(0) != "hair") {
				hair->destroyObjectFromDatabase(true);
				return;
			}

			//TODO: randomize hair customization

			if (!vendor->transferObject(hair, 4)) {
				hair->destroyObjectFromDatabase(true);
			}
		}
	}

}

void CreateVendorSessionImplementation::randomizeVendorFeatures(CreatureObject* vendor, VendorCreatureTemplate* vendorTempl) {

	// Randomize Configured Customization Variables
	for( int i = 0; i < vendorTempl->getCustomizationStringNamesSize(); i++ ){
		String customizationStringName = vendorTempl->getCustomizationStringName(i);

		if( i >= vendorTempl->getCustomizationValuesSize() )
			continue;

		Vector<int> values = vendorTempl->getCustomizationValues(i);
		if( values.isEmpty() )
			continue;

		// Select random value from array
		int randomValue = values.get(System::random(values.size() - 1));

		// Some customization strings are mutually exclusive pairs of names separated by
		// a comma.  Client expects only one of those names to be non-zero.  The other
		// should be zero.  Randomly choose which one to give a value from the values array
		int idx = customizationStringName.indexOf( ',' );
		if( idx >= 0 ){
			String customizationStringName1 = customizationStringName.subString( 0, idx );
			String customizationStringName2 = customizationStringName.subString( idx+1 );
			if( System::random(1) == 1 ){
				vendor->setCustomizationVariable( customizationStringName1, randomValue, false );
				vendor->setCustomizationVariable( customizationStringName2, 0, false );
			}
			else{
				vendor->setCustomizationVariable( customizationStringName1, 0, false );
				vendor->setCustomizationVariable( customizationStringName2, randomValue, false );
			}

		}
		else{
			// Set single variable
			vendor->setCustomizationVariable( customizationStringName, randomValue, false );
		}
	} // foreach customizationStringName
}

void CreateVendorSessionImplementation::randomizeVendorHeight(CreatureObject* vendor, VendorCreatureTemplate* vendorTempl) {

	// minScale/maxScale are floats with two significant digits past the decimal
	int minScale = vendorTempl->getMinScale()*100;
	int maxScale = vendorTempl->getMaxScale()*100;
	int heightMod = System::random( maxScale - minScale );

	float height = (minScale + heightMod)/100.0;
	vendor->setHeight( height, false );
}
