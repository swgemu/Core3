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

			if (counter < amountOfTicks) {
				int maxHealth = creature->getMaxHAM(CreatureAttribute::HEALTH);
				int maxAction = creature->getMaxHAM(CreatureAttribute::ACTION);
				int maxMind = creature->getMaxHAM(CreatureAttribute::MIND);

				creature->setMaxHAM(CreatureAttribute::HEALTH, maxHealth + hamBack, true);
				creature->setMaxHAM(CreatureAttribute::ACTION, maxAction + hamBack, true);
				creature->setMaxHAM(CreatureAttribute::MIND, maxMind + hamBack, true);

				counter++;

				this->reschedule(6000); // Reschedule in 6 seconds...
			}
			else {

				creature->removePendingTask("channelForceRegenTask");
			}
		}
	}
};


#endif /* CHANNELFORCEREGENTASK_H_ */
