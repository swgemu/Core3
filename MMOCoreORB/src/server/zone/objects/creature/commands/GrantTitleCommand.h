/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GRANTTITLECOMMAND_H_
#define GRANTTITLECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GrantTitleCommand : public QueueCommand {
public:

	GrantTitleCommand(const String& name, ZoneProcessServer* server)
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

#endif //GRANTTITLECOMMAND_H_
