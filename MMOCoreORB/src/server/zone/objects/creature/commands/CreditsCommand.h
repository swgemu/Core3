/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREDITSCOMMAND_H_
#define CREDITSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/transaction/TransactionLog.h"

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

			ManagedReference<CreatureObject*> player = nullptr;

			StringTokenizer args(arguments.toString());

			if(object == nullptr || !object->isPlayerCreature()) {

				String firstName;
				if(args.hasMoreTokens()) {
					args.getStringToken(firstName);
					player = server->getZoneServer()->getPlayerManager()->getPlayer(firstName);
				}

			} else {
				player = cast<CreatureObject*>( object.get());
			}

			if (player == nullptr) {
				creature->sendSystemMessage("invalid arguments for credits command:  /credits <firstname> <add/subtract> <amount> <bank/cash>");
				return GENERALERROR;
			}

			Locker clocker(player, creature);

			String action;
			args.getStringToken(action);

			int amount;
			amount = args.getIntToken();

			String location;
			args.getStringToken(location);

			bool success = false;

			if (action == "add") {

				if (location.toLowerCase() == "cash") {
					TransactionLog trx(TrxCode::CUSTOMERSERVICE, player, amount, true);
					player->addCashCredits(amount);
					success = true;
				}

				if (location.toLowerCase() == "bank") {
					TransactionLog trx(TrxCode::CUSTOMERSERVICE, player, amount, false);
					player->addBankCredits(amount);
					success = true;
				}

			} else if (action == "subtract") {

				if (location.toLowerCase() == "cash") {
					if (player->verifyCashCredits(amount)) {
						TransactionLog trx(player, TrxCode::CUSTOMERSERVICE, amount, true);
						player->subtractCashCredits(amount);
					} else {
						TransactionLog trx(player, TrxCode::CUSTOMERSERVICE, player->getCashCredits(), true);
						player->clearCashCredits();
					}

					success = true;
				}

				if (location.toLowerCase() == "bank") {
					if (player->verifyBankCredits(amount)) {
						TransactionLog trx(player, TrxCode::CUSTOMERSERVICE, amount, false);
						player->subtractBankCredits(amount);
					} else {
						TransactionLog trx(player, TrxCode::CUSTOMERSERVICE, player->getBankCredits(), false);
						player->clearBankCredits();
					}

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
