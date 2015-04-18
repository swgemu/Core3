/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ITEMMOVEBACKCOMMAND_H_
#define ITEMMOVEBACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ItemmovebackCommand : public QueueCommand {
public:

	ItemmovebackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->executeObjectControllerAction(0x4B74A403, target, "back 10");

		return SUCCESS;
	}

};

#endif //ITEMMOVEBACKCOMMAND_H_
