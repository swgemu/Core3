/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETVETERANREWARDTIMECOMMAND_H_
#define GETVETERANREWARDTIMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GetVeteranRewardTimeCommand : public QueueCommand {
public:

	GetVeteranRewardTimeCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(player))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(player))
			return INVALIDLOCOMOTION;

		if( player == NULL || !player->isPlayerCreature() )
			return GENERALERROR;

		PlayerObject* playerGhost = player->getPlayerObject();
		if( playerGhost == NULL )
			return GENERALERROR;

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();
		if( playerManager == NULL )
			return GENERALERROR;

		// Get account
		ManagedReference<Account*> account = playerManager->getAccount( playerGhost->getAccountID() );
		if( account == NULL )
			return GENERALERROR;

		// Send message with current account age
		StringIdChatParameter timeActiveMsg;
		timeActiveMsg.setStringId("veteran", "self_time_active"); // You have %DI days logged for veteran rewards.
		timeActiveMsg.setDI( account->getAgeInDays() );
		player->sendSystemMessage( timeActiveMsg );

		StringBuffer buff;

		// Check if player is eligible for a reward
		int eligibleMilestone = playerManager->getEligibleMilestone( playerGhost, account );
		if( eligibleMilestone > -1 ){
			buff << "You are eligible for the " << String::valueOf(eligibleMilestone) << "-day reward!";
			player->sendSystemMessage( buff.toString() );
			player->sendSystemMessage( "Use /claimVeteranReward to choose your reward!" );
			return SUCCESS;
		}
		else{
			player->sendSystemMessage( "@veteran:not_eligible"); // You are not currently eligible for a veteran reward.
		}

		// Check next milestone
		int nextMilestone = playerManager->getFirstIneligibleMilestone( playerGhost, account );
		buff << "You will be eligible for the " << String::valueOf(nextMilestone) << "-day reward in ";
		buff << String::valueOf(nextMilestone - account->getAgeInDays() ) << " days";
		player->sendSystemMessage( buff.toString() );

		return SUCCESS;
	}

};

#endif //GETVETERANREWARDTIMECOMMAND_H_
