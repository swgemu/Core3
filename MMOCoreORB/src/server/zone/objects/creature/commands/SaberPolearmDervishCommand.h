/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABERPOLEARMDERVISHCOMMAND_H_
#define SABERPOLEARMDERVISHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class SaberPolearmDervishCommand : public CombatQueueCommand {
public:

	SaberPolearmDervishCommand(const String& name, ZoneProcessServer* server)
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


		if (!weapon->isJediPolearmWeapon()) {
			return INVALIDWEAPON;
		}

		return doCombatAction(creature, target);
	}

};

#endif //SABERPOLEARMDERVISHCOMMAND_H_
