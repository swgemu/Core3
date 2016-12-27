/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DOUBLETAPCOMMAND_H_
#define DOUBLETAPCOMMAND_H_

#include "CombatQueueCommand.h"

class DoubleTapCommand : public CombatQueueCommand {
public:

	DoubleTapCommand(const String& name, ZoneProcessServer* server)
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

#endif //DOUBLETAPCOMMAND_H_
