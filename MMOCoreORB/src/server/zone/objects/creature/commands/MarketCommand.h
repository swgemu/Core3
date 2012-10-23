/*
 * VendorInfoCommand.h
 *
 *  Created on: Apr 6, 2011
 *      Author: polonel
 */

#ifndef MARKETCOMMAND_H_
#define MARKETCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/managers/auction/AuctionManager.h"

class MarketCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;

		ManagedReference<AuctionManager*> auctionManager = creature->getZoneServer()->getAuctionManager();
		//Parse the weather command.

		StringTokenizer tokenizer(arguments.toString());
		if (!tokenizer.hasMoreTokens()) {
			sendSyntax(creature);
			return 1;
		}

		String command;
		tokenizer.getStringToken(command);
		command = command.toLowerCase();

		if (command == "enable") {
			auctionManager->setMarketEnabled(true);
			creature->sendSystemMessage("Market Enabled");
		} else if (command == "disable") {
			auctionManager->setMarketEnabled(false);
			creature->sendSystemMessage("Market Disabled");
		} else if (command == "info") {
			auctionManager->displayInfo(creature);
		}

		return 0;
	}

	static void sendSyntax(CreatureObject* player) {
		if (player != NULL)
			player->sendSystemMessage("Syntax: /server market [enable/disable/info]");
	}

};

#endif /* MARKETCOMMAND_H_ */
