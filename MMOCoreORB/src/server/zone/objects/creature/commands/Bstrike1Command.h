/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BSTRIKE1_H_
#define BSTRIKE1_H_

#include "CombatQueueCommand.h"

class Bstrike1Command : public CombatQueueCommand {
public:

	Bstrike1Command(const String& name, ZoneProcessServer* server)
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

#endif //BSTRIKE1_H_
