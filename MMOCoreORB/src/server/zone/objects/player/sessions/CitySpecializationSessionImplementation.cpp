/*
 * CitySpecializationSessionImplementation.cpp
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#include "server/zone/objects/player/sessions/CitySpecializationSession.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/variables/AbilityList.h"
#include "server/zone/objects/player/variables/Ability.h"
#include "server/zone/objects/player/sui/callbacks/CitySpecializationSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CitySpecializationConfirmSuiCallback.h"

int CitySpecializationSessionImplementation::initializeSession() {
	PlayerObject* ghost = creatureObject->getPlayerObject();

	if (ghost == NULL)
		return cancelSession();

	if (!cityRegion->isMayor(creatureObject->getObjectID()))
		return cancelSession();

	ManagedReference<SuiListBox*> sui = new SuiListBox(creatureObject, SuiWindowType::CITY_SPEC, 0x00);
	sui->setPromptTitle("@city/city:city_specs_t"); //City Specialization
	sui->setPromptText("@city/city:city_specs_d");
	sui->setCallback(new CitySpecializationSuiCallback(creatureObject->getZoneServer()));
	sui->setUsingObject(terminalObject);
	sui->setForceCloseDistance(16.f);

	AbilityList* abilityList = ghost->getAbilityList();

	for (int i = 0; i < abilityList->size(); ++i) {
		Reference<Ability*> ability = abilityList->get(i);
		String abilityName = ability->getAbilityName();

		if (abilityName.beginsWith("city_spec"))
			sui->addMenuItem("@city/city:" + abilityName);
	}

	if (!cityRegion->getCitySpecialization().isEmpty()) {
		sui->addMenuItem("@city/city:null",-1);
	}

	if (sui->getMenuSize() <= 0) {
		creatureObject->sendSystemMessage("@city/city:no_specs"); //You need to learn a specialization skill before you can select one for your city.
		return cancelSession();
	}

	ghost->addSuiBox(sui);
	creatureObject->sendMessage(sui->generateMessage());

	return 1;
}

int CitySpecializationSessionImplementation::sendConfirmationBox(const String& choice) {
	PlayerObject* ghost = creatureObject->getPlayerObject();

	if (ghost == NULL)
		return cancelSession();

	if (choice != "@city/city:null") {
		if (cityRegion->getCityRank() < CityRegion::RANK_TOWNSHIP) {
			creatureObject->sendSystemMessage("@city/city:no_rank_spec"); //Your city must be at least rank 3 before you can set a specialization
			return cancelSession();
		}

		if (!creatureObject->checkCooldownRecovery("city_specialization")) {
			StringIdChatParameter params("city/city", "spec_time"); //You can't set another city spec right now. Time Remaining: %TO
			Time* timeRemaining = creatureObject->getCooldownTime("city_specialization");
			params.setTO(String::valueOf(round(fabs(timeRemaining->miliDifference() / 1000.f))) + " seconds");
			creatureObject->sendSystemMessage(params);

			return cancelSession();
		}
	}

	SuiMessageBox* confirm = new SuiMessageBox(creatureObject, SuiWindowType::CITY_SPEC_CONFIRM);
	confirm->setPromptTitle("@city/city:confirm_spec_t"); //Confirm Specialization

	if (choice == "@city/city:null") {
		confirm->setPromptText(choice + "_d");
		specialization = "";
	} else {
		confirm->setPromptText(choice + "_d\n\n@city/city:confirm_spec_d");
		specialization = choice;
	}
	confirm->setOkButton(true, "@yes");
	confirm->setCancelButton(true, "@no");
	confirm->setCallback(new CitySpecializationConfirmSuiCallback(creatureObject->getZoneServer()));

	ghost->addSuiBox(confirm);
	creatureObject->sendMessage(confirm->generateMessage());

	return 1;
}

int CitySpecializationSessionImplementation::acceptChoice() {
	CityManager* cityManager = creatureObject->getZoneServer()->getCityManager();
	cityManager->changeCitySpecialization(cityRegion, creatureObject, specialization);

	return cancelSession();
}
