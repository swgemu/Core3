/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LEAVEGAMECOMMAND_H_
#define LEAVEGAMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LeaveGameCommand : public QueueCommand {
public:

	LeaveGameCommand(const String& name, ZoneProcessServer* server)
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

#endif //LEAVEGAMECOMMAND_H_
