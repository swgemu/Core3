/*
 * ForceChokeTickTask.h
 *
 *  Created on: Jan 28, 2016
 *      Author: swgemu Nee
 */

#ifndef FORCECHOKETICKTASK_H_
#define FORCECHOKETICKTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

class ForceChokeTickTask : public Task {
	ManagedReference<CreatureObject*> creatureTarget;
	ManagedReference<CreatureObject*> creature;
	int tickDamage;
	int counter;
public:

	ForceChokeTickTask(CreatureObject* attacker, int damage) {
		creature = attacker;
		tickDamage = damage;
		counter = 0;
	}

	void run() {
		Locker crossLocker(creatureTarget, creature);

		if(creatureTarget != NULL) {
			const static int amountOfTicks = 6;
			int damage = System::random(10);
			int tickDamage = 100 + (damage * 40);
			int newTick = round((float) tickDamage / (float) amountOfTicks);
			Reference<CreatureObject*> attackerRef = creature;
			Reference<CreatureObject*> victimRef = creatureTarget;

			if (counter < amountOfTicks) {

				victimRef->inflictDamage(attackerRef, CreatureAttribute::HEALTH, newTick, true);
				creatureTarget->sendSystemMessage("@combat_effects:choke_single"); // You are choking!

				if (creatureTarget->hasAttackDelay())
					creatureTarget->removeAttackDelay();

				counter++;

				this->reschedule(6000); // Reschedule in 6 seconds.
			}
			else {
				(creature->removePendingTask("forceChokeTickTask"));
			}

		}
	}
};

#endif /* FORCECHOKETICKTASK_H_ */
