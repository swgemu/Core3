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
		// FIXME
		ManagedReference<CreatureObject*> strong = player.get();

		if (strong == NULL)
			return;

		try {
			Locker _locker(strong);

			//player->info("activating command queue action");

			ManagedReference<FishingManager*> manager = strong->getZoneProcessServer()->getFishingManager();
			//Locker lockerManager(manager);
			//player->removePendingTask("fishing");
			if (fishingState != FishingManagerImplementation::NOTFISHING) {
				manager->fishingStep(strong);

			} /*else if (marker != NULL) {
					// new event
				manager->createFishingEvent(player, nextAction, zoneServer, marker, fish, boxID, fishingState, mood);

			}*/ else {

				manager->stopFishingEvent(strong);

			}

			//player->info("command queue action activated");


		} catch (...) {
			//player = NULL;

			throw;
		}

		//player = NULL;
	}
};

}
}
}
}
}

using namespace server::zone::managers::minigames::events;

#endif /* FISHINGEVENT_H_ */
