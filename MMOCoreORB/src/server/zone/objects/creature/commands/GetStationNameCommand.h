/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETSTATIONNAMECOMMAND_H_
#define GETSTATIONNAMECOMMAND_H_

#include "server/login/account/Account.h"

class GetStationNameCommand : public QueueCommand {
public:

	GetStationNameCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if(!creature->isPlayerCreature())
			return INVALIDTARGET;

		ManagedReference<CreatureObject* > targetCreature = NULL;
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		StringTokenizer args(arguments.toString());

		if(args.hasMoreTokens()) {
			String character;
			args.getStringToken(character);

			targetCreature = playerManager->getPlayer(character);

		} else {

			targetCreature =
					server->getZoneServer()->getObject(target).castTo<CreatureObject*>();
		}

		if(targetCreature == NULL || !targetCreature->isPlayerCreature())
			return INVALIDTARGET;

		ManagedReference<Account*> account = targetCreature->getPlayerObject()->getAccount();
		if(account == NULL) {
			creature->sendSystemMessage("Account not found");
			return SUCCESS;
		}

		Locker alocker(account);

		creature->sendSystemMessage("Account name for " + targetCreature->getFirstName() +  ": " + account->getUsername());

		return SUCCESS;
	}

};

#endif //GETSTATIONNAMECOMMAND_H_
