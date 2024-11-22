/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef POBCELLDOTTASK_H_
#define POBCELLDOTTASK_H_

#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace events {

class PobCellDotTask : public Task {
	ManagedWeakReference<PobShipObject*> weakShip;

public:
	PobCellDotTask(PobShipObject* ship) : Task() {
		weakShip = ship;
	}

	void run() {
		auto pobShip = weakShip.get();

		if (pobShip == nullptr) {
			return;
		}

		Locker lock(pobShip);

		if (!pobShip->isShipLaunched()) {
			return;
		}

		if (pobShip->triggerCellDamageOverTime()) {
			pobShip->applyPobComponentDot();

			// pobShip->info(true) << "PobCellDotTask -- Re-Scheduling for " << PobShipObject::CELL_DOT_TICK * 1000;

			schedule(PobShipObject::CELL_DOT_TICK * 1000);
		}
	}

	void schedule(uint64 delay = 0) {
		auto pobShip = weakShip.get();

		if (pobShip != nullptr) {
			auto zone = pobShip->getZone();

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

using namespace server::zone::objects::ship;

#endif // POBCELLDOTTASK_H_