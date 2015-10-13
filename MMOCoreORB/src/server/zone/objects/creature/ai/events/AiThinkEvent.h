/*
 * AiThinkEvent.h
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#ifndef AiThinkEvent_H_
#define AiThinkEvent_H_


#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/managers/creature/AiMap.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace events {

class AiThinkEvent : public Task {
	ManagedWeakReference<AiAgent*> creature;
	Time startTime;

public:
	AiThinkEvent(AiAgent* pl) : Task(1000) {
		creature = pl;
		startTime.updateToCurrentTime();
		AiMap::instance()->activeRecoveryEvents.increment();
	}

	~AiThinkEvent() {
		AiMap::instance()->activeRecoveryEvents.decrement();
	}

	void run() {
		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);
		strongRef->doRecovery(startTime.miliDifference());
	}

	void schedule(uint64 delay = 0)
	{
		startTime.updateToCurrentTime();
		Task::schedule(delay);
	}
};

}
}
}
}
}
}

using namespace server::zone::objects::creature::events;


#endif /* AiThinkEvent_H_ */
