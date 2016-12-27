/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FLUSHINGSHOT1COMMAND_H_
#define FLUSHINGSHOT1COMMAND_H_

#include "CombatQueueCommand.h"

class FlushingShot1Command : public CombatQueueCommand {
public:

	FlushingShot1Command(const String& name, ZoneProcessServer* server)
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

#endif //FLUSHINGSHOT1COMMAND_H_
