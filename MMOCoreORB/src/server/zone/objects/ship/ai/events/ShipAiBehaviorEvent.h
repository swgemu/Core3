/*
 * ShipAiBehaviorEvent.h
 */

#ifndef SHIPAIBEHAVIOREVENT_H_
#define SHIPAIBEHAVIOREVENT_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/managers/space/SpaceAiMap.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace events {

class ShipAiBehaviorEvent : public Task {
	ManagedWeakReference<ShipAiAgent*> agent;
	bool hasFollowObject;
	bool isRetreating;

public:
	ShipAiBehaviorEvent(ShipAiAgent* pl) : Task(1000), agent(pl), hasFollowObject(false), isRetreating(false) {
		SpaceAiMap::instance()->activeBehaviorEvents.increment();
	}

	~ShipAiBehaviorEvent() {
		SpaceAiMap::instance()->activeBehaviorEvents.decrement();

		if (hasFollowObject) {
			SpaceAiMap::instance()->behaviorsWithFollowObject.decrement();

			hasFollowObject = false;
		}

		if (isRetreating) {
			SpaceAiMap::instance()->behaviorsRetreating.decrement();

			isRetreating = false;
		}
	}

	void run() {
		SpaceAiMap::instance()->scheduledBehaviorEvents.decrement();

		if (hasFollowObject) {
			SpaceAiMap::instance()->behaviorsWithFollowObject.decrement();

			hasFollowObject = false;
		}

		if (isRetreating) {
			SpaceAiMap::instance()->behaviorsRetreating.decrement();

			isRetreating = false;
		}

		ManagedReference<ShipAiAgent*> strongRef = agent.get();

		if (strongRef == nullptr)
			return;

		Locker locker(strongRef);

		strongRef->runBehaviorTree();

		// strongRef->info(true) << strongRef->getDisplayedName() << " - ID: " << strongRef->getObjectID() << " -- ShipAiBehaviorEvent ran";
	}

	void schedule(uint64 delay = 0) {
		SpaceAiMap::instance()->scheduledBehaviorEvents.increment();

		ManagedReference<ShipAiAgent*> strongRef = agent.get();

		if (strongRef != nullptr) {
			auto zone = strongRef->getZone();

			if (zone != nullptr) {
				setCustomTaskQueue(zone->getZoneName());
			}
		}

		try {
			Task::schedule(delay);

			if (strongRef != nullptr) {
				// strongRef->info(true) << strongRef->getDisplayedName() << " - ID: " << strongRef->getObjectID() << " -- ShipAiBehavior scheduled with delay: " << delay;

				if (strongRef->getFollowShipObject().get() != nullptr && !hasFollowObject) {
					SpaceAiMap::instance()->behaviorsWithFollowObject.increment();

					hasFollowObject = true;
				} else if (strongRef->getFollowShipObject().get() == nullptr && hasFollowObject) {
					SpaceAiMap::instance()->behaviorsWithFollowObject.decrement();

					hasFollowObject = false;
				}

				if (strongRef->isRetreating() && !isRetreating) {
					SpaceAiMap::instance()->behaviorsRetreating.increment();

					isRetreating = true;
				} else if (!strongRef->isRetreating() && isRetreating) {
					SpaceAiMap::instance()->behaviorsRetreating.decrement();

					isRetreating = false;
				}
			}
		} catch (...) {
			SpaceAiMap::instance()->scheduledBehaviorEvents.decrement();
		}
	}

	bool cancel() {
		bool ret = false;

		if ((ret = Task::cancel())) {
			SpaceAiMap::instance()->scheduledBehaviorEvents.decrement();

			if (hasFollowObject) {
				SpaceAiMap::instance()->behaviorsWithFollowObject.decrement();

				hasFollowObject = false;
			}

			if (isRetreating) {
				SpaceAiMap::instance()->behaviorsRetreating.decrement();

				isRetreating = false;
			}
		}

		return ret;
	}

	void clearShipAgentObject() {
		agent = nullptr;
	}
};

} // namespace events
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::events;

#endif /* SHIPAIBEHAVIOREVENT_H_ */
