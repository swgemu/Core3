/*
 * CreateVendorSessionImplementation.cpp
 *
 *  Created on: May 20, 2012
 *      Author: Kyle
 */

#include "VendorAdBarkingSession.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

int VendorAdBarkingSessionImplementation::initializeSession() {

	ManagedReference<CreatureObject*> player = this->owner.get();

	if (player == NULL)
		return 0;

	if (player->containsActiveSession(SessionFacadeType::VENDORADBARKING)) {
		return 0;
	}

	advertisingMod = player->getSkillMod("advertising");

	owner->addActiveSession(SessionFacadeType::VENDORADBARKING, _this.get());

	sendPhraseOptions();

	return 0;
}

void VendorAdBarkingSessionImplementation::sendPhraseOptions() {

//	ManagedReference<SuiListBox*> status = new SuiListBox(owner, SuiWindowType::STRUCTURE_STATUS);
//	status->setPromptTitle("@player_structure:vendor_strcats_t"); //Select Phrase Category
//	status->setPromptText("@player_structure:vendor_strcats_d"); //Select the type of phrase for the vendor to bark. If you have "Advanced Vocalization" an option to customize the advertisement will appear on the list.
//	status->setUsingObject(vendor);
//	status->setOkButton(true, "@ok");
//	status->setCancelButton(true, "@cancel");
//	status->setCallback(new AdBarkingPhraseSuiCallback(owner->getZoneServer()));
//
//	if(owner->hasSkill("crafting_merchant_advertising_02"))
//		status->addMenuItem("Customize");
//
//	status->addMenuItem("@map_loc_cat_n:vendor_armor");
//	status->addMenuItem("@map_loc_cat_n:vendor_clothing");
//	status->addMenuItem("@map_loc_cat_n:vendor_components");
//	status->addMenuItem("@map_loc_cat_n:vendor_droids");
//	status->addMenuItem("@map_loc_cat_n:vendor_equipment");
//	status->addMenuItem("@map_loc_cat_n:vendor_food");
//	status->addMenuItem("@map_loc_cat_n:vendor_housing");
//	status->addMenuItem("@map_loc_cat_n:vendor_resources");
//	status->addMenuItem("@map_loc_cat_n:vendor_tools");
//	status->addMenuItem("@map_loc_cat_n:vendor_weapons");
//	status->addMenuItem("@map_loc_cat_n:vendor_junk");
//	status->addMenuItem("@map_loc_cat_n:vendor_pets");
//	status->addMenuItem("@map_loc_cat_n:vendor_medical");
//	status->addMenuItem("@map_loc_cat_n:vendor_ships");
//
//	ghost->addSuiBox(status);
//	creature->sendMessage(status->generateMessage());
}
