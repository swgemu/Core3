/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNARMEDCOMBO2COMMAND_H_
#define UNARMEDCOMBO2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class UnarmedCombo2Command : public CombatQueueCommand {
public:

	UnarmedCombo2Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isUnarmedWeapon()) {
			return INVALIDWEAPON;
		}

		float healthmod = System::random(70) + 10;
		float actionmod = System::random(70) + 10;
		float mindmod = System::random(70) + 10;

		int total = healthmod + actionmod + mindmod;

		healthmod /= total;
		actionmod /= total;
		mindmod /= total;

		UnicodeString args = "healthDamageMultiplier=" + String::valueOf(healthmod) + ";actionDamageMultiplier=" + String::valueOf(actionmod) + ";mindDamageMultiplier=" + String::valueOf(mindmod) + ";";

		return doCombatAction(creature, target, args);
	}

};

#endif //UNARMEDCOMBO2COMMAND_H_
