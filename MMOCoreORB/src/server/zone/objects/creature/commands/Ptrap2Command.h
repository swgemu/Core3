/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PTRAP2_H_
#define PTRAP2_H_

#include "CombatQueueCommand.h"

class Ptrap2Command : public CombatQueueCommand {
public:

	Ptrap2Command(const String& name, ZoneProcessServer* server)
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

#endif //PTRAP2_H_
