/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNARMEDSTUN1COMMAND_H_
#define UNARMEDSTUN1COMMAND_H_

#include "CombatQueueCommand.h"

class UnarmedStun1Command : public CombatQueueCommand {
public:

	UnarmedStun1Command(const String& name, ZoneProcessServer* server)
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

#endif //UNARMEDSTUN1COMMAND_H_
