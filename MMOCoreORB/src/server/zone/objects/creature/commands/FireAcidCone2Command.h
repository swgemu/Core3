/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FIREACIDCONE2COMMAND_H_
#define FIREACIDCONE2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class FireAcidCone2Command : public CombatQueueCommand {
public:

	FireAcidCone2Command(const String& name, ZoneProcessServer* server)
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

#endif //FIREACIDCONE2COMMAND_H_
