/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INITIALIZECOMPONENTCOMMAND_H_
#define INITIALIZECOMPONENTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class InitializeComponentCommand : public QueueCommand {
public:

	InitializeComponentCommand(const String& name, ZoneProcessServer* server)
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

#endif //INITIALIZECOMPONENTCOMMAND_H_
