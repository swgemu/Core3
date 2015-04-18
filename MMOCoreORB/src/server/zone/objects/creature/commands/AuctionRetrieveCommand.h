/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AUCTIONRETRIEVECOMMAND_H_
#define AUCTIONRETRIEVECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AuctionRetrieveCommand : public QueueCommand {
public:

	AuctionRetrieveCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //AUCTIONRETRIEVECOMMAND_H_
