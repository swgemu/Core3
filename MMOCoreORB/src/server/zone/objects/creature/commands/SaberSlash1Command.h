/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABERSLASH1COMMAND_H_
#define SABERSLASH1COMMAND_H_

#include "JediCombatQueueCommand.h"

class SaberSlash1Command : public JediCombatQueueCommand {
public:

	SaberSlash1Command(const String& name, ZoneProcessServer* server)
		: JediCombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		return doCombatAction(creature, target, "");
	}

	String getAnimation(TangibleObject* attacker, TangibleObject* defender, WeaponObject* weapon, uint8 hitLocation, int damage) const {

		String anim = "";
		if (weapon->isJediOneHandedWeapon()) {
			return "knockdown_1hmelee_1";
		} else if (weapon->isJediTwoHandedWeapon()) {
			return "knockdown_2hmelee_1";
		} else if (weapon->isJediPolearmWeapon()) {
			return "knockdown_polearm_1";
		} else {
			warning("Invalid weapon in saberSlash getAnimation");
			return "";
		}
	}

};

#endif //SABERSLASH1COMMAND_H_
