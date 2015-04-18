/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LAUNCHFIREWORKCOMMAND_H_
#define LAUNCHFIREWORKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LaunchFireworkCommand : public QueueCommand {
public:

	LaunchFireworkCommand(const String& name, ZoneProcessServer* server)
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

#endif //LAUNCHFIREWORKCOMMAND_H_
