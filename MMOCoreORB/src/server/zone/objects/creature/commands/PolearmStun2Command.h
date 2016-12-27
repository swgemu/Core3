/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POLEARMSTUN2COMMAND_H_
#define POLEARMSTUN2COMMAND_H_

#include "CombatQueueCommand.h"

class PolearmStun2Command : public CombatQueueCommand {
public:

	PolearmStun2Command(const String& name, ZoneProcessServer* server)
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

#endif //POLEARMSTUN2COMMAND_H_
