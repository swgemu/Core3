/*
 * DizzyFallDownEvent.h
 *
 *  Created on: 02/06/2010
 *      Author: victor
 */

#ifndef DIZZYFALLDOWNEVENT_H_
#define DIZZYFALLDOWNEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"

class DizzyFallDownEvent : public Task {
	ManagedReference<CreatureObject*> creature;
public:

	DizzyFallDownEvent(CreatureObject* creat) {
		creature = creat;
	}

	void run() {
		Locker locker(creature);

		if (creature->isDizzied()) {
			creature->setPosture(CreaturePosture::KNOCKEDDOWN);
			creature->sendSystemMessage("@cbt_spam:dizzy_fall_down_single");
		}

		creature->removePendingTask("dizzyFallDownEvent");
	}
};


#endif /* DIZZYFALLDOWNEVENT_H_ */
