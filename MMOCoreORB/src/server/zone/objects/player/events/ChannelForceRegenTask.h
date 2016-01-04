/*
 * ChannelForceRegenTask.h
 *
 *  Created on: Aug 18, 2011
 *      Author: swgemu
 */

#ifndef CHANNELFORCEREGENTASK_H_
#define CHANNELFORCEREGENTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

class ChannelForceRegenTask : public Task {
	ManagedReference<CreatureObject*> creature;
	int forceBonus;
	int counter;
public:

	ChannelForceRegenTask(CreatureObject* creo, int bonus) {
		creature = creo;
		forceBonus = bonus;
		counter = 0;
	}

	void run() {
		Locker locker(creature);

		if(creature != NULL) {
			const static int amountOfTicks = 10; // How many ticks will it take to get back to normal HAM.
			int hamBack = round((float) forceBonus / (float) amountOfTicks);
			int origHealth = creature->getMaxHAM(CreatureAttribute::HEALTH);
			int origAction = creature->getMaxHAM(CreatureAttribute::ACTION);
			int origMind = creature->getMaxHAM(CreatureAttribute::MIND);

			if (counter < amountOfTicks) {
				int currentHealth = creature->getMaxHAM(CreatureAttribute::HEALTH);
				int currentAction = creature->getMaxHAM(CreatureAttribute::ACTION);
				int currentMind = creature->getMaxHAM(CreatureAttribute::MIND);

				creature->setMaxHAM(CreatureAttribute::HEALTH, currentHealth + hamBack, true);
				creature->setMaxHAM(CreatureAttribute::ACTION, currentAction + hamBack, true);
				creature->setMaxHAM(CreatureAttribute::MIND, currentMind + hamBack, true);

				counter++;

				this->reschedule(6000); // Reschedule in 6 seconds...

				if (currentHealth < origHealth && currentAction < origAction && currentMind < origMind) {
					creature->setMaxHAM(CreatureAttribute::HEALTH, origHealth - hamBack, true);
					creature->setMaxHAM(CreatureAttribute::ACTION, origAction - hamBack, true);
					creature->setMaxHAM(CreatureAttribute::MIND, origMind - hamBack, true);
				} else {
					if (currentHealth > origHealth && currentAction > origAction && currentMind > origMind) {
						creature->setMaxHAM(CreatureAttribute::HEALTH, origHealth, true);
						creature->setMaxHAM(CreatureAttribute::ACTION, origAction, true);
						creature->setMaxHAM(CreatureAttribute::MIND, origMind, true);
					}
				}
			}
			else {
				creature->removePendingTask("channelForceRegenTask");
			}
		}
	}
};

#endif /* CHANNELFORCEREGENTASK_H_ */
