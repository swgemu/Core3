/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FULLAUTOSINGLE1COMMAND_H_
#define FULLAUTOSINGLE1COMMAND_H_

#include "CombatQueueCommand.h"

class FullAutoSingle1Command : public CombatQueueCommand {
public:

	FullAutoSingle1Command(const String& name, ZoneProcessServer* server)
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

#endif //FULLAUTOSINGLE1COMMAND_H_
