/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STARTLESHOT1COMMAND_H_
#define STARTLESHOT1COMMAND_H_

#include "CombatQueueCommand.h"

class StartleShot1Command : public CombatQueueCommand {
public:

	StartleShot1Command(const String& name, ZoneProcessServer* server)
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

#endif //STARTLESHOT1COMMAND_H_
