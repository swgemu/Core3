/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREDITSCOMMAND_H_
#define CREDITSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CreditsCommand : public QueueCommand {
public:

	CreditsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		try {

			ManagedReference<SceneObject* > object =
					server->getZoneServer()->getObject(target);

			ManagedReference<CreatureObject*> player = NULL;

			StringTokenizer args(arguments.toString());

			if(object == NULL || !object->isPlayerCreature()) {

				String firstName;
				if(args.hasMoreTokens()) {
					args.getStringToken(firstName);
					player = server->getZoneServer()->getPlayerManager()->getPlayer(firstName);
				}

			} else {
				player = cast<CreatureObject*>( object.get());
			}

			if (player == NULL) {
				creature->sendSystemMessage("invalid arguments for credits command:  /credits <firstname> <add/subtract> <amount> <bank/cash>");
				return GENERALERROR;
			}

			String action;
			args.getStringToken(action);

			int amount;
			amount = args.getIntToken();

			String location;
			args.getStringToken(location);

			bool success = false;

			if (action == "add") {

				if (location.toLowerCase() == "cash") {
					player->addCashCredits(amount);
					success = true;
				}

				if (location.toLowerCase() == "bank") {
					player->addBankCredits(amount);
					success = true;
				}

			} else if (action == "subtract") {

				if (location.toLowerCase() == "cash") {
					if (player->verifyCashCredits(amount))
						player->subtractCashCredits(amount);
					else
						player->setCashCredits(0, true);

					success = true;
				}

				if (location.toLowerCase() == "bank") {
					if (player->verifyBankCredits(amount))
						player->subtractBankCredits(amount);
					else
						player->setBankCredits(0, true);

					success = true;
				}
			}

			if(success)
				creature->sendSystemMessage("Credits have been deposited successfully for " + player->getFirstName());
			else
				creature->sendSystemMessage("invalid arguments for credits command:  /credits <firstname> <add/subtract> <amount> <bank/cash>");

		} catch (Exception& e) {
			creature->sendSystemMessage("invalid arguments for credits command:  /credits <firstname> <add/subtract> <amount> <bank/cash>");
		}

		return SUCCESS;
	}

};

#endif //CREDITSCOMMAND_H_
