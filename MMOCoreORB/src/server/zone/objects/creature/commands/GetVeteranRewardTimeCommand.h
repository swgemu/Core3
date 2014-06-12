/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef GETVETERANREWARDTIMECOMMAND_H_
#define GETVETERANREWARDTIMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GetVeteranRewardTimeCommand : public QueueCommand {
public:

	GetVeteranRewardTimeCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) {

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
		if( nextMilestone > -1 ){
			buff << "You will be eligible for the " << String::valueOf(nextMilestone) << "-day reward in ";
			buff << String::valueOf(nextMilestone - account->getAgeInDays() ) << " days";
			player->sendSystemMessage( buff.toString() );
		}

		return SUCCESS;
	}

};

#endif //GETVETERANREWARDTIMECOMMAND_H_
