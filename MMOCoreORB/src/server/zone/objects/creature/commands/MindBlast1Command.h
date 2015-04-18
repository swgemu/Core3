/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MINDBLAST1COMMAND_H_
#define MINDBLAST1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class MindBlast1Command : public ForcePowersQueueCommand {
public:

	MindBlast1Command(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		return doCombatAction(creature, target);
	}

};

#endif //MINDBLAST1COMMAND_H_
