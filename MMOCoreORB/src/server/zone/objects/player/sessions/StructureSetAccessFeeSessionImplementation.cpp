/*
 * StructureSetAccessFeeSession.cpp
 *
 *  Created on: April 30, 2012
 *      Author: Kyle
 */

#include "StructureSetAccessFeeSession.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sessions/sui/PlayerManagementSessionSuiCallback.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/sui/callbacks/StructureSetAccessFeeSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructureSetAccessDurationSuiCallback.h"
#include "server/zone/objects/building/BuildingObject.h"

int StructureSetAccessFeeSessionImplementation::initializeSession() {

	if(player == NULL || structure == NULL) {
		cancelSession();
		return 0;
	}

	if(!structure->isOwnerOf(player)) {
		cancelSession();
		return 0;
	}

	if(structure->isPrivateStructure()) {
		player->sendSystemMessage("@player_structure:public_only");
		cancelSession();
		return 0;
	}

	return 1;
}

int StructureSetAccessFeeSessionImplementation::clearSession() {

	if(feeAmountBox != NULL && playerGhost != NULL && player != NULL) {
		if(playerGhost->hasSuiBox(feeAmountBox->getBoxID())) {
			player->sendMessage(feeAmountBox->generateCloseMessage());
		}

	}

	if(durationBox != NULL && playerGhost != NULL && player != NULL) {
		if(playerGhost->hasSuiBox(durationBox->getBoxID())) {
			player->sendMessage(durationBox->generateCloseMessage());
		}

	}

	player = NULL;

	return 0;
}

void StructureSetAccessFeeSessionImplementation::promptSetAccessFee() {

	if(!structure->isOwnerOf(player)) {
		cancelSession();
		return;
	}

	if(structure->isPrivateStructure()) {
		player->sendSystemMessage("@player_structure:public_only");
		cancelSession();
		return;
	}

	if(feeAmountBox == NULL) {
		feeAmountBox = new SuiInputBox(player, SuiWindowType::STRUCTURE_SET_ACCESS_FEE);
		feeAmountBox->setCallback(new StructureSetAccessFeeSuiCallback(player->getZoneServer()));
		feeAmountBox->setPromptTitle("@player_structure:access_fee_t"); //Access Fee
		feeAmountBox->setUsingObject(structure);
		feeAmountBox->setPromptText("@player_structure:access_fee"); // How much would you like to charge people to enter the building
	}

	playerGhost->addSuiBox(feeAmountBox);
	player->sendMessage(feeAmountBox->generateMessage());
}

void StructureSetAccessFeeSessionImplementation::setAccessFee(const int fee) {
	accessFee = fee;
	promptSetAccessDuration();
}

void StructureSetAccessFeeSessionImplementation::promptSetAccessDuration() {
	if(!structure->isOwnerOf(player)) {
		cancelSession();
		return;
	}

	if(structure->isPrivateStructure()) {
		player->sendSystemMessage("@player_structure:public_only");
		cancelSession();
		return;
	}

	if(durationBox == NULL) {
		durationBox = new SuiInputBox(player, SuiWindowType::STRUCTURE_SET_ACCESS_DURATION);
		durationBox->setCallback(new StructureSetAccessDurationSuiCallback(player->getZoneServer()));
		durationBox->setPromptTitle("@player_structure:access_time_t"); //Access Fee
		durationBox->setUsingObject(structure);
		durationBox->setPromptText("@player_structure:access_time"); // How much would you like to charge people to enter the building
	}

	playerGhost->addSuiBox(durationBox);
	player->sendMessage(durationBox->generateMessage());
}

void StructureSetAccessFeeSessionImplementation::setAccessDuration(const int duration) {

	structure->setAccessFee(accessFee, duration);

	player->sendSystemMessage("Structure now has an access fee");

	cancelSession();
}
