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
	ManagedWeakReference<CreatureObject*> weakPlayer;
	int fishingState;

public:
	FishingEvent(CreatureObject* player, int state) : Task(7000) {
		weakPlayer = player;
		fishingState = state;
	}

	void run() {
		ManagedReference<CreatureObject*> player = weakPlayer.get();

		if (player == nullptr) {
			return;
		}

		auto zoneProcessServer = player->getZoneProcessServer();

		if (zoneProcessServer == nullptr) {
			clearPlayerFishing(player);
			return;
		}

		auto fishingManager = zoneProcessServer->getFishingManager();

		if (fishingManager == nullptr) {
			clearPlayerFishing(player);
			return;
		}

		try {
			Locker lock(player);

			ManagedReference<FishingManager*> manager = zoneProcessServer->getFishingManager();

			if (fishingState != FishingManagerImplementation::NOTFISHING) {
				manager->continueFishing(player);
			} else {
				manager->stopFishingEvent(player);
			}
		} catch (...) {
			throw;
		}
	}

	void clearPlayerFishing(CreatureObject* player) {
		if (player == nullptr) {
			return;
		}

		Locker lock(player);

		player->setMoodString("none");
	}
};

} // namespace events
} // namespace minigames
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::minigames::events;

#endif /* FISHINGEVENT_H_ */
