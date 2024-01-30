#include "GamblingEvent.h"

#include "server/zone/managers/minigames/GamblingManager.h"
#include "server/zone/objects/tangible/terminal/gambling/GamblingTerminal.h"

GamblingEvent::GamblingEvent(GamblingTerminal* terminal, int count) : Task() {
	gamblingTerm = terminal;
	gameCount = count;
}

void GamblingEvent::run() {
	ManagedReference<GamblingTerminal*> gamblingTerminal = gamblingTerm.get();

	if (gamblingTerminal == nullptr)
		return;

	if (gamblingTerminal->getState() == GamblingTerminal::NOGAMERUNNING)
		return;

	if (gamblingTerminal->getGameCount() != gameCount)
		return;

	auto zoneProcess = gamblingTerminal->getZoneProcessServer();

	if (zoneProcess == nullptr)
		return;

	auto gamblingManager = zoneProcess->getGamblingManager();

	if (gamblingManager == nullptr)
		return;

	gamblingManager->continueGame(gamblingTerminal);
}