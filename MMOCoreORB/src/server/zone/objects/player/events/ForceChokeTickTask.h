/*
 * ForceChokeTickTask.h
 *
 *  Created on: Jan 28, 2016
 *      Author: swgemu Nee
 */

#ifndef FORCECHOKETICKTASK_H_
#define FORCECHOKETICKTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/combat/CreatureAttackData.h"

class ForceChokeTickTask : public Task {
	ManagedReference<CreatureObject*> creatureTarget;
	ManagedReference<CreatureObject*> creature;
	const static int amountOfTicks;
	int counter;
public:

	ForceChokeTickTask(CreatureObject* attacker, CreatureObject* defender, float damageMultiplier) {
		creature = attacker;
		creatureTarget = defender;
		counter = 0;
	}

	void run() {

		if(creatureTarget != NULL) {
			const static int amountOfTicks = 5;
			float damageMultiplier = System::random(9);
			int tickDamage = 175 + (damageMultiplier * 25);

			if (counter < amountOfTicks) {

				Locker locker (creatureTarget);
				// doCombatAction(creature, creatureTarget, arguments, weapon); ???
				creatureTarget->playEffect("clienteffect/pl_force_choke.cef", "");
				creatureTarget->sendSystemMessage("@combat_effects:choke_single"); // You are choking!

				counter++;

				this->reschedule(5000); // Reschedule in 5 seconds.
			}
			else {
				(creature->removePendingTask("forceChokeTickTask"));
			}

		}
	}
};

#endif /* FORCECHOKETICKTASK_H_ */
