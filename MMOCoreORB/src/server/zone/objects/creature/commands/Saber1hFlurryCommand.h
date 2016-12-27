/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABER1HFLURRYCOMMAND_H_
#define SABER1HFLURRYCOMMAND_H_

#include "JediCombatQueueCommand.h"

class Saber1hFlurryCommand : public JediCombatQueueCommand {
public:

	Saber1hFlurryCommand(const String& name, ZoneProcessServer* server)
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

#endif //SABER1HFLURRYCOMMAND_H_
