/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PTRAP1_H_
#define PTRAP1_H_

#include "CombatQueueCommand.h"

class Ptrap1Command : public CombatQueueCommand {
public:

	Ptrap1Command(const String& name, ZoneProcessServer* server)
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

#endif //PTRAP1_H_
