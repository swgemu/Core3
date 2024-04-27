/*
 * CreateVendorSessionImplementation.cpp
 *
 *  Created on: May 20, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/player/sessions/vendor/VendorAdBarkingSession.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/callbacks/AdBarkingPhraseSuiCallback.h"

int VendorAdBarkingSessionImplementation::initializeSession() {
	ManagedReference<CreatureObject*> player = this->owner.get();
	ManagedReference<TangibleObject*> vendor = weakVendor.get();

	if (player == nullptr || vendor == nullptr) {
		return 0;
	}

	advertisingMod = player->getSkillMod("advertising");

	player->addActiveSession(SessionFacadeType::VENDORADBARKING, _this.getReferenceUnsafeStaticCast());

	if (vendor->getOptionsBitmask() & OptionBitmask::VENDOR) {
		sendPhraseOptions();
	} else {
		sendCustomMessageInput();
	}

	return 0;
}

void VendorAdBarkingSessionImplementation::sendPhraseOptions() {
	ManagedReference<CreatureObject*> player = this->owner.get();
	ManagedReference<TangibleObject*> vendor = weakVendor.get();

	if (player == nullptr || vendor == nullptr) {
		cancelSession();
		return;
	}

	// Event Perk NPC Actors use custom messages only
	if (!(vendor->getOptionsBitmask() & OptionBitmask::VENDOR)) {
		sendCustomMessageInput();
		return;
	}

	ManagedReference<SuiListBox*> phrases = new SuiListBox(player, SuiWindowType::VENDOR_PHRASES);
	phrases->setPromptTitle("@player_structure:vendor_strcats_t"); //Select Phrase Category
	phrases->setPromptText("@player_structure:vendor_strcats_d"); //Select the type of phrase for the vendor to bark. If you have "Advanced Vocalization" an option to customize the advertisement will appear on the list.

	phrases->setUsingObject(vendor);
	phrases->setOkButton(true, "@ok");
	phrases->setCancelButton(true, "@cancel");
	phrases->setCallback(new AdBarkingPhraseSuiCallback(player->getZoneServer()));

	if (player->hasSkill("crafting_merchant_advertising_02"))
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
	phrases->addMenuItem("@map_loc_cat_n:vendor_pets", 11);
	phrases->addMenuItem("@map_loc_cat_n:vendor_medical", 12);
	phrases->addMenuItem("@map_loc_cat_n:vendor_ships", 13);

	player->getPlayerObject()->addSuiBox(phrases);
	player->sendMessage(phrases->generateMessage());
}

void VendorAdBarkingSessionImplementation::sendCustomMessageInput() {
	ManagedReference<CreatureObject*> player = this->owner.get();
	ManagedReference<TangibleObject*> vendor = weakVendor.get();

	if (player == nullptr || vendor == nullptr) {
		cancelSession();
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		cancelSession();
		return;
	}

	ManagedReference<SuiInputBox*> input = new SuiInputBox(player, SuiWindowType::VENDOR_CUSTOM_PHRASE);

	if (input == nullptr) {
		cancelSession();
		return;
	}

	if (vendor->getOptionsBitmask() & OptionBitmask::VENDOR) {
		input->setPromptTitle("@player_structure:cust_t");
		input->setPromptText("@player_structure:cust_d");
	} else {
		input->setPromptTitle("@event_perk_npc_actor:cust_t");
		input->setPromptText("@event_perk_npc_actor:cust_d");
	}

	input->setUsingObject(vendor);
	input->setCancelButton(true, "@cancel");

	input->setForceCloseDistance(16.f);
	input->setMaxInputSize(128);
	input->setCallback(new AdBarkingPhraseSuiCallback(player->getZoneServer()));

	ghost->addSuiBox(input);
	player->sendMessage(input->generateMessage());
}

void VendorAdBarkingSessionImplementation::sendMoodSelect() {
	ManagedReference<CreatureObject*> player = this->owner.get();
	ManagedReference<TangibleObject*> vendor = weakVendor.get();

	if (player == nullptr || vendor == nullptr) {
		cancelSession();
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		cancelSession();
		return;
	}

	ManagedReference<SuiListBox*> moods = new SuiListBox(player, SuiWindowType::VENDOR_MOODS);

	if (moods == nullptr) {
		cancelSession();
		return;
	}

	if (vendor->getOptionsBitmask() & OptionBitmask::VENDOR) {
		moods->setPromptTitle("@player_structure:vendor_moods_t");
		moods->setPromptText("@player_structure:vendor_moods_d");

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
	} else {
		moods->setPromptTitle("@event_perk_npc_actor:actor_moods_t");
		moods->setPromptText("@event_perk_npc_actor:actor_moods_d");

		moods->addMenuItem("@event_perk_npc_actor:amazed", 0);
		moods->addMenuItem("@event_perk_npc_actor:amused", 1);
		moods->addMenuItem("@event_perk_npc_actor:angry", 2);
		moods->addMenuItem("@event_perk_npc_actor:annoyed", 3);
		moods->addMenuItem("@event_perk_npc_actor:bitter", 4);
		moods->addMenuItem("@event_perk_npc_actor:bloodthirsty", 5);
		moods->addMenuItem("@event_perk_npc_actor:brave", 6);
		moods->addMenuItem("@event_perk_npc_actor:callous", 7);
		moods->addMenuItem("@event_perk_npc_actor:careful", 8);
		moods->addMenuItem("@event_perk_npc_actor:cocky", 9);
		moods->addMenuItem("@event_perk_npc_actor:cold", 10);
		moods->addMenuItem("@event_perk_npc_actor:condescending", 11);
		moods->addMenuItem("@event_perk_npc_actor:crude", 12);
		moods->addMenuItem("@event_perk_npc_actor:cruel", 13);
		moods->addMenuItem("@event_perk_npc_actor:depressed", 14);
		moods->addMenuItem("@event_perk_npc_actor:disappointed", 15);
		moods->addMenuItem("@event_perk_npc_actor:discreet", 16);
		moods->addMenuItem("@event_perk_npc_actor:disgusted", 17);
		moods->addMenuItem("@event_perk_npc_actor:disoriented", 18);
		moods->addMenuItem("@event_perk_npc_actor:drunk", 19);
		moods->addMenuItem("@event_perk_npc_actor:embarrassed", 20);
		moods->addMenuItem("@event_perk_npc_actor:enthusiastic", 21);
		moods->addMenuItem("@event_perk_npc_actor:evil", 22);
		moods->addMenuItem("@event_perk_npc_actor:exhausted", 23);
		moods->addMenuItem("@event_perk_npc_actor:fanatical", 24);
		moods->addMenuItem("@event_perk_npc_actor:guilty", 25);
		moods->addMenuItem("@event_perk_npc_actor:happy", 26);
		moods->addMenuItem("@event_perk_npc_actor:hopeful", 27);
		moods->addMenuItem("@event_perk_npc_actor:hopeless", 28);
		moods->addMenuItem("@event_perk_npc_actor:hungry", 29);
		moods->addMenuItem("@event_perk_npc_actor:hysterical", 30);
		moods->addMenuItem("@event_perk_npc_actor:joyful", 31);
		moods->addMenuItem("@event_perk_npc_actor:loving", 32);
		// moods->addMenuItem("@event_perk_npc_actor:lul", 33);
		moods->addMenuItem("@event_perk_npc_actor:malevolent", 34);
		moods->addMenuItem("@event_perk_npc_actor:mischievous", 35);
		moods->addMenuItem("@event_perk_npc_actor:nervous", 36);
		moods->addMenuItem("@event_perk_npc_actor:none", 37);
		moods->addMenuItem("@event_perk_npc_actor:playful", 38);
		moods->addMenuItem("@event_perk_npc_actor:polite", 39);
		moods->addMenuItem("@event_perk_npc_actor:rude", 40);
		moods->addMenuItem("@event_perk_npc_actor:sad", 41);
		moods->addMenuItem("@event_perk_npc_actor:sarcastic", 42);
		moods->addMenuItem("@event_perk_npc_actor:scornful", 43);
		moods->addMenuItem("@event_perk_npc_actor:shy", 44);
		moods->addMenuItem("@event_perk_npc_actor:stubborn", 45);
		moods->addMenuItem("@event_perk_npc_actor:taunting", 46);
		moods->addMenuItem("@event_perk_npc_actor:thirsty", 47);
		moods->addMenuItem("@event_perk_npc_actor:whiny", 48);
	}

	moods->setUsingObject(vendor);
	moods->setOkButton(true, "@ok");
	moods->setCancelButton(true, "@cancel");
	moods->setCallback(new AdBarkingPhraseSuiCallback(player->getZoneServer()));

	ghost->addSuiBox(moods);
	player->sendMessage(moods->generateMessage());
}

void VendorAdBarkingSessionImplementation::sendAnimationSelect() {
	ManagedReference<CreatureObject*> player = this->owner.get();
	ManagedReference<TangibleObject*> vendor = weakVendor.get();

	if (player == nullptr || vendor == nullptr) {
		cancelSession();
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		cancelSession();
		return;
	}

	ManagedReference<SuiListBox*> animations = new SuiListBox(player, SuiWindowType::VENDOR_ANIMATION);

	if (animations == nullptr) {
		cancelSession();
		return;
	}

	if (vendor->getOptionsBitmask() & OptionBitmask::VENDOR) {
		animations->setPromptTitle("@player_structure:vendor_anim_t");
		animations->setPromptText("@player_structure:vendor_anim_d");

		animations->addMenuItem("@player_structure:pose_proudly", 0);
		animations->addMenuItem("@player_structure:slow_down", 1);
		animations->addMenuItem("@player_structure:point_to_self", 2);
		animations->addMenuItem("@player_structure:rub_belly", 3);
		animations->addMenuItem("@player_structure:pat_abdomen", 4);
		animations->addMenuItem("@player_structure:nod_head_once", 5);
		animations->addMenuItem("@player_structure:celebrate", 6);
		animations->addMenuItem("@player_structure:wave2", 7);
		animations->addMenuItem("@player_structure:rub_chin_thoughtfully", 8);
		animations->addMenuItem("@player_structure:beckon", 9);
		animations->addMenuItem("@player_structure:bow5", 10);
	} else {
		animations->setPromptTitle("@event_perk_npc_actor:actor_anim_t");
		animations->setPromptText("@event_perk_npc_actor:actor_anim_d");

		animations->addMenuItem("@event_perk_npc_actor:applause_excited", 0);
		animations->addMenuItem("@event_perk_npc_actor:applause_polite", 1);
		animations->addMenuItem("@event_perk_npc_actor:beckon", 2);
		animations->addMenuItem("@event_perk_npc_actor:beg", 3);
		animations->addMenuItem("@event_perk_npc_actor:bow5", 4);
		animations->addMenuItem("@event_perk_npc_actor:celebrate", 5);
		animations->addMenuItem("@event_perk_npc_actor:cough_heavy", 6);
		animations->addMenuItem("@event_perk_npc_actor:cough_polite", 7);
		animations->addMenuItem("@event_perk_npc_actor:cover_mouth", 8);
		animations->addMenuItem("@event_perk_npc_actor:flex_biceps", 9);
		animations->addMenuItem("@event_perk_npc_actor:gesticulate_wildly", 10);
		animations->addMenuItem("@event_perk_npc_actor:hair_flip", 1);
		animations->addMenuItem("@event_perk_npc_actor:hug_self", 12);
		animations->addMenuItem("@event_perk_npc_actor:kiss_blow_kiss", 13);
		animations->addMenuItem("@event_perk_npc_actor:laugh_cackle", 14);
		animations->addMenuItem("@event_perk_npc_actor:laugh_titter", 15);
		animations->addMenuItem("@event_perk_npc_actor:nod_head_once", 16);
		animations->addMenuItem("@event_perk_npc_actor:point_accusingly", 17);
		animations->addMenuItem("@event_perk_npc_actor:point_away", 18);
		animations->addMenuItem("@event_perk_npc_actor:point_down", 19);
		animations->addMenuItem("@event_perk_npc_actor:point_forward", 20);
		animations->addMenuItem("@event_perk_npc_actor:point_left", 21);
		animations->addMenuItem("@event_perk_npc_actor:point_right", 22);
		animations->addMenuItem("@event_perk_npc_actor:point_to_self", 23);
		animations->addMenuItem("@event_perk_npc_actor:point_up", 24);
		animations->addMenuItem("@event_perk_npc_actor:pose_proudly", 25);
		animations->addMenuItem("@event_perk_npc_actor:pound_fist_chest", 26);
		animations->addMenuItem("@event_perk_npc_actor:pound_fist_palm", 27);
		animations->addMenuItem("@event_perk_npc_actor:rub_belly", 28);
		animations->addMenuItem("@event_perk_npc_actor:rub_chin_thoughtfully", 29);
		animations->addMenuItem("@event_perk_npc_actor:scratch_head", 30);
		animations->addMenuItem("@event_perk_npc_actor:search", 31);
		animations->addMenuItem("@event_perk_npc_actor:shake_head_disgust", 32);
		animations->addMenuItem("@event_perk_npc_actor:shake_head_no", 33);
		animations->addMenuItem("@event_perk_npc_actor:shrug_shoulders", 34);
		animations->addMenuItem("@event_perk_npc_actor:slit_throat", 35);
		animations->addMenuItem("@event_perk_npc_actor:smell_armpit", 36);
		animations->addMenuItem("@event_perk_npc_actor:snap_finger1", 37);
		animations->addMenuItem("@event_perk_npc_actor:sneeze", 38);
		animations->addMenuItem("@event_perk_npc_actor:taunt1", 39);
		animations->addMenuItem("@event_perk_npc_actor:wave2", 40);
		animations->addMenuItem("@event_perk_npc_actor:wave_finger_warning", 41);
		animations->addMenuItem("@event_perk_npc_actor:wave_hail", 42);
		animations->addMenuItem("@event_perk_npc_actor:weeping", 43);
		animations->addMenuItem("@event_perk_npc_actor:yawn", 44);
	}

	animations->setUsingObject(vendor);
	animations->setOkButton(true, "@ok");
	animations->setCancelButton(true, "@cancel");
	animations->setCallback(new AdBarkingPhraseSuiCallback(player->getZoneServer()));

	ghost->addSuiBox(animations);
	player->sendMessage(animations->generateMessage());
}

void VendorAdBarkingSessionImplementation::completeSession() {
	ManagedReference<CreatureObject*> player = this->owner.get();
	ManagedReference<TangibleObject*> vendor = weakVendor.get();

	if (player == nullptr || vendor == nullptr) {
		cancelSession();
		return;
	}

	DataObjectComponentReference* data = vendor->getDataObjectComponent();

	if (data == nullptr || data->get() == nullptr || !data->get()->isVendorData()) {
		cancelSession();
		return;
	}

	VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());

	if (vendorData == nullptr) {
		cancelSession();
		return;
	}

	Locker locker(vendor);

	vendorData->setAdBarking(true);
	vendorData->setAdPhrase(message);
	vendorData->setAdMood(mood);
	vendorData->setAdAnimation(animation);

	if (vendor->isVendor()) {
		player->sendSystemMessage("@player_structure:areabarks_enabled");
	} else {
		player->sendSystemMessage("@event_perk_npc_actor:areabarks_enabled"); // When conversed with the actor will now perform.
	}

	cancelSession();
}
