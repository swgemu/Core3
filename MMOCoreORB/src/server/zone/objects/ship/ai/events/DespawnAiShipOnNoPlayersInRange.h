/*
 * DespawnAiShipOnNoPlayersInRange.h
 */

#ifndef DESPAWNAISHIPONNOPLAYERSINRANGE_H_
#define DESPAWNAISHIPONNOPLAYERSINRANGE_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace events {

class DespawnAiShipOnNoPlayersInRange : public Task {
	ManagedWeakReference<ShipAiAgent*> ship;

public:
	DespawnAiShipOnNoPlayersInRange(ShipAiAgent* shipO) {
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

		strongShip->clearDespawnEvent();

		auto zone = strongShip->getZone();

		if (zone == nullptr) {
			return;
		}

		if (!strongShip->getDespawnOnNoPlayerInRange()) {
			return;
		}

		if (strongShip->getNumberOfPlayersInRange() <= 0) {
			strongShip->destroyObjectFromWorld(true);
			strongShip->notifyDespawn();

			// strongShip->info(true) << strongShip->getDisplayedName() << " removed from ShipAgent from world";
		}
	}
};

} // namespace events
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::ai::events;

#endif /* DESPAWNAISHIPONNOPLAYERSINRANGE_H_ */
