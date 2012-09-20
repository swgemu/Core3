/*
 * BankTerminalMenuComponent.cpp
 *
 *  Created on: 01/12/2012
 *      Author: Elvaron
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "BankTerminalMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sui/banktransferbox/SuiBankTransferBox.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/region/CityRegion.h"

void BankTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) {

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	if (sceneObject->getZone() == NULL)
		return;

	String location = ghost->getBankLocation();

	//if (location = "") {
		// Join Bank
		menuResponse->addRadialMenuItemToRadialID(20, 71, 3, "@sui:bank_join");
	//} else {
		// Quit Bank - no checks here since there are error message stfs
		menuResponse->addRadialMenuItemToRadialID(20, 72, 3, "@sui:bank_quit");

		/*SceneObject* deposit = player->getSlottedObject("bank");
		if (deposit->getContainerObjectsSize() == 0) {
			// Quit Bank
			menuResponse->addRadialMenuItemToRadialID(118, 128, 3, "@player_structure:permission_destroy"); //Destroy Structure
		}
		 */

		String currentLocation = sceneObject->getZone()->getZoneName();
		//if (currentLocation == location) {
			menuResponse->addRadialMenuItemToRadialID(20, 73, 3, "@sui:bank_items"); //Safety Deposit
		//}
	//}
	menuResponse->addRadialMenuItemToRadialID(20, 68, 3, "@sui:bank_credits"); // Deposit/Withdrawal
	menuResponse->addRadialMenuItemToRadialID(20, 69, 3, "@sui:bank_depositall"); // Deposit all
	menuResponse->addRadialMenuItemToRadialID(20, 70, 3, "@sui:bank_withdrawall"); // Withdraw all

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, creature);
}

int BankTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!creature->isPlayerCreature())
		return 0;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	String planet = ghost->getBankLocation();

	ManagedReference<CityRegion* > region = sceneObject->getCityRegion().get();

	if (region != NULL) {
		if (region->isBanned(creature->getObjectID())) {
				creature->sendSystemMessage("@city/city:youre_city_banned"); // you are banned from this city and may not use any of its public services and structures
				return 0;
		}
	}

	if(selectedID == WITHDRAW || selectedID == 20) {

		ManagedReference<SuiBankTransferBox*> sui = new SuiBankTransferBox(sceneObject, creature, SuiWindowType::BANK_TRANSFER);

		sui->addCash(creature->getCashCredits());
		sui->addBank(creature->getBankCredits());

		ghost->addSuiBox(sui);
		creature->sendMessage(sui->generateMessage());

		return 0;
	} else if (selectedID == JOIN) {

		if (planet == "") {
			// JOIN BANK
			ghost->setBankLocation(creature->getZone()->getZoneName());
			//creature->transferObject(bank, 4);
			SceneObject* bank = creature->getSlottedObject("bank");
			bank->sendTo(creature, true);
			creature->sendSystemMessage("@system_msg:succesfully_joined_bank");
		} else if (planet == creature->getZone()->getZoneName()) {
			// Already joined this bank
			creature->sendSystemMessage("@system_msg:already_member_of_bank");
		} else {
			// Already member different bank
			creature->sendSystemMessage("@system_msg:member_of_different_bank");
		}

		return 0;
	} else if (selectedID == QUIT) {

		SceneObject* bank = creature->getSlottedObject("bank");

		ZoneServer* server = creature->getZoneServer();

		/*It doens't check whether you're on your registered bank's planet
		 * It probably doesn't matter though.
		 * If anyone remembers you had to go to the correct planet for it we can change it */

		if (bank->getContainerObjectsSize() == 0) {

			//creature->removeObject(bank, NULL, true);
			bank->sendDestroyTo(creature);

			// QUIT BANK
			ghost->setBankLocation("");

			creature->sendSystemMessage("@system_msg:succesfully_quit_bank");
		} else {
			// Not empty
			creature->sendSystemMessage("@system_msg:bank_not_empty");
		}

		return 0;

	} else if (selectedID == DEPOSIT) {

		if (planet == creature->getZone()->getZoneName() || GLOBALSAFETYDEPOSIT) {

			ManagedReference<SceneObject*> bank = creature->getSlottedObject("bank");
			bank->openContainerTo(creature);
		} else {
			creature->sendSystemMessage("@newbie_tutorial/system_messages:bank_info_2");
		}

		return 0;
	} else if (selectedID == DEPOSITALL) {

		uint32 cash = creature->getCashCredits();

		StringIdChatParameter params;
		params.setStringId("@base_player:prose_deposit_success");
		params.setDI(cash);
		creature->sendSystemMessage(params);

		creature->subtractCashCredits(cash);
		creature->addBankCredits(cash);

		return 0;
	} else if (selectedID == WITHDRAWALL) {

		uint32 cash = creature->getBankCredits();

		StringIdChatParameter params;
		params.setStringId("@base_player:prose_withdraw_success");
		params.setDI(cash);
		creature->sendSystemMessage(params);

		creature->subtractBankCredits(cash);
		creature->addCashCredits(cash);

		return 0;
	} else
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, creature, selectedID);

	return 0;
}

