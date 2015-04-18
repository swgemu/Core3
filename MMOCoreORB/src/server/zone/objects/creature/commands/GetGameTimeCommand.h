/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETGAMETIMECOMMAND_H_
#define GETGAMETIMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GetGameTimeCommand : public QueueCommand {
public:

	GetGameTimeCommand(const String& name, ZoneProcessServer* server)
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

#endif //GETGAMETIMECOMMAND_H_
