/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MELEE2HAREA1COMMAND_H_
#define MELEE2HAREA1COMMAND_H_

#include "CombatQueueCommand.h"

class Melee2hArea1Command : public CombatQueueCommand {
public:

	Melee2hArea1Command(const String& name, ZoneProcessServer* server)
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

#endif //MELEE2HAREA1COMMAND_H_
