/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABER2HPHANTOMCOMMAND_H_
#define SABER2HPHANTOMCOMMAND_H_

#include "JediCombatQueueCommand.h"

class Saber2hPhantomCommand : public JediCombatQueueCommand {
public:

	Saber2hPhantomCommand(const String& name, ZoneProcessServer* server)
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

#endif //SABER2HPHANTOMCOMMAND_H_
