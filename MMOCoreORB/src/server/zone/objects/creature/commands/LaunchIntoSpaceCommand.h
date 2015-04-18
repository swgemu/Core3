/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LAUNCHINTOSPACECOMMAND_H_
#define LAUNCHINTOSPACECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LaunchIntoSpaceCommand : public QueueCommand {
public:

	LaunchIntoSpaceCommand(const String& name, ZoneProcessServer* server)
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

#endif //LAUNCHINTOSPACECOMMAND_H_

