/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALTHSHOT2COMMAND_H_
#define HEALTHSHOT2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class HealthShot2Command : public CombatQueueCommand {
public:

	HealthShot2Command(const String& name, ZoneProcessServer* server)
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

#endif //HEALTHSHOT2COMMAND_H_
