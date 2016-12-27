/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LASTDITCHCOMMAND_H_
#define LASTDITCHCOMMAND_H_

#include "CombatQueueCommand.h"

class LastDitchCommand : public CombatQueueCommand {
public:

	LastDitchCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		int dmg = doCombatAction(creature, target);

		return dmg;
	}

};

#endif //LASTDITCHCOMMAND_H_
