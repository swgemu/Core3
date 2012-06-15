/*
 * AiThinkEvent.h
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#ifndef AiThinkEvent_H_
#define AiThinkEvent_H_


#include "../AiAgent.h"
#include "../ai/AiActor.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class AiThinkEvent : public Task {
	ManagedWeakReference<AiAgent*> creature;
	ManagedWeakReference<AiActor*> actor;

public:
	AiThinkEvent(AiAgent* pl) : Task(1000) {
		creature = pl;
	}

	AiThinkEvent(AiActor* a) : Task(1000) {
		actor = a;
	}

	~AiThinkEvent() {
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

		strongRef->next();
	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::events;


#endif /* AiThinkEvent_H_ */
