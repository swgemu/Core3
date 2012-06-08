/*
 * AiAwarenessEvent.h
 *
 *  Created on: Nov 20, 2010
 *      Author: da
 */

#ifndef AIAWARENESSEVENT_H_
#define AIAWARENESSEVENT_H_

#include "engine/util/u3d/Coordinate.h"
#include "../AiAgent.h"
#include "../CreatureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class AiAwarenessEvent : public Task {
	ManagedWeakReference<AiAgent*> creature;
	ManagedWeakReference<CreatureObject*> target;
	Coordinate coord;
	uint64 mtime;

public:
	AiAwarenessEvent(AiAgent* pl, CreatureObject* t) : Task(1000) {
		creature = pl;
		target = t;
		coord.setPosition(t->getPosition());
	}

	virtual ~AiAwarenessEvent() {
	}

	void run() {
		ManagedReference<AiAgent*> strongRef = creature.get();
		ManagedReference<CreatureObject*> targetRef = target.get();

		if (strongRef == NULL || targetRef == NULL)
			return;

		Locker locker(strongRef);

		Locker clocker(targetRef, strongRef);

		strongRef->doAwarenessCheck(coord, mtime, targetRef);
	}

	void schedule(uint64 delay = 0) {
		mtime = delay;
		Task::schedule(delay);
	}

	void setTarget(CreatureObject *t) {
		target = t;
		coord.setPosition(t->getPosition());
	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::events;

#endif /* AIAWARENESSEVENT_H_ */
