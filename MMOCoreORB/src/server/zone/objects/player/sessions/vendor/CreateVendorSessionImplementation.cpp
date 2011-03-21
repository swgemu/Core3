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

int CreateVendorSessionImplementation::initializeSession() {
	player = NULL;
	vendor = NULL;

	vendorName = "Vendor";
	gender = "male";
	selectedVendorType = 0;

	return 0;
}

void CreateVendorSessionImplementation::initalizeWindow(PlayerCreature* pl) {
	player = pl;
	if (player->hasSuiBoxWindowType(SuiWindowType::STRUCTURE_CREATE_VENDOR)
			|| player->hasSuiBoxWindowType(SuiWindowType::STRUCTURE_NAME_VENDOR)) {

		player->sendSystemMessage("@player_structure:already_creating");
		return;
	}

	if (player == NULL)
		return;

	int hiringMod = player->getSkillMod("hiring");
	String vendorName;

	suiSelectVendor = new SuiListBox(player, SuiWindowType::STRUCTURE_CREATE_VENDOR);

	suiSelectVendor->setPromptTitle("@player_structure:vendor_type_t");
	suiSelectVendor->setPromptText("@player_structure:vendor_type_d");
	suiSelectVendor->setCancelButton(true, "@cancel");

	for (int i = 1; i <= hiringMod; ++i) {
		if (i == 9 || i == 19 || i == 28)
			suiSelectVendor->addMenuItem(VendorType::getVendorStfName(i), i);
	}

	//suiSelectVendor->setUsingObject(structure);

	player->addSuiBox(suiSelectVendor);
	player->sendMessage(suiSelectVendor->generateMessage());
}

