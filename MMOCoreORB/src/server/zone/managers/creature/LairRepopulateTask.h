#ifndef LAIRREPOPULATETASK_H_
#define LAIRREPOPULATETASK_H_

#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class LairRepopulateTask : public Task {
	WeakReference<TangibleObject*> lair;
	WeakReference<LairObserver*> observer;

public:
	LairRepopulateTask(TangibleObject* obj, LairObserver* observer) {
		lair = obj;
		this->observer = observer;
	}

	void run() {
		TangibleObject* strongLair = lair.get();
		LairObserver* strongObserver = observer.get();

		if (strongLair == nullptr || strongObserver == nullptr) {
			return;
		}

		if (strongLair->isDestroyed() || strongObserver->getLivingCreatureCount() < 1)
			return;

		LairObject* lair = cast<LairObject*>(strongLair);

		if (lair != nullptr && (lair->isRepopulated() || lair->getNumberOfPlayersInRange() > 0))
			return;

		strongObserver->repopulateLair(strongLair);
	}
};

#endif /* LAIRREPOPULATETASK_H_ */