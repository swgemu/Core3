/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPCRAFTINGSESSIONCOMMAND_H_
#define STOPCRAFTINGSESSIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class StopCraftingSessionCommand : public QueueCommand {
public:

	StopCraftingSessionCommand(const String& name, ZoneProcessServer* server)
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

#endif //STOPCRAFTINGSESSIONCOMMAND_H_
