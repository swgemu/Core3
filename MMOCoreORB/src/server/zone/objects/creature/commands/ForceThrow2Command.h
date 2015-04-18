/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCETHROW2COMMAND_H_
#define FORCETHROW2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class ForceThrow2Command : public ForcePowersQueueCommand {
public:

	ForceThrow2Command(const String& name, ZoneProcessServer* server)
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

#endif //FORCETHROW2COMMAND_H_
