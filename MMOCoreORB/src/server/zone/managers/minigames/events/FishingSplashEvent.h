/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FISHINGSPLASHEVENT_H_
#define FISHINGSPLASHEVENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/minigames/FishingManager.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class FishingSplashEvent : public Task {
	ManagedReference<CreatureObject*> player;
	ManagedReference<SceneObject*> splash;

public:
	FishingSplashEvent(CreatureObject* player, SceneObject* splash) : Task(1000) {
		this->player = player;
		this->splash = splash;
	}

	void run() {
		try {
			Locker _locker(player);

			//player->info("activating command queue action");

			ManagedReference<FishingManager*> manager = player->getZoneProcessServer()->getFishingManager();
			Locker splashLocker(splash);
			manager->removeSplash(splash);

			//player->info("command queue action activated");

		} catch (...) {
			//player = NULL;

			throw;
		}

		//player = NULL;

	}

	SceneObject* getSplash() {
		return splash;
	}

};

}
}
}
}
}

using namespace server::zone::managers::minigames::events;

#endif /* FISHINGSPLASHEVENT_H_ */
