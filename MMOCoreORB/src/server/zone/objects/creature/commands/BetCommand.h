/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BETCOMMAND_H_
#define BETCOMMAND_H_

#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/objects/creature/CreatureObject.h"

class BetCommand : public QueueCommand {
public:

	BetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;

		if (creature->isPlayerCreature()) {

			CreatureObject* player = cast<CreatureObject*>(creature);

			if (player == NULL)
				return GENERALERROR;

			GamblingManager* gamblingManager = server->getGamblingManager();

			if (gamblingManager == NULL)
				return GENERALERROR;

			if (!gamblingManager->isPlaying(player)) {
				player->sendSystemMessage("@gambling/default_interface:bet_failed");
				return GENERALERROR;
			}

			try {
				StringTokenizer args(arguments.toString());

				if (args.hasMoreTokens()) {
					int amount = args.getIntToken();
					String bet;
					args.getStringToken(bet);

					bet.toLowerCase();

					int targetBet = -1;

					for (int i=0; i<gamblingManager->getRoulette()->size(); ++i) {

						if (gamblingManager->getRoulette()->get(i)==bet) {
							targetBet = i;
						}
					}

					if (targetBet == -1) {
						player->sendSystemMessage("@gambling/default_interface:bet_failed_amt");
						return GENERALERROR;
					}

					gamblingManager->bet(player, amount, targetBet, 0);
				}
			} catch (Exception& e) {
				player->sendSystemMessage("@gambling/default_interface:bet_failed_amt");
			}

		}

		return SUCCESS;
	}

};

#endif //BETCOMMAND_H_
