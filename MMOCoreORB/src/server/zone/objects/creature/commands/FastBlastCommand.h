/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FASTBLASTCOMMAND_H_
#define FASTBLASTCOMMAND_H_

#include "CombatQueueCommand.h"

class FastBlastCommand : public CombatQueueCommand {
public:

	FastBlastCommand(const String& name, ZoneProcessServer* server)
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

#endif //FASTBLASTCOMMAND_H_
