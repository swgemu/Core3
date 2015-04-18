/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AUCTIONCREATECOMMAND_H_
#define AUCTIONCREATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AuctionCreateCommand : public QueueCommand {
public:

	AuctionCreateCommand(const String& name, ZoneProcessServer* server)
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

#endif //AUCTIONCREATECOMMAND_H_
