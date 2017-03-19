/*
 * StructureSetAccessFeeSession.cpp
 *
 *  Created on: April 30, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/player/sessions/StructureSetAccessFeeSession.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/sui/callbacks/StructureSetAccessFeeSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructureSetAccessDurationSuiCallback.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/PlayerObject.h"

int StructureSetAccessFeeSessionImplementation::initializeSession() {
	ManagedReference<CreatureObject*> player = this->player.get();
	ManagedReference<BuildingObject*> structure = this->structure.get();

	if (player == NULL || structure == NULL) {
		cancelSession();
		return 0;
	}

	if (!structure->isOnAdminList(player)) {
		cancelSession();
		return 0;
	}

	if (structure->isPrivateStructure()) {
		player->sendSystemMessage("@player_structure:public_only");
		cancelSession();
		return 0;
	}

	return 1;
}

int StructureSetAccessFeeSessionImplementation::clearSession() {
	ManagedReference<CreatureObject*> player = this->player.get();

	if (player != NULL) {
		ManagedReference<PlayerObject*> playerGhost = player->getPlayerObject();

		if (playerGhost != NULL) {
			if (feeAmountBox != NULL) {
				if (playerGhost->hasSuiBox(feeAmountBox->getBoxID())) {
					player->sendMessage(feeAmountBox->generateCloseMessage());
				}
			}

			if (durationBox != NULL) {
				if (playerGhost->hasSuiBox(durationBox->getBoxID())) {
					player->sendMessage(durationBox->generateCloseMessage());
				}
			}
		}
	}

	player = NULL;

	return 0;
}

void StructureSetAccessFeeSessionImplementation::promptSetAccessFee() {
	ManagedReference<CreatureObject*> player = this->player.get();
	ManagedReference<BuildingObject*> structure = this->structure.get();

	if (player == NULL || structure == NULL) {
		cancelSession();
		return;
	}

	ManagedReference<PlayerObject*> playerGhost = player->getPlayerObject();

	if (!structure->isOnAdminList(player) || playerGhost == NULL) {
		cancelSession();
		return;
	}

	if (structure->isPrivateStructure()) {
		player->sendSystemMessage("@player_structure:public_only");
		cancelSession();
		return;
	}

	if (feeAmountBox == NULL) {
		feeAmountBox = new SuiInputBox(player, SuiWindowType::STRUCTURE_SET_ACCESS_FEE);
		feeAmountBox->setCallback(new StructureSetAccessFeeSuiCallback(player->getZoneServer()));
		feeAmountBox->setPromptTitle("@player_structure:access_fee_t"); //Access Fee
		feeAmountBox->setUsingObject(structure);
		feeAmountBox->setMaxInputSize(4);
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
	ManagedReference<CreatureObject*> player = this->player.get();
	ManagedReference<BuildingObject*> structure = this->structure.get();

	if (player == NULL || structure == NULL) {
		cancelSession();
		return;
	}

	ManagedReference<PlayerObject*> playerGhost = player->getPlayerObject();

	if (!structure->isOnAdminList(player) || playerGhost == NULL) {
		cancelSession();
		return;
	}

	if (structure->isPrivateStructure()) {
		player->sendSystemMessage("@player_structure:public_only");
		cancelSession();
		return;
	}

	if (durationBox == NULL) {
		durationBox = new SuiInputBox(player, SuiWindowType::STRUCTURE_SET_ACCESS_DURATION);
		durationBox->setCallback(new StructureSetAccessDurationSuiCallback(player->getZoneServer()));
		durationBox->setPromptTitle("@player_structure:access_time_t"); //Access Fee
		durationBox->setUsingObject(structure);
		durationBox->setMaxInputSize(3);
		durationBox->setPromptText("@player_structure:access_time"); // How much would you like to charge people to enter the building
	}

	playerGhost->addSuiBox(durationBox);
	player->sendMessage(durationBox->generateMessage());
}

void StructureSetAccessFeeSessionImplementation::setAccessDuration(const int duration) {
	ManagedReference<CreatureObject*> player = this->player.get();
	ManagedReference<BuildingObject*> structure = this->structure.get();

	if (player == NULL || structure == NULL) {
		cancelSession();
		return;
	}

	structure->setAccessFee(accessFee, duration);

	player->sendSystemMessage("Structure now has an access fee");

	cancelSession();
}
