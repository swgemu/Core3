/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DISARMINGSHOT2COMMAND_H_
#define DISARMINGSHOT2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class DisarmingShot2Command : public CombatQueueCommand {
public:

	DisarmingShot2Command(const String& name, ZoneProcessServer* server)
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

#endif //DISARMINGSHOT2COMMAND_H_
