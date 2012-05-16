/*
 * ChannelForceRegenTask.h
 *
 *  Created on: Aug 18, 2011
 *      Author: swgemu
 */

#ifndef FORCECHOKETICKTASK_H_
#define FORCECHOKETICKTASK_H_


#include "server/zone/objects/creature/CreatureObject.h"

class ForceChokeTickTask : public Task {
	ManagedReference<CreatureObject*> creature;
	int counter;
public:

	ForceChokeTickTask(CreatureObject* creo) {
		creature = creo;
		counter = 0;
	}

	void run() {
		Locker locker(creature);

		if(creature != NULL) {
			int amountOfTicks = 5;
			int damage = System::random(2000) + 1000;

			if (!creature->isAiAgent())
				damage *= 0.25; // Player reduction.


			if (counter < amountOfTicks && !creature->isIncapacitated() && !creature->isDead()) {

				creature->inflictDamage(creature, CreatureAttribute::HEALTH, damage, true);
				creature->inflictDamage(creature, CreatureAttribute::ACTION, damage, true);
				creature->inflictDamage(creature, CreatureAttribute::MIND, damage, true);

				this->reschedule(6000); // Reschedule in 6 seconds...

				creature->playEffect("clienteffect/pl_force_choke.cef", "");

				counter++;
			}
			else {

				creature->removePendingTask("forceChokeTickTask");
			}
		}
	}
};


#endif /* CHANNELFORCEREGENTASK_H_ */
