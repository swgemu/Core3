#include "GamblingEvent.h"

#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/objects/tangible/terminal/gambling/GamblingTerminal.h"

GamblingEvent::GamblingEvent(GamblingTerminal* gamblingTerm, int counter) : Task() {
	gamblingTerminal = gamblingTerm;
	gameCount = counter;
}

void GamblingEvent::run() {
	Reference<GamblingManager*> manager = gamblingTerminal->getZoneProcessServer()->getGamblingManager();

	if ((gamblingTerminal->getState() != GamblingTerminal::NOGAMERUNNING) && (gamblingTerminal->getGameCount() == gameCount)) {
		manager->continueGame(gamblingTerminal);
	}
}