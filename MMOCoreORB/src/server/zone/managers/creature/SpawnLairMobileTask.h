/*
 * SpawnLairMobileTask.h
 *
 * Created on: 2024-07-06
 * Author: Hakry
 */

#ifndef SPAWNLAIRMOBILETASK_H_
#define SPAWNLAIRMOBILETASK_H_

#include "server/zone/objects/tangible/LairObject.h"
#include "server/zone/managers/creature/LairObserver.h"

class SpawnLairMobileTask : public Task {
	ManagedWeakReference<LairObject*> lairWeak;
	int spawnNumber;
	String mobileString;
	bool spawnPassive;

public:
	SpawnLairMobileTask(LairObject* lair, int spawnNum, String mobileStr, bool passive) {
		lairWeak = lair;
		spawnNumber = spawnNum;
		mobileString = mobileStr;
		spawnPassive = passive;
	}

	void run() {
		auto lairObject = lairWeak.get();

		if (lairObject == nullptr) {
			return;
		}

		if (lairObject->getZone() == nullptr) {
			return;
		}

		// lairObject->info(true) << "spawn lair mobile called for Lair: " << lairObject->getDisplayedName() << " ID: " << lairObject->getObjectID() << " Position: " << lairObject->getPosition().toString();

		Locker lock(lairObject);

		ManagedReference<LairObserver*> lairObserver = nullptr;
		SortedVector<ManagedReference<Observer*>> observers = lairObject->getObservers(ObserverEventType::OBJECTDESTRUCTION);

		for (int i = 0; i < observers.size(); i++) {
			lairObserver = cast<LairObserver*>(observers.get(i).get());

			if (lairObserver != nullptr) {
				break;
			}
		}

		if (lairObserver == nullptr) {
			return;
		}

		lairObserver->spawnLairMobile(lairObject, spawnNumber, mobileString, spawnPassive);
	}
};

#endif /* SPAWNLAIRMOBILETASK_H_ */