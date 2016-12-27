/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GAMBLINGEVENT_H_
#define GAMBLINGEVENT_H_

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/objects/tangible/terminal/gambling/GamblingTerminal.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class GamblingEvent : public Task {
	ManagedReference<GamblingTerminal*> gamblingTerminal;
	int gameCount;

public:
	GamblingEvent(GamblingTerminal* gamblingTerm, int counter) : Task() {
		gamblingTerminal = gamblingTerm;
		gameCount = counter;
	}

	void run() {
		try {
			//Locker _locker(player);

			//player->info("activating command queue action");

			ManagedReference<GamblingManager*> manager = gamblingTerminal->getZoneProcessServer()->getGamblingManager();
			//gamblingTerminal->setState(state+1);
			if ((gamblingTerminal->getState() != GamblingTerminal::NOGAMERUNNING) && (gamblingTerminal->getGameCount() == gameCount)) {
				manager->continueGame(gamblingTerminal);
			}

			//player->info("command queue action activated");


		} catch (...) {
			throw;
		}

		//gamblingTerminal = NULL; <- ?

	}

};

}
}
}
}
}

using namespace server::zone::managers::minigames::events;

#endif /* GAMBLINGSLOTEVENT_H_ */
