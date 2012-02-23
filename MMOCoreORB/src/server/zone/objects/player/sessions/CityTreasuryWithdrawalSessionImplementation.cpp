/*
 * CityTreasuryWithdrawalSessionImplementation.cpp
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#include "CityTreasuryWithdrawalSession.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/callbacks/CityTreasuryWithdrawalReasonSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CityTreasuryWithdrawalSuiCallback.h"

int CityTreasuryWithdrawalSessionImplementation::initializeSession() {
	PlayerObject* ghost = creatureObject->getPlayerObject();

	if (ghost == NULL || !cityRegion->isMayor(creatureObject->getObjectID()))
		return cancelSession();

	ManagedReference<SuiInputBox*> input = new SuiInputBox(creatureObject, SuiWindowType::CITY_TREASURY_WITHDRAWAL_REASON);
	input->setPromptTitle("@city/city:withdraw_reason_t"); //Reason for Withdrawal
	input->setPromptText("@city/city:withdraw_reason_d"); //Enter the reason for the withdraw. The citizenship will be notified...
	input->setUsingObject(terminalObject);
	input->setMaxInputSize(255);
	input->setForceCloseDistance(16.f);
	input->setCallback(new CityTreasuryWithdrawalReasonSuiCallback(creatureObject->getZoneServer()));

	ghost->addSuiBox(input);
	creatureObject->sendMessage(input->generateMessage());

	return 1;
}

int CityTreasuryWithdrawalSessionImplementation::sendTransferBox(const String& reason) {
	setReason(reason);

	PlayerObject* ghost = creatureObject->getPlayerObject();

	if (ghost == NULL)
		return cancelSession();

	int maxWithdrawal = MIN(cityRegion->getMaxWithdrawal(), cityRegion->getCityTreasury());

	ManagedReference<SuiTransferBox*> transfer = new SuiTransferBox(creatureObject, SuiWindowType::CITY_TREASURY_WITHDRAWAL);
	transfer->setPromptTitle("@city/city:treasury_withdraw"); //Treasury Withdrawal
	transfer->setPromptText("@city/city:treasury_withdraw_prompt"); //Enter the amount you would like to withdraw from the treasury. You can only withdraw between 10,000 and 50,000 credits per day.
	transfer->addFrom("@city/city:total_funds", "0", "0", "1"); //Total funds available
	transfer->addTo("@city/city:treasury", String::valueOf(maxWithdrawal), String::valueOf(maxWithdrawal), "1"); //Treasury
	transfer->setUsingObject(terminalObject);
	transfer->setForceCloseDistance(16.f);
	transfer->setCallback(new CityTreasuryWithdrawalSuiCallback(creatureObject->getZoneServer()));

	ghost->addSuiBox(transfer);
	creatureObject->sendMessage(transfer->generateMessage());

	return 1;
}

int CityTreasuryWithdrawalSessionImplementation::withdrawCredits(int value) {
	if (cityRegion == NULL)
		return cancelSession();

	CityManager* cityManager = creatureObject->getZoneServer()->getCityManager();
	cityManager->withdrawFromCityTreasury(cityRegion, creatureObject, value, terminalObject);

	return 1;
}
