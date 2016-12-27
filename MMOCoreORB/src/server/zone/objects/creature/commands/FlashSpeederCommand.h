/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FLASHSPEEDERCOMMAND_H_
#define FLASHSPEEDERCOMMAND_H_

#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/ReplaceFlashSpeederSuiCallback.h"

class FlashSpeederCommand : public QueueCommand {
public:



	FlashSpeederCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(player))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(player))
			return INVALIDLOCOMOTION;

		if( !player->isPlayerCreature() )
			return GENERALERROR;

		if( player->getPlayerObject() == NULL )
			return GENERALERROR;

		// Player must have chosen flash speeder as a veteran reward
		if( !player->getPlayerObject()->hasChosenVeteranReward( "object/tangible/deed/vehicle_deed/speederbike_flash_deed.iff" ) ){
			player->sendSystemMessage( "@veteran:flash_speeder_not_eligible" ); //	"You are not eligible to receive a Flash Speeder"
			return GENERALERROR;
		}

		// Player must have enough credits
		if( player->getCashCredits() + player->getBankCredits() < ReplaceFlashSpeederSuiCallback::FLASH_SPEEDER_COST ){
			player->sendSystemMessage( "@veteran:flash_speeder_no_credits" ); // "You do not have enough credits to receive a replacement."
			return GENERALERROR;
		}

		// Build and send confirmation window
		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::CONFIRM_FLASH_SPEEDER_PURCHASE);
		suiBox->setCallback(new ReplaceFlashSpeederSuiCallback(server->getZoneServer()));
		suiBox->setPromptTitle("Confirm Flash Speeder Replacement");
		suiBox->setPromptText( "@veteran:flash_speeder_replace_prompt" );  // "A replacement Flash Speeder is available at the cost of 20000 credits. Are you sure you want a new speeder?"
		suiBox->setCancelButton(true, "@no");
		suiBox->setOkButton(true, "@yes");

		player->getPlayerObject()->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());

		return SUCCESS;
	}

};

#endif //FLASHSPEEDERCOMMAND_H_
