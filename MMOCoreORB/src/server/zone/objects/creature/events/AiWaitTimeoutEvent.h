#ifndef AIWAITTIMEOUTEVENT_H
#define AIWAITTIMEOUTEVENT_H
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/managers/creature/AiMap.h"
#include "../PatrolPoint.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class AiWaitTimeoutEvent : public Task {
	ManagedWeakReference<AiAgent*> creature;

public:
	AiWaitTimeoutEvent(AiAgent* pl) : Task(10000) {
		creature = pl;
	}

	virtual ~AiWaitTimeoutEvent() {
	}

	void run() {
		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		PatrolPoint* nextLocation = strongRef->getNextPosition();

		if (nextLocation != NULL) {
			SceneObject* cell = strongRef->getParent().get();
			Zone* zone = strongRef->getZone();
			if (cell == NULL && zone != NULL)
				strongRef->teleport(nextLocation->getPositionX(), zone->getHeight(nextLocation->getPositionX(), nextLocation->getPositionY()), nextLocation->getPositionY(), 0);
			else if (cell != NULL && cell->isCellObject())
				strongRef->teleport(nextLocation->getPositionX(), nextLocation->getPositionZ(), nextLocation->getPositionY(), cell->getObjectID());
			else
				strongRef->teleport(nextLocation->getPositionX(), nextLocation->getPositionZ(), nextLocation->getPositionY(), 0);
		}
	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::events;

#endif // AIWAITTIMEOUTEVENT_H

