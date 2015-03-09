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

		strongRef->teleport(nextLocation->getPositionX(), nextLocation->getPositionZ(), nextLocation->getPositionY(), nextLocation->getCell() != NULL ? nextLocation->getCell()->getObjectID() : 0);
	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::events;

#endif // AIWAITTIMEOUTEVENT_H

