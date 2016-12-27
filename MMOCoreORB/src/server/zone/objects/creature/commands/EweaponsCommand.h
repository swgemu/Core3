/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EWEAPONS_H_
#define EWEAPONS_H_

#include "CombatQueueCommand.h"

class EweaponsCommand : public CombatQueueCommand {
public:

	EweaponsCommand(const String& name, ZoneProcessServer* server)
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

#endif //EWEAPONS_H_
