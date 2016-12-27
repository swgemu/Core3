/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNDOCK_H_
#define UNDOCK_H_

#include "CombatQueueCommand.h"

class UndockCommand : public CombatQueueCommand {
public:

	UndockCommand(const String& name, ZoneProcessServer* server)
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

#endif //UNDOCK_H_
