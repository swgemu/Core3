/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JSTART3_H_
#define JSTART3_H_

#include "CombatQueueCommand.h"

class Jstart3Command : public CombatQueueCommand {
public:

	Jstart3Command(const String& name, ZoneProcessServer* server)
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

#endif //JSTART3_H_
