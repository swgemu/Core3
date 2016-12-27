/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNARMEDCOMBO1COMMAND_H_
#define UNARMEDCOMBO1COMMAND_H_

#include "CombatQueueCommand.h"

class UnarmedCombo1Command : public CombatQueueCommand {
public:

	UnarmedCombo1Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		float healthmod = (90.f - (float)System::random(50)) / 100.f;
		float actionmod = 0.1f;
		float mindmod = 1.f - healthmod - actionmod;

		UnicodeString args = "healthDamageMultiplier=" + String::valueOf(healthmod) + ";actionDamageMultiplier=" + String::valueOf(actionmod) + ";mindDamageMultiplier=" + String::valueOf(mindmod) + ";";

		return doCombatAction(creature, target, args);
	}

};

#endif //UNARMEDCOMBO1COMMAND_H_
