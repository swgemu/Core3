#ifndef LAIRREPOPULATETASK_H_
#define LAIRREPOPULATETASK_H_

#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/tangible/TangibleObject.h"


class LairRepopulateTask : public Task {

	ManagedWeakReference<TangibleObject*> lair;
	ManagedWeakReference<LairObserver*> observer;

public:

	LairRepopulateTask(TangibleObject* obj, LairObserver* observer) {
		lair = obj;
		this->observer = observer;

	}

	void run() {
		ManagedReference<TangibleObject*> strongRef = lair.get();
		ManagedReference<LairObserver*> strongObserver = observer.get();


		if (strongRef == nullptr || strongObserver == nullptr || strongObserver->getRespawnNumber() > 0) {
			return;
		}

		if (strongObserver->getLivingCreatureCount() <= 0) {
			return;
		}

		if (strongRef->getConditionDamage() < strongRef->getMaxCondition() * 0.5) {
			reschedule(10 * 1000);
			return;
		}

		Zone* zone = strongRef->getZone();

		if (zone == nullptr) {
			return;
		}

		Reference<SortedVector<ManagedReference<QuadTreeEntry*> >*> playerObjects = new SortedVector<ManagedReference<QuadTreeEntry*> >();

		int players = zone->getInRangePlayers(strongRef->getPositionX(), strongRef->getPositionY(), 150.0f, playerObjects); //Player check within 150m

		if (players >= 1) {
			reschedule(60 * 1000);
			return;
		}

		Locker locker(strongRef);

		strongObserver->repopulateLair(strongRef);
	}
};

#endif /* LAIRREPOPULATETASK_H_ */