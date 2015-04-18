/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ITEMROTATELEFTCOMMAND_H_
#define ITEMROTATELEFTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ItemrotateleftCommand : public QueueCommand {
public:

	ItemrotateleftCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->executeObjectControllerAction(0xA8EB1D48, target, "left 45");

		return SUCCESS;
	}

};

#endif //ITEMROTATELEFTCOMMAND_H_
