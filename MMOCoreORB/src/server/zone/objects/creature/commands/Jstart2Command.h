/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JSTART2_H_
#define JSTART2_H_

#include "CombatQueueCommand.h"

class Jstart2Command : public CombatQueueCommand {
public:

	Jstart2Command(const String& name, ZoneProcessServer* server)
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

#endif //JSTART2_H_
