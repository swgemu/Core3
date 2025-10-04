/*
 * RemoveDisabledInvulnerableTask.h
 */

#ifndef REMOVEDISABLEDINVULNERABLETASK_H_
#define REMOVEDISABLEDINVULNERABLETASK_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "templates/params/ship/ShipFlag.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace events {

class RemoveDisabledInvulnerableTask : public Task {
	ManagedWeakReference<ShipAiAgent*> ship;

public:
	RemoveDisabledInvulnerableTask(ShipAiAgent* shipO) {
		ship = shipO;

		auto zone = shipO->getZone();

		if (zone != nullptr) {
			setCustomTaskQueue(zone->getZoneName());
		}
	}

	void run() {
		ManagedReference<ShipAiAgent*> strongShip = ship.get();

		if (strongShip == nullptr) {
			return;
		}

		Locker locker(strongShip);

		auto zone = strongShip->getZone();

		if (zone == nullptr) {
			return;
		}

		strongShip->removeShipFlag(ShipFlag::DISABLED_INVULNERABLE);
	}
};

} // namespace events
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::ai::events;

#endif /* REMOVEDISABLEDINVULNERABLETASK_H_ */
