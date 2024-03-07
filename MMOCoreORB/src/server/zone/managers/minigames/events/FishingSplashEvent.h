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
	ManagedWeakReference<SceneObject*> splashWeak;

public:
	FishingSplashEvent(SceneObject* splashObj) : Task(1000) {
		splashWeak = splashObj;
	}

	void run() {
		auto splash = splashWeak.get();

		if (splash == nullptr)
			return;

		auto zoneProcServer = splash->getZoneProcessServer();

		if (zoneProcServer == nullptr)
			return;

		ManagedReference<FishingManager*> fishingManager = zoneProcServer->getFishingManager();

		if (fishingManager == nullptr)
			return;

		try {
			Locker splashLocker(splash);

			fishingManager->removeSplash(splash);
		} catch (...) {

			throw;
		}
	}
};
} // namespace events
} // namespace minigames
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::minigames::events;

#endif /* FISHINGSPLASHEVENT_H_ */
