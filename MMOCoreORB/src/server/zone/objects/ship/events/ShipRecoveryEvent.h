/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef SHIPRECOVERYEVENT_H_
#define SHIPRECOVERYEVENT_H_

#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace events {

class ShipRecoveryEvent : public Task {
	ManagedWeakReference<ShipObject*> weakShip;

public:
	ShipRecoveryEvent(ShipObject* shipObj) : Task(1000) {
		weakShip = shipObj;
	}

	void run() {
		ManagedReference<ShipObject*> ship = weakShip.get();

		if (ship == nullptr)
			return;

		ship->doRecovery(1000);
	}

	void schedule(uint64 delay = 0) {
		ManagedReference<ShipObject*> ship = weakShip.get();

		if (ship != nullptr) {
			auto zone = ship->getZone();

			if (zone != nullptr) {
				setCustomTaskQueue(zone->getZoneName());
			}
		}

		try {
			Task::schedule(delay);
		} catch (...) {
		}
	}
};

} // namespace events
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::events;

#endif /*SHIPRECOVERYEVENT_H_*/
