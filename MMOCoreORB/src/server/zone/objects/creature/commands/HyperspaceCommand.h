/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HYPERSPACE_H_
#define HYPERSPACE_H_

#include "CombatQueueCommand.h"

class HyperspaceCommand : public CombatQueueCommand {
public:

	HyperspaceCommand(const String& name, ZoneProcessServer* server)
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

#endif //HYPERSPACE_H_
