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

	const static int TICKS_TO_REGEN = 10; // How many ticks will it take to get back to normal HAM.

	ChannelForceRegenTask(CreatureObject* creo, int bonus) {
		creature = creo;
		forceBonus = bonus;
		counter = 0;
	}

	void run() {
		Locker locker(creature);

		if(creature != NULL) {
			Locker locker(creature);
			int hamBack = round((float) forceBonus / (float) TICKS_TO_REGEN);
			int hamDiff = (counter == 10) ? ((int)forceBonus % TICKS_TO_REGEN) : ((int)forceBonus / TICKS_TO_REGEN);

			int maxHealth = creature->getMaxHAM(CreatureAttribute::HEALTH);
			int maxAction = creature->getMaxHAM(CreatureAttribute::ACTION);
			int maxMind = creature->getMaxHAM(CreatureAttribute::MIND);

			if (counter < TICKS_TO_REGEN) {
				creature->setMaxHAM(CreatureAttribute::HEALTH, maxHealth + hamBack, true);
				creature->setMaxHAM(CreatureAttribute::ACTION, maxAction + hamBack, true);
				creature->setMaxHAM(CreatureAttribute::MIND, maxMind + hamBack, true);

				counter++;
				this->reschedule(6000); // Reschedule in 6 seconds.
			}
			// 'Band-aid' temporary fix to keep from going into permanent negative modifiers when player is UN-buffed only...
			creature->setMaxHAM(CreatureAttribute::HEALTH, maxHealth + hamDiff, true);
			creature->setMaxHAM(CreatureAttribute::ACTION, maxAction + hamDiff, true);
			creature->setMaxHAM(CreatureAttribute::MIND, maxMind + hamDiff, true);

			creature->removePendingTask("channelForceRegenTask");
		}
	}
};

#endif /* CHANNELFORCEREGENTASK_H_ */
