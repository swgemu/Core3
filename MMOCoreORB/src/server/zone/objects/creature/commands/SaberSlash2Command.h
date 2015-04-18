/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABERSLASH2COMMAND_H_
#define SABERSLASH2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class SaberSlash2Command : public CombatQueueCommand {
public:

	SaberSlash2Command(const String& name, ZoneProcessServer* server)
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

#endif //SABERSLASH2COMMAND_H_
