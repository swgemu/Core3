/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FIREACIDSINGLE1COMMAND_H_
#define FIREACIDSINGLE1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class FireAcidSingle1Command : public CombatQueueCommand {
public:

	FireAcidSingle1Command(const String& name, ZoneProcessServer* server)
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

#endif //FIREACIDSINGLE1COMMAND_H_
