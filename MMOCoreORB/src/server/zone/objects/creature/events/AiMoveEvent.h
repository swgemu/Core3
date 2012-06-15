/*
 * AiMoveEvent.h
 *
 *  Created on: 10/07/2010
 *      Author: victor
 */

#ifndef AiMoveEvent_H_
#define AiMoveEvent_H_

#include "../AiAgent.h"
#include "../PatrolPoint.h"
#include "../ai/AiActor.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class AiMoveEvent : public Task {
	ManagedWeakReference<AiAgent*> creature;
	ManagedWeakReference<AiActor*> actor;

public:
	AiMoveEvent(AiAgent* pl) : Task(1000) {
		creature = pl;
	}

	AiMoveEvent(AiActor* a) : Task(1000) {
		actor = a;
	}

	~AiMoveEvent() {
	}

	void run() {
		ManagedReference<AiActor*> strongRef = actor.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);

		ManagedReference<CreatureObject*> host = strongRef->getHost();

		if (host == NULL) {
			strongRef->next(AiActor::NONE);
			return;
		}

		Locker clocker(strongRef, host);

		strongRef->doMovement();
	}

	void clearCreatureObject() {
		creature = NULL;
	}

	void clearActorObject() {
		actor = NULL;
	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::events;



#endif /* AiMoveEvent_H_ */
