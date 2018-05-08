/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FASTBLASTCOMMAND_H_
#define FASTBLASTCOMMAND_H_

#include "CombatQueueCommand.h"

class FastBlastCommand : public CombatQueueCommand {
public:

	FastBlastCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

			if (!checkStateMask(creature))
				return INVALIDSTATE;

			if (!checkInvalidLocomotions(creature))
				return INVALIDLOCOMOTION;

					UnicodeString args = "healthDamageMultiplier=0.34f;actionDamageMultiplier=0.34f;mindDamageMultiplier=0.34f;";

			return doCombatAction(creature, target, args);
		}

	};

#endif //FASTBLASTCOMMAND_H_
