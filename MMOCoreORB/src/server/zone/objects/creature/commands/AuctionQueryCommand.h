/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AUCTIONQUERYCOMMAND_H_
#define AUCTIONQUERYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AuctionQueryCommand : public QueueCommand {
public:

	AuctionQueryCommand(const String& name, ZoneProcessServer* server)
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

#endif //AUCTIONQUERYCOMMAND_H_
