/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BLEEDINGSHOTCOMMAND_H_
#define BLEEDINGSHOTCOMMAND_H_

#include "CombatQueueCommand.h"

class BleedingShotCommand : public CombatQueueCommand {
public:

	BleedingShotCommand(const String& name, ZoneProcessServer* server)
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

#endif //BLEEDINGSHOTCOMMAND_H_
