/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABER1HFLURRY2COMMAND_H_
#define SABER1HFLURRY2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "CombatQueueCommand.h"

class Saber1hFlurry2Command : public CombatQueueCommand {
public:

	Saber1hFlurry2Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isJediOneHandedWeapon()) {
			return INVALIDWEAPON;
		}

		return doCombatAction(creature, target);
	}

};

#endif //SABER1HFLURRY2COMMAND_H_
