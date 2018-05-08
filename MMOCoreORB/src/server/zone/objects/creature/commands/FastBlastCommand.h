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

			float mods[3] = {0.f, 0.f, 0.f};

			for (int i = 0; i < 3; i++)
				mods[System::random(2)];

			UnicodeString args = "healthDamageMultiplier=0.33f;actionDamageMultiplier=0.33f;mindDamageMultiplier=0.33f;";

			return doCombatAction(creature, target, args);
		}

	};

#endif //FASTBLASTCOMMAND_H_
