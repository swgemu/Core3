/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FLAMECONE2COMMAND_H_
#define FLAMECONE2COMMAND_H_

#include "CombatQueueCommand.h"

class FlameCone2Command : public CombatQueueCommand {
public:

	FlameCone2Command(const String& name, ZoneProcessServer* server)
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

#endif //FLAMECONE2COMMAND_H_
