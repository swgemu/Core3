/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABER2HBODYHIT3COMMAND_H_
#define SABER2HBODYHIT3COMMAND_H_

#include "JediCombatQueueCommand.h"

class Saber2hBodyHit3Command : public JediCombatQueueCommand {
public:

	Saber2hBodyHit3Command(const String& name, ZoneProcessServer* server)
		: JediCombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		return doCombatAction(creature, target);
	}

};

#endif //SABER2HBODYHIT3COMMAND_H_
