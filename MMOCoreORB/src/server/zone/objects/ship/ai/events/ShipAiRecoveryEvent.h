/*
 * ShipAiRecoveryEvent.h
 */

#ifndef SHIPAIRECOVERYEVENT_H_
#define SHIPAIRECOVERYEVENT_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/managers/space/SpaceAiMap.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace events {

class ShipAiRecoveryEvent : public Task {
	ManagedWeakReference<ShipAiAgent*> agent;
	Time startTime;

public:
	ShipAiRecoveryEvent(ShipAiAgent* aiAgent) : Task(1000) {
		agent = aiAgent;
		startTime.updateToCurrentTime();
		SpaceAiMap::instance()->activeRecoveryEvents.increment();
	}

	~ShipAiRecoveryEvent() {
		SpaceAiMap::instance()->activeRecoveryEvents.decrement();
	}

	void run() {
		ManagedReference<ShipAiAgent*> strongRef = agent.get();

		if (strongRef == nullptr /*|| (!strongRef->isPet() && (strongRef->isDead() || strongRef->isIncapacitated()))*/)
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

	void clearShipAgentObject() {
		agent = nullptr;
	}
};

} // namespace events
} // namespace ai
} // namespace space
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::events;

#endif /* SHIPAIRECOVERYEVENT_H_ */
