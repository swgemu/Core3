/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLEARVETERANREWARDCOMMAND_H_
#define CLEARVETERANREWARDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class ClearVeteranRewardCommand : public QueueCommand {
public:

	ClearVeteranRewardCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(player))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(player))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		int milestone = -1;

		if(tokenizer.hasMoreTokens())
			milestone = tokenizer.getIntToken();

		if( milestone < 0 ){
			player->sendSystemMessage("SYNTAX: /clearVeteranReward player milestone");
			return INVALIDPARAMETERS;
		}

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);
		if (obj == NULL || !obj->isPlayerCreature()) {
			player->sendSystemMessage("SYNTAX: /clearVeteranReward player milestone");
			return INVALIDPARAMETERS;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>( obj.get());
		PlayerObject* targetGhost = targetCreature->getPlayerObject();

		Locker clocker(targetCreature, player);

		String reward = targetGhost->getChosenVeteranReward( milestone );
		if( reward.isEmpty() ){
			player->sendSystemMessage("Player has not chosen a reward for that milestone");
			return GENERALERROR;
		}

		// Get account
		ManagedReference<Account*> account = targetGhost->getAccount();

		if( account == NULL ){
			player->sendSystemMessage("Error finding account");
			return GENERALERROR;
		}

		Locker alocker(account);

		// Clear reward in all characters registered to the account

		GalaxyAccountInfo *info = targetGhost->getGalaxyAccountInfo();

		if(info == NULL)
			return GENERALERROR;

		info->clearVeteranReward(milestone);

		player->sendSystemMessage( targetGhost->getAccount()->getUsername() + "'s " + String::valueOf(milestone) + "-day reward has been cleared" );

		return SUCCESS;
	}

};

#endif //CLEARVETERANREWARDCOMMAND_H_
