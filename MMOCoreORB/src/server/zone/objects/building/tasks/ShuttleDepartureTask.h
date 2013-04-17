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

protected:
	int landedTime; //In seconds
	int landingTime; //How long the landing animation takes to complete in seconds.
	int departedTime; //In seconds

public:
	enum shuttleType {SHUTTLEPORT = 0, STARPORT} thisShuttleType;

public:
	ShuttleDepartureTask(CreatureObject* shuttle, shuttleType type) : Task() {
		landedTime = 120;
		shuttleObject = shuttle;
		thisShuttleType = type;

		switch (thisShuttleType) {
		case SHUTTLEPORT:
			departedTime = 300;
			landingTime = 11;
			break;
		case STARPORT:
			departedTime = 60;
			landingTime = 14;
			break;
		}

	}

	void run() {
		ManagedReference<CreatureObject*> strongReference = shuttleObject.get();

		if (strongReference == NULL) {
			return;
		}

		Locker _lock(strongReference);

		if (strongReference->isStanding()) {
			strongReference->setPosture(CreaturePosture::PRONE);
			reschedule(departedTime * 1000);
		} else {
			strongReference->setPosture(CreaturePosture::UPRIGHT);
			reschedule((landedTime + landingTime) * 1000);
		}
	}

	int getSecondsRemaining() {
		int seconds = (int) (getNextExecutionTime().miliDifference() / 1000.f * -1) + 1;

		return seconds;
	}

	bool isLanded() {
		ManagedReference<CreatureObject*> strongReference = shuttleObject.get();

		if (strongReference == NULL) {
			return false;
		}

		if (!strongReference->isStanding())
			return false;

		//Make sure the shuttle isn't still landing
		if ((landedTime - getSecondsRemaining()) <= landingTime)
			return false;

		return true;
	}

	bool isLanding() {
		ManagedReference<CreatureObject*> strongReference = shuttleObject.get();

		if (strongReference == NULL) {
			return false;
		}

		if (strongReference->isStanding() && (landedTime - getSecondsRemaining()) <= landingTime)
			return true;

		return false;
	}

	int getLandingTime() {
		return landingTime;
	}

	int getLandedTime() {
		return landedTime;
	}

	int getDepartedTime() {
		return departedTime;
	}
};

#endif /* SHUTTLEDEPARTURETASK_H_ */
