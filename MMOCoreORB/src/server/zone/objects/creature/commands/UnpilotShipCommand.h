/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNPILOTSHIP_H_
#define UNPILOTSHIP_H_

#include "CombatQueueCommand.h"

class UnpilotShipCommand : public CombatQueueCommand {
public:

	UnpilotShipCommand(const String& name, ZoneProcessServer* server)
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

#endif //UNPILOTSHIP_H_
