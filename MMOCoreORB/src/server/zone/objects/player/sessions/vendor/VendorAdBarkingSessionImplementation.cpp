/*
 * CreateVendorSessionImplementation.cpp
 *
 *  Created on: May 20, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/player/sessions/vendor/VendorAdBarkingSession.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/callbacks/AdBarkingPhraseSuiCallback.h"

int VendorAdBarkingSessionImplementation::initializeSession() {

	ManagedReference<CreatureObject*> player = this->owner.get();

	if (player == NULL)
		return 0;

	advertisingMod = player->getSkillMod("advertising");

	owner->addActiveSession(SessionFacadeType::VENDORADBARKING, _this.get());

	sendPhraseOptions();

	return 0;
}

void VendorAdBarkingSessionImplementation::sendPhraseOptions() {

	if(owner == NULL || vendor == NULL) {
		cancelSession();
		return;
	}

	ManagedReference<SuiListBox*> phrases = new SuiListBox(owner, SuiWindowType::VENDOR_PHRASES);
	phrases->setPromptTitle("@player_structure:vendor_strcats_t"); //Select Phrase Category
	phrases->setPromptText("@player_structure:vendor_strcats_d"); //Select the type of phrase for the vendor to bark. If you have "Advanced Vocalization" an option to customize the advertisement will appear on the list.
	phrases->setUsingObject(vendor);
	phrases->setOkButton(true, "@ok");
	phrases->setCancelButton(true, "@cancel");
	phrases->setCallback(new AdBarkingPhraseSuiCallback(owner->getZoneServer()));

	if(owner->hasSkill("crafting_merchant_advertising_02"))
		phrases->addMenuItem("Customize", 0);

	phrases->addMenuItem("@map_loc_cat_n:vendor_armor", 1);
	phrases->addMenuItem("@map_loc_cat_n:vendor_clothing", 2);
	phrases->addMenuItem("@map_loc_cat_n:vendor_components", 3);
	phrases->addMenuItem("@map_loc_cat_n:vendor_droids", 4);
	phrases->addMenuItem("@map_loc_cat_n:vendor_equipment", 5);
	phrases->addMenuItem("@map_loc_cat_n:vendor_food", 6);
	phrases->addMenuItem("@map_loc_cat_n:vendor_housing", 7);
	phrases->addMenuItem("@map_loc_cat_n:vendor_resources", 8);
	phrases->addMenuItem("@map_loc_cat_n:vendor_tools", 9);
	phrases->addMenuItem("@map_loc_cat_n:vendor_weapons", 10);
	phrases->addMenuItem("@map_loc_cat_n:vendor_junk", 11);
	phrases->addMenuItem("@map_loc_cat_n:vendor_pets", 12);
	phrases->addMenuItem("@map_loc_cat_n:vendor_medical", 13);
	phrases->addMenuItem("@map_loc_cat_n:vendor_ships", 14);

	owner->getPlayerObject()->addSuiBox(phrases);
	owner->sendMessage(phrases->generateMessage());
}

void VendorAdBarkingSessionImplementation::sendCustomMessageInput() {

	if(owner == NULL || vendor == NULL) {
		cancelSession();
		return;
	}

	ManagedReference<SuiInputBox*> input = new SuiInputBox(owner, SuiWindowType::VENDOR_CUSTOM_PHRASE);
	input->setPromptTitle("@player_structure:cust_t");
	input->setPromptText("@player_structure:cust_d");
	input->setUsingObject(vendor);
	input->setForceCloseDistance(16.f);
	input->setMaxInputSize(128);
	input->setCallback(new AdBarkingPhraseSuiCallback(owner->getZoneServer()));

	owner->getPlayerObject()->addSuiBox(input);
	owner->sendMessage(input->generateMessage());
}

void VendorAdBarkingSessionImplementation::sendMoodSelect() {

	if(owner == NULL || vendor == NULL) {
		cancelSession();
		return;
	}

	ManagedReference<SuiListBox*> moods = new SuiListBox(owner, SuiWindowType::VENDOR_MOODS);
	moods->setPromptTitle("@player_structure:vendor_moods_t");
	moods->setPromptText("@player_structure:vendor_moods_d");
	moods->setUsingObject(vendor);
	moods->setOkButton(true, "@ok");
	moods->setCancelButton(true, "@cancel");
	moods->setCallback(new AdBarkingPhraseSuiCallback(owner->getZoneServer()));

	moods->addMenuItem("@player_structure:alert", 0);
	moods->addMenuItem("@player_structure:bubbly", 1);
	moods->addMenuItem("@player_structure:casual", 2);
	moods->addMenuItem("@player_structure:cheerful", 3);
	moods->addMenuItem("@player_structure:dignified", 4);
	moods->addMenuItem("@player_structure:earnest", 5);
	moods->addMenuItem("@player_structure:ecstatic", 6);
	moods->addMenuItem("@player_structure:enthusiastic", 7);
	moods->addMenuItem("@player_structure:exuberant", 8);
	moods->addMenuItem("@player_structure:friendly", 9);
	moods->addMenuItem("@player_structure:happy", 10);
	moods->addMenuItem("@player_structure:joyful", 11);
	moods->addMenuItem("@player_structure:playful", 12);
	moods->addMenuItem("@player_structure:polite", 13);
	moods->addMenuItem("@player_structure:respectful", 14);
	moods->addMenuItem("@player_structure:sincere", 15);
	moods->addMenuItem("@player_structure:warm", 16);

	owner->getPlayerObject()->addSuiBox(moods);
	owner->sendMessage(moods->generateMessage());
}

void VendorAdBarkingSessionImplementation::sendAnimationSelect() {

	if(owner == NULL || vendor == NULL) {
		cancelSession();
		return;
	}

	ManagedReference<SuiListBox*> moods = new SuiListBox(owner, SuiWindowType::VENDOR_ANIMATION);
	moods->setPromptTitle("@player_structure:vendor_anim_t");
	moods->setPromptText("@player_structure:vendor_anim_d");
	moods->setUsingObject(vendor);
	moods->setOkButton(true, "@ok");
	moods->setCancelButton(true, "@cancel");
	moods->setCallback(new AdBarkingPhraseSuiCallback(owner->getZoneServer()));

	moods->addMenuItem("@player_structure:pose_proudly", 0);
	moods->addMenuItem("@player_structure:slow_down", 1);
	moods->addMenuItem("@player_structure:point_to_self", 2);
	moods->addMenuItem("@player_structure:rub_belly", 3);
	moods->addMenuItem("@player_structure:pat_abdomen", 4);
	moods->addMenuItem("@player_structure:nod_head_once", 5);
	moods->addMenuItem("@player_structure:celebrate", 6);
	moods->addMenuItem("@player_structure:wave2", 7);
	moods->addMenuItem("@player_structure:rub_chin_thoughtfully", 8);
	moods->addMenuItem("@player_structure:beckon", 9);
	moods->addMenuItem("@player_structure:bow5", 10);

	owner->getPlayerObject()->addSuiBox(moods);
	owner->sendMessage(moods->generateMessage());
}

void VendorAdBarkingSessionImplementation::completeSession() {

	if(owner == NULL || vendor == NULL) {
		cancelSession();
		return;
	}

	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
		cancelSession();
		return;
	}

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
	if(vendorData == NULL) {
		cancelSession();
		return;
	}

	Locker locker(vendor);

	vendorData->setAdBarking(true);
	vendorData->setAdPhrase(message);
	vendorData->setAdMood(mood);
	vendorData->setAdAnimation(animation);

	owner->sendSystemMessage("@player_structure:areabarks_enabled");

	cancelSession();
}
