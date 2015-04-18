/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TARGETCOMMAND_H_
#define TARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TargetCommand : public QueueCommand {
public:

	TargetCommand(const String& name, ZoneProcessServer* server)
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

#endif //TARGETCOMMAND_H_
