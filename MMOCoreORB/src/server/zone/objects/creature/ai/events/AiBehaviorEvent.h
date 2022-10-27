/*
 * AiBehaviorEvent.h
 *
 *  Created on: 10/07/2010
 *      Author: victor
 */

#ifndef AiBehaviorEvent_H_
#define AiBehaviorEvent_H_

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/managers/creature/AiMap.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace events {

class AiBehaviorEvent : public Task {
	ManagedWeakReference<AiAgent*> creature;
	bool hasFollowObject;
	bool isRetreating;

public:
	AiBehaviorEvent(AiAgent* pl) : Task(1000), creature(pl), hasFollowObject(false), isRetreating(false) {
		AiMap::instance()->activeBehaviorEvents.increment();
	}

	~AiBehaviorEvent() {
		AiMap::instance()->activeBehaviorEvents.decrement();

		if (hasFollowObject) {
			AiMap::instance()->behaviorsWithFollowObject.decrement();

			hasFollowObject = false;
		}

		if (isRetreating) {
			AiMap::instance()->behaviorsRetreating.decrement();

			isRetreating = false;
		}
	}

	void run() {
		AiMap::instance()->scheduledBehaviorEvents.decrement();

		if (hasFollowObject) {
			AiMap::instance()->behaviorsWithFollowObject.decrement();

			hasFollowObject = false;
		}

		if (isRetreating) {
			AiMap::instance()->behaviorsRetreating.decrement();

			isRetreating = false;
		}

		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef == nullptr)
			return;

		Locker locker(strongRef);

		strongRef->runBehaviorTree();
	}

	void schedule(uint64 delay = 0) {
		AiMap::instance()->scheduledBehaviorEvents.increment();

		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef != nullptr) {
			auto zone = strongRef->getZone();

			if (zone != nullptr) {
				setCustomTaskQueue(zone->getZoneName());
			}
		}

		try {
			Task::schedule(delay);

			if (strongRef != nullptr) {
				if (strongRef->getFollowObject() != nullptr && !hasFollowObject) {
					AiMap::instance()->behaviorsWithFollowObject.increment();

					hasFollowObject = true;
				} else if (strongRef->getFollowObject() == nullptr && hasFollowObject) {
					AiMap::instance()->behaviorsWithFollowObject.decrement();

					hasFollowObject = false;
				}

				if (strongRef->isRetreating() && !isRetreating) {
					AiMap::instance()->behaviorsRetreating.increment();

					isRetreating = true;
				} else if (!strongRef->isRetreating() && isRetreating) {
					AiMap::instance()->behaviorsRetreating.decrement();

					isRetreating = false;
				}
			}
		} catch (...) {
			AiMap::instance()->scheduledBehaviorEvents.decrement();
		}
	}

	bool cancel() {
		bool ret = false;

		if ((ret = Task::cancel())) {
			AiMap::instance()->scheduledBehaviorEvents.decrement();

			if (hasFollowObject) {
				AiMap::instance()->behaviorsWithFollowObject.decrement();

				hasFollowObject = false;
			}

			if (isRetreating) {
				AiMap::instance()->behaviorsRetreating.decrement();

				isRetreating = false;
			}
		}

		return ret;
	}

	void clearCreatureObject() {
		creature = nullptr;
	}

};

}
}
}
}
}
}

using namespace server::zone::objects::creature::events;



#endif /* AiMoveEvent_H_ */
