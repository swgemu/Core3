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
	static const int LANDEDTIME = 30000; //In milliseconds
	static const int DEPARTEDTIME = 120000; //In milliseconds

public:
	ShuttleDepartureTask(CreatureObject* shuttle) : Task() {
		shuttleObject = shuttle;
	}

	void run() {
		if (shuttleObject == NULL) {
			cancel();
			return;
		}

		Locker _lock(shuttleObject);

		if (shuttleObject->isStanding()) {
			shuttleObject->info("Shuttle is departing", true);
			shuttleObject->setPosture(CreaturePosture::PRONE);
			reschedule(DEPARTEDTIME);
		} else {
			shuttleObject->info("Shuttle is landing", true);
			shuttleObject->setPosture(CreaturePosture::UPRIGHT);
			reschedule(LANDEDTIME);
		}
	}

	void landShuttle() {

	}

	void departShuttle() {

	}
};

#endif /* SHUTTLEDEPARTURETASK_H_ */
