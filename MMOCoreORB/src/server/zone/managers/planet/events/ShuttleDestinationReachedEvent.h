/*
 * ShuttleDestinationReachedEvent.h
 *
 *  Created on: Apr 13, 2011
 *      Author: crush
 */

#ifndef SHUTTLEDESTINATIONREACHEDEVENT_H_
#define SHUTTLEDESTINATIONREACHEDEVENT_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"

//Landing = posture 0 - Standing
//Takeoff = posture 2 - Prone

class ShuttleDestinationReachedEvent : public Task {
	ManagedReference<CreatureObject*> shuttleObject;

public:
	ShuttleDestinationReachedEvent(CreatureObject* shuttle) : Task() {
		shuttleObject = shuttle;
	}

	void run() {
		if (shuttleObject->isStanding()) { //Shuttle is landed
			shuttleObject->setPosture(CreaturePosture::PRONE);
			reschedule(300000);
		} else { //Shuttle is flying
			shuttleObject->setPosture(CreaturePosture::UPRIGHT);
			reschedule(90000);
		}
	}
};


#endif /* SHUTTLEDESTINATIONREACHEDEVENT_H_ */
