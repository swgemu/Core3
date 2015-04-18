/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ITEMMOVEUPCOMMAND_H_
#define ITEMMOVEUPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ItemmoveupCommand : public QueueCommand {
public:

	ItemmoveupCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->executeObjectControllerAction(0x4B74A403, target, "up 10");

		return SUCCESS;
	}

};

#endif //ITEMMOVEUPCOMMAND_H_
