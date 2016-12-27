/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EPULSE2_H_
#define EPULSE2_H_

#include "CombatQueueCommand.h"

class Epulse2Command : public CombatQueueCommand {
public:

	Epulse2Command(const String& name, ZoneProcessServer* server)
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

#endif //EPULSE2_H_
