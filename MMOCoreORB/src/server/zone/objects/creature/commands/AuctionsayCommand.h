/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AUCTIONSAYCOMMAND_H_
#define AUCTIONSAYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"

class AuctionsayCommand : public QueueCommand {
public:

	AuctionsayCommand(const String& name, ZoneProcessServer* server)
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

#endif //AUCTIONSAYCOMMAND_H_
