/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GAMBLINGTIMEOUTEVENT_H_
#define GAMBLINGTIMEOUTEVENT_H_

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/minigames/gambling/GamblingManager.h"
#include "server/zone/objects/tangible/terminal/gambling/GamblingTerminal.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class GamblingTimeoutEvent : public Task {
	ManagedWeakReference<GamblingManager*> gamblingManager;
	ManagedReference<CreatureObject*> player;

public:
	GamblingTimeoutEvent(GamblingManager* gamb, CreatureObject* play) : Task() {
		gamblingManager = gamb;
		player = play;
	}

	void run() {
		player->removePendingTask("gamblingTimeout");

		ManagedReference<GamblingManager*> strongRef = gamblingManager.get();

		if (strongRef == nullptr)
			return;

		Locker locker(strongRef);

		strongRef->closePlayerSUI(player);
		strongRef->leaveTable(player);
	}

};

}
}
}
}
}

using namespace server::zone::managers::minigames::events;

#endif /* GAMBLINGTIMEOUTEVENT_H_ */
