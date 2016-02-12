/*
 * CreatureRangedAttackCommand.h
 *
 *  Created on: Jan 13, 2013
 *      Author: root
 */

#ifndef CREATURERANGEDATTACKCOMMAND_H_
#define CREATURERANGEDATTACKCOMMAND_H_
#include "CombatQueueCommand.h"
class CreatureRangedAttackCommand : public CombatQueueCommand {
public:

	CreatureRangedAttackCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (weapon == NULL || !weapon->isRangedWeapon()) {
			return INVALIDWEAPON;
		}

		return doCombatAction(creature, target);
	}
};





#endif /* CREATURERANGEDATTACKCOMMAND_H_ */
