/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FISHINGEVENT_H_
#define FISHINGEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/minigames/FishingManager.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class FishingEvent : public Task {
	ManagedWeakReference<CreatureObject*> player;
	int fishingState;

public:
	FishingEvent(CreatureObject* player, int fishingState) : Task(7000) {
		this->player = player;
		this->fishingState = fishingState;
	}

	void run() {
		ManagedReference<CreatureObject*> strong = player.get();

		if (strong == nullptr) {
			return;
		}

		try {
			Locker _locker(strong);

			ManagedReference<FishingManager*> manager = strong->getZoneProcessServer()->getFishingManager();

			if (fishingState != FishingManagerImplementation::NOTFISHING) {
				manager->fishingStep(strong);

			} else {
				manager->stopFishingEvent(strong);
			}

		} catch (...) {
			// player = nullptr;

			throw;
		}

		// player = nullptr;
	}
};

} // namespace events
} // namespace minigames
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::minigames::events;

#endif /* FISHINGEVENT_H_ */
