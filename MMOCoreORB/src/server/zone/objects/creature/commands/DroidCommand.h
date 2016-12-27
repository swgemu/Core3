/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROID_H_
#define DROID_H_

#include "CombatQueueCommand.h"

class DroidCommand : public CombatQueueCommand {
public:

	DroidCommand(const String& name, ZoneProcessServer* server)
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

#endif //DROID_H_
