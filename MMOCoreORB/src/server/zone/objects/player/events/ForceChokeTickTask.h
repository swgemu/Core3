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
	ManagedReference<CreatureObject*> creatureTarget;
	int counter;
public:

	ForceChokeTickTask(CreatureObject* creo, CreatureObject* creoTarget) {
		creature = creo;
		creatureTarget = creoTarget;
		counter = 0;
	}

	void run() {
		Locker locker(creature);

		if(creature != NULL && creatureTarget != NULL) {
			int amountOfTicks = 5;
			int damage = 500;

			if (counter < amountOfTicks && !creature->isIncapacitated() && !creature->isDead() && (creature->getPvpStatusBitmask() != CreatureFlag::NONE)) {

				creature->inflictDamage(creatureTarget, CreatureAttribute::HEALTH, (damage + System::random(200)), true);
				creature->inflictDamage(creatureTarget, CreatureAttribute::ACTION, (damage + System::random(200)), true);
				creature->inflictDamage(creatureTarget, CreatureAttribute::MIND, (damage + System::random(200)), true);

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
