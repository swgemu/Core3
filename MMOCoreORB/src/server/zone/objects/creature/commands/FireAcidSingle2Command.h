/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FIREACIDSINGLE2COMMAND_H_
#define FIREACIDSINGLE2COMMAND_H_

#include "CombatQueueCommand.h"

class FireAcidSingle2Command : public CombatQueueCommand {
public:

	FireAcidSingle2Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isHeavyAcidRifle())
			return INVALIDWEAPON;

		return doCombatAction(creature, target);
	}

};

#endif //FIREACIDSINGLE2COMMAND_H_
