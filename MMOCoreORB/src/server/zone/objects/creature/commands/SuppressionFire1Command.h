/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SUPPRESSIONFIRE1COMMAND_H_
#define SUPPRESSIONFIRE1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class SuppressionFire1Command : public CombatQueueCommand {
public:

	SuppressionFire1Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target);
	}

};

#endif //SUPPRESSIONFIRE1COMMAND_H_