void CreateVendorSessionImplementation::handleMenuSelect(byte menuID) {
	int hiringMod = player->getSkillMod("hiring");
	suiSelectVendor->clearOptions();
	suiSelectVendor->removeAllMenuItems();

	if (menuID == VendorType::TERMINAL) {
		suiSelectVendor->setPromptTitle("@player_structure:terminal_type_t");
		suiSelectVendor->setPromptText("@player_structure:terminal_type_d");

		for (int i = 1; i <= hiringMod; ++i) {
			if ((i != 9 && i != 19 && i != 28) && VendorType::isTerminalType(i))
				suiSelectVendor->addMenuItem(VendorType::getVendorStfName(i), i);
		}

		player->sendMessage(suiSelectVendor->generateMessage());
		player->addSuiBox(suiSelectVendor);

	} else if (menuID == VendorType::DROID) {
		suiSelectVendor->setPromptTitle("@player_structure:droid_type_t");
		suiSelectVendor->setPromptText("@player_structure:droid_type_d");
		for (int i = 1; i <= hiringMod; ++i) {
			if (i != 9 && i != 19 && i != 28 && VendorType::isDroidType(i))
				suiSelectVendor->addMenuItem(VendorType::getVendorStfName(i), i);
		}

		player->sendMessage(suiSelectVendor->generateMessage());
		player->addSuiBox(suiSelectVendor);

	} else if (menuID == VendorType::NPC) {
		suiSelectVendor->setPromptTitle("@player_structure:race_type_t");
		suiSelectVendor->setPromptText("@player_structure:race_type_d");
		for (int i = 1; i <= hiringMod; ++i) {
			if ((i != 9 && i != 19 && i != 28) && VendorType::isNpcType(i))
				suiSelectVendor->addMenuItem(VendorType::getVendorStfName(i), i);
		}

		player->sendMessage(suiSelectVendor->generateMessage());
		player->addSuiBox(suiSelectVendor);

	} else if (VendorType::isTerminalType(menuID)) {
		selectedVendorType = menuID;
		SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);

		input->setCancelButton(true, "@cancel");
		input->setPromptTitle("@player_structure:name_t");
		input->setPromptText("@player_structure:name_d");

		player->sendMessage(input->generateMessage());
		player->addSuiBox(input);

	} else if (VendorType::isDroidType(menuID)) {
		selectedVendorType = menuID;
		SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);

		input->setCancelButton(true, "@cancel");
		input->setPromptTitle("@player_structure:name_t");
		input->setPromptText("@player_structure:name_d");

		player->sendMessage(input->generateMessage());
		player->addSuiBox(input);

	} else if (VendorType::isNpcType(menuID)) {
		selectedVendorType = menuID;

		if (VendorType::isMaleOnly(menuID)) {
			gender = "male";
			SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);

			input->setCancelButton(true, "@cancel");
			input->setPromptTitle("@player_structure:name_t");
			input->setPromptText("@player_structure:name_d");

			player->sendMessage(input->generateMessage());
			player->addSuiBox(input);

		} else {
			suiSelectVendor->setPromptTitle("@player_structure:gender_t");
			suiSelectVendor->setPromptText("@player_structure:gender_d");
			suiSelectVendor->addMenuItem("@player_structure:male", VendorType::GENDER_MALE);
			suiSelectVendor->addMenuItem("@player_structure:female", VendorType::GENDER_FEMALE);

			player->sendMessage(suiSelectVendor->generateMessage());
			player->addSuiBox(suiSelectVendor);
		}

	} else if (menuID == VendorType::GENDER_MALE) {
		gender = "male";
		SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);

		input->setCancelButton(true, "@cancel");
		input->setPromptTitle("@player_structure:name_t");
		input->setPromptText("@player_structure:name_d");

		player->sendMessage(input->generateMessage());
		player->addSuiBox(input);

	} else if (menuID == VendorType::GENDER_FEMALE) {
		gender = "female";
		SuiInputBox* input = new SuiInputBox(player, SuiWindowType::STRUCTURE_NAME_VENDOR);

		input->setCancelButton(true, "@cancel");
		input->setPromptTitle("@player_structure:name_t");
		input->setPromptText("@player_structure:name_d");

		player->sendMessage(input->generateMessage());
		player->addSuiBox(input);
	}

	/*
	switch (menuID) {
	case VendorType::TERMINAL: { //Terminal
		suiBox->setPromptTitle("@player_structure:terminal_type_t");
		suiBox->setPromptText("@player_structure:terminal_type_d");
		suiBox->addMenuItem("@player_structure:terminal_bulky", VendorType::TERMINAL_BULKY);
		suiBox->addMenuItem("@player_structure:terminal_fancy", VendorType::TERMINAL_FANCY);
		suiBox->addMenuItem("@player_structure:terminal_slim", VendorType::TERMINAL_SLIM);
		suiBox->addMenuItem("@player_structure:terminal_small", VendorType::TERMINAL_SMALL);
		suiBox->addMenuItem("@player_structure:terminal_standard", VendorType::TERMINAL_STANDARD);

		player->sendMessage(suiBox->generateMessage());
		player->addSuiBox(suiBox);
		break;
	}
	case VendorType::DROID: { //Droids
		suiBox->setPromptTitle("@player_structure:droid_type_t");
		suiBox->setPromptText("@player_structure:droid_type_d");
		suiBox->addMenuItem("@player_structure:droid_bartender", VendorType::DROID_BARTENDER);
		suiBox->addMenuItem("@player_structure:droid_power", VendorType::DROID_POWER);
		suiBox->addMenuItem("@player_structure:droid_protocol", VendorType::DROID_PROTOCOL);
		suiBox->addMenuItem("@player_structure:droid_surgical", VendorType::DROID_SURGICAL);
		suiBox->addMenuItem("@player_structure:droid_wed", VendorType::DROID_WED);

		player->sendMessage(suiBox->generateMessage());
		player->addSuiBox(suiBox);
		break;
	}
	case VendorType::NPC: { // NPC
		suiBox->setPromptTitle("@player_structure:race_type_t");
		suiBox->setPromptText("@player_structure:race_type_d");
		suiBox->addMenuItem("@player_structure:race_aqualish", VendorType::NPC_AQUALISH);
		suiBox->addMenuItem("@player_structure:race_bith", VendorType::NPC_BITH);
		suiBox->addMenuItem("@player_structure:race_bothan", VendorType::NPC_BOTHAN);
		suiBox->addMenuItem("@player_structure:race_devaronian", VendorType::NPC_DEVARONIAN);
		suiBox->addMenuItem("@player_structure:race_gran", VendorType::NPC_GRAN);
		suiBox->addMenuItem("@player_structure:race_human", VendorType::NPC_HUMAN);
		suiBox->addMenuItem("@player_structure:race_ishi_tib", VendorType::NPC_ISHI);
		suiBox->addMenuItem("@player_structure:race_ithorian", VendorType::NPC_ITHORIAN);
		suiBox->addMenuItem("@player_structure:race_moncal", VendorType::NPC_MONCAL);
		suiBox->addMenuItem("@player_structure:race_nikto", VendorType::NPC_NIKTO);
		suiBox->addMenuItem("@player_structure:race_quarren", VendorType::NPC_QUARREN);
		suiBox->addMenuItem("@player_structure:race_random", VendorType::NPC_RANDOM);
		suiBox->addMenuItem("@player_structure:race_rodian", VendorType::NPC_RODIAN);
		suiBox->addMenuItem("@player_structure:race_sullustan", VendorType::NPC_SULLUSTAN);
		suiBox->addMenuItem("@player_structure:race_trandoshan", VendorType::NPC_TRANDOSHAN);
		suiBox->addMenuItem("@player_structure:race_twilek", VendorType::NPC_TWILEK);
		suiBox->addMenuItem("@player_structure:race_weequay", VendorType::NPC_WEEQUAY);
		suiBox->addMenuItem("@player_structure:race_wookiee", VendorType::NPC_WOOKIEE);
		suiBox->addMenuItem("@player_structure:race_zabrak", VendorType::NPC_ZABRAK);

		player->sendMessage(suiBox->generateMessage());
		player->addSuiBox(suiBox);
		break;
	}

	// Vendor Selection
	}*/

}

