/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABERPOLEARMSPINATTACK2COMMAND_H_
#define SABERPOLEARMSPINATTACK2COMMAND_H_

#include "JediCombatQueueCommand.h"

class SaberPolearmSpinAttack2Command : public JediCombatQueueCommand {
public:

	SaberPolearmSpinAttack2Command(const String& name, ZoneProcessServer* server)
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

#endif //SABERPOLEARMSPINATTACK2COMMAND_H_
