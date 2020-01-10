#include "GamblingEvent.h"

#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/objects/tangible/terminal/gambling/GamblingTerminal.h"

GamblingEvent::GamblingEvent(GamblingTerminal* gamblingTerm, int counter) : Task() {
	gamblingTerminal = gamblingTerm;
	gameCount = counter;
}

void GamblingEvent::run() {
	try {
		//Locker _locker(player);

		//player->info("activating command queue action");

		Reference<GamblingManager*> manager = gamblingTerminal->getZoneProcessServer()->getGamblingManager();
		//gamblingTerminal->setState(state+1);
		if ((gamblingTerminal->getState() != GamblingTerminal::NOGAMERUNNING) && (gamblingTerminal->getGameCount() == gameCount)) {
			manager->continueGame(gamblingTerminal);
		}

		//player->info("command queue action activated");


	}
	catch (...) {
		throw;
	}

	//gamblingTerminal = nullptr; <- ?

}