/*
 * ShuttleDepartureTask.h
 *
 *  Created on: Aug 19, 2011
 *      Author: crush
 */

#ifndef SHUTTLEDEPARTURETASK_H_
#define SHUTTLEDEPARTURETASK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/engine.h"

class ShuttleDepartureTask : public Task {
	ManagedWeakReference<CreatureObject*> shuttleObject;

public:
	static const int LANDINGTIME = 15; //How long the landing animation takes to complete in seconds.
	static const int LANDEDTIME = 120; //In seconds
	static const int DEPARTEDTIME = 300; //In seconds

public:
	ShuttleDepartureTask(CreatureObject* shuttle) : Task() {
		shuttleObject = shuttle;
	}

	void run() {
		if (shuttleObject == NULL) {
			//cancel();
			return;
		}

		Locker _lock(shuttleObject);

		if (shuttleObject->isStanding()) {
			shuttleObject->setPosture(CreaturePosture::PRONE);
			reschedule(DEPARTEDTIME * 1000);
		} else {
			shuttleObject->setPosture(CreaturePosture::UPRIGHT);
			reschedule((LANDEDTIME + LANDINGTIME) * 1000);
		}
	}

	int getSecondsRemaining() {
		int seconds = (int) getNextExecutionTime().miliDifference() / 1000.f * -1;

		return seconds;
	}

	bool isLanded() {
		if (!shuttleObject->isStanding())
			return false;

		//Make sure the shuttle isn't still landing
		if ((LANDEDTIME - getSecondsRemaining()) <= LANDINGTIME)
			return false;

		return true;
	}

	bool isLanding() {
		if (shuttleObject->isStanding() && (LANDEDTIME - getSecondsRemaining()) <= LANDINGTIME)
			return true;

		return false;
	}
};

#endif /* SHUTTLEDEPARTURETASK_H_ */
