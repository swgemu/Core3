/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABERPOLEARMDERVISHCOMMAND_H_
#define SABERPOLEARMDERVISHCOMMAND_H_

#include "JediCombatQueueCommand.h"

class SaberPolearmDervishCommand : public JediCombatQueueCommand {
public:

	SaberPolearmDervishCommand(const String& name, ZoneProcessServer* server)
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

#endif //SABERPOLEARMDERVISHCOMMAND_H_
