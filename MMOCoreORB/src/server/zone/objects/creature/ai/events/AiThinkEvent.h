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
	ManagedWeakReference<AiAgent*> agent;
	Time startTime;

public:
	AiThinkEvent(AiAgent* aiAgent) : Task(1000) {
		agent = aiAgent;
		startTime.updateToCurrentTime();
		AiMap::instance()->activeRecoveryEvents.increment();
	}

	~AiThinkEvent() {
		AiMap::instance()->activeRecoveryEvents.decrement();
	}

	void run() {
		ManagedReference<AiAgent*> strongRef = agent.get();

		if (strongRef == nullptr || strongRef->isDead() || strongRef->isIncapacitated())
			return;

		ZoneServer* zoneServer = strongRef->getZoneServer();

		if (zoneServer != nullptr && zoneServer->isServerShuttingDown())
			return;

		Locker locker(strongRef);
		strongRef->doRecovery(startTime.miliDifference());
	}

	void schedule(uint64 delay = 0) {
		startTime.updateToCurrentTime();
		Task::schedule(delay);
	}

	void clearAgentObject() {
		agent = nullptr;
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
