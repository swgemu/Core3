/*
 * NotifyInsertEvent.h
 *
 *  Created on: Jun 17, 2012
 *      Author: da
 */

#ifndef NOTIFYINSERTEVENT_H_
#define NOTIFYINSERTEVENT_H_

#include "../ai/AiActor.h"
#include "engine/util/u3d/QuadTreeEntry.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class NotifyInsertEvent : public Task {
	ManagedWeakReference<QuadTreeEntry*> entry;
	ManagedWeakReference<AiActor*> actor;

public:
	NotifyInsertEvent(AiActor* a, QuadTreeEntry* e) : Task(1000) {
		actor = a;
		entry = e;
	}

	virtual ~NotifyInsertEvent() {
	}

	void run() {
		ManagedReference<AiActor*> strongRef = actor.get();
		ManagedReference<QuadTreeEntry*> entryRef = entry.get();

		if (strongRef == NULL || entryRef == NULL)
			return;

		Locker locker(strongRef);

		Locker clocker(entryRef, strongRef);

		strongRef->notifyInsert(entryRef);
	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::events;

#endif /* NOTIFYINSERTEVENT_H_ */
