/*
 * AiMoveEvent.h
 *
 *  Created on: 10/07/2010
 *      Author: victor
 */

#ifndef AiMoveEvent_H_
#define AiMoveEvent_H_

#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/managers/creature/AiMap.h"
#include "../PatrolPoint.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class AiMoveEvent : public Task {
	ManagedWeakReference<AiAgent*> creature;
	bool hasFollowObject;

public:
	AiMoveEvent(AiAgent* pl) : Task(1000) {
		creature = pl;
		hasFollowObject = false;

		AiMap::instance()->activeMoveEvents.increment();
	}

	~AiMoveEvent() {
		AiMap::instance()->activeMoveEvents.decrement();

		if (hasFollowObject) {
			AiMap::instance()->moveEventsWithFollowObject.decrement();

			hasFollowObject = false;
		}
	}

	void run() {
		AiMap::instance()->scheduledMoveEvents.decrement();

		if (hasFollowObject) {
			AiMap::instance()->moveEventsWithFollowObject.decrement();

			hasFollowObject = false;
		}

		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		strongRef->doMovement();
	}

	void schedule(uint64 delay = 0) {
		AiMap::instance()->scheduledMoveEvents.increment();

		ManagedReference<AiAgent*> strongRef = creature.get();

		try {
			Task::schedule(delay);

			if (strongRef != NULL) {
				if (strongRef->getFollowObject() != NULL && !hasFollowObject) {
					AiMap::instance()->moveEventsWithFollowObject.increment();

					hasFollowObject = true;
				} else if (strongRef->getFollowObject() == NULL && hasFollowObject) {
					AiMap::instance()->moveEventsWithFollowObject.decrement();

					hasFollowObject = false;
				}
			}
		} catch (...) {
			AiMap::instance()->scheduledMoveEvents.decrement();
		}
	}

	bool cancel() {
		bool ret = false;

		if ((ret = Task::cancel())) {
			AiMap::instance()->scheduledMoveEvents.decrement();

			if (hasFollowObject) {
				AiMap::instance()->moveEventsWithFollowObject.decrement();

				hasFollowObject = false;
			}
		}

		return ret;
	}

	void clearCreatureObject() {
		creature = NULL;
	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::events;



#endif /* AiMoveEvent_H_ */
