/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FLUSHINGSHOT2COMMAND_H_
#define FLUSHINGSHOT2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class FlushingShot2Command : public CombatQueueCommand {
public:

	FlushingShot2Command(const String& name, ZoneProcessServer* server)
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

#endif //FLUSHINGSHOT2COMMAND_H_
