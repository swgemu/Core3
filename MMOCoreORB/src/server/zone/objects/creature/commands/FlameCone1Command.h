/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FLAMECONE1COMMAND_H_
#define FLAMECONE1COMMAND_H_

#include "CombatQueueCommand.h"

class FlameCone1Command : public CombatQueueCommand {
public:

	FlameCone1Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isFlameThrower())
			return INVALIDWEAPON;

		return doCombatAction(creature, target);
	}
};
#endif //FLAMECONE1COMMAND_H_
