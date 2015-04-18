/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABERSLASH1COMMAND_H_
#define SABERSLASH1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class SaberSlash1Command : public CombatQueueCommand {
public:

	SaberSlash1Command(const String& name, ZoneProcessServer* server)
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
		String animCRC = "";

		if (weapon->isJediOneHandedWeapon()) {
			animCRC = "knockdown_1hmelee_1";
		} else if (weapon->isJediTwoHandedWeapon()) {
			animCRC = "knockdown_2hmelee_1";
		} else if (weapon->isJediPolearmWeapon()) {
			animCRC = "knockdown_polearm_1";
		} else {
			return INVALIDWEAPON;
		}

		UnicodeString args = "animationCRC=" + String::valueOf(animCRC.hashCode()) + ";";

		return doCombatAction(creature, target, args);
	}

};

#endif //SABERSLASH1COMMAND_H_
