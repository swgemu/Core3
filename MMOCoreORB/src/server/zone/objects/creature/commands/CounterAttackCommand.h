/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COUNTERATTACKCOMMAND_H_
#define COUNTERATTACKCOMMAND_H_

#include "CombatQueueCommand.h"

class CounterAttackCommand : public CombatQueueCommand {
public:

	CounterAttackCommand(const String& name, ZoneProcessServer* server)
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

#endif //COUNTERATTACKCOMMAND_H_
