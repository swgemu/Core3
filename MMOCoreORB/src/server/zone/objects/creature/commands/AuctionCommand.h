/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AUCTIONCOMMAND_H_
#define AUCTIONCOMMAND_H_

#include "server/chat/ChatManager.h"

class AuctionCommand : public QueueCommand {
public:

	AuctionCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ChatManager* chatManager = server->getZoneServer()->getChatManager();
		chatManager->handleAuctionChat( creature, arguments);

		return SUCCESS;
	}

};

#endif //AUCTIONCOMMAND_H_