void CreateVendorSessionImplementation::handleNameVendor(String& name) {
	if (selectedVendorType == 0)
		return;

	vendorName = name;
	if (VendorType::isTerminalType(selectedVendorType) || VendorType::isDroidType(selectedVendorType))
		createTerminalDroidVendor(selectedVendorType);

	else if (VendorType::isNpcType(selectedVendorType))
		createNpcVendor();

}

void CreateVendorSessionImplementation::createTerminalDroidVendor(int vendorType) {
	uint32 vendorTemplateCRC = String("object/tangible/vendor/" + VendorType::getVendorTypeName(vendorType) + ".iff").hashCode();
	vendor = player->getZoneServer()->createObject(vendorTemplateCRC);

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (vendor == NULL || inventory == NULL || !vendor->isVendor())
		return;

	ManagedReference<VendorTerminal*> terminal = (VendorTerminal*) vendor.get();

	Locker inventoryLocker(inventory);

	terminal->setOwnerID(player->getObjectID());
	terminal->setCustomObjectName("Vendor: " + vendorName, false);

	inventory->addObject(terminal, -1);
	terminal->sendTo(player, true);

	cancelSession();

}

void CreateVendorSessionImplementation::createNpcVendor() {
	//player->sendSystemMessage("Still being implemented. Please do not report bugs regarding NPC Vendors.");
	//return;

	uint32 vendorTemplateCRC = String("object/mobile/vendor/" + VendorType::getVendorTypeName(selectedVendorType) + "_" + gender + ".iff").hashCode();
	vendor = player->getZoneServer()->createObject(vendorTemplateCRC);

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (vendor == NULL || inventory == NULL || !vendor->isVendor())
		return;

	ManagedReference<VendorCreature*> creature = (VendorCreature*) vendor.get();

	Locker inventoryLocker(inventory);

	creature->setOwnerID(player->getObjectID());
	creature->setCustomObjectName("Vendor: " + vendorName, false);

	inventory->addObject(creature, -1);
	creature->sendTo(player, true);

}
