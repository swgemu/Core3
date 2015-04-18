/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SABER2HPHANTOMCOMMAND_H_
#define SABER2HPHANTOMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "CombatQueueCommand.h"

class Saber2hPhantomCommand : public CombatQueueCommand {
public:

	Saber2hPhantomCommand(const String& name, ZoneProcessServer* server)
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


		if (!weapon->isJediTwoHandedWeapon()) {
			return INVALIDWEAPON;
		}

		return doCombatAction(creature, target);
	}

};

#endif //SABER2HPHANTOMCOMMAND_H_
