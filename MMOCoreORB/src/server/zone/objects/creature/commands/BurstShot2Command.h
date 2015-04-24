/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BURSTSHOT2COMMAND_H_
#define BURSTSHOT2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class BurstShot2Command : public CombatQueueCommand {
public:

	BurstShot2Command(const String& name, ZoneProcessServer* server)
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

#endif //BURSTSHOT2COMMAND_H_
