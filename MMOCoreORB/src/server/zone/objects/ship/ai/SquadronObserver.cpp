/*
			Copyright <SWGEmu>
	See file COPYING for copying conditions.

	SquadronObserver.cpp

	Author: Hakry
	Created On: 2025-10-09
*/

#include "SquadronObserver.h"

SquadronObserver::SquadronObserver() {
	setLoggingName("SquadronObserver");

	setRandomFormation();
}

SquadronObserver::SquadronObserver(ShipAiAgent* shipAgent) {
	setLoggingName("SquadronObserver");

	setRandomFormation();

	if (shipAgent != nullptr) {
		squadronVector.add(shipAgent);
	}
}

SquadronObserver::~SquadronObserver() {
	squadronVector.removeAll();
}

int SquadronObserver::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {

	return 0;
}

void SquadronObserver::addSquadronShip(ShipAiAgent* shipAgent) {
	if (shipAgent == nullptr) {
		return;
	}

	Locker lock(&mutex);

	// info(true) << __LINE__ << ":" << __FUNCTION__ << " -- Adding Ship Agent: " << shipAgent->getDisplayedName() << " Current Size: " << squadronVector.size();

	squadronVector.add(shipAgent);

	// info(true) << __LINE__ << ":" << __FUNCTION__ << " -- Adding Ship Agent Complete - New Size: " << squadronVector.size();
}

void SquadronObserver::dropSquadronShip(ShipAiAgent* shipAgent) {
	if (shipAgent == nullptr) {
		return;
	}

	Locker lock(&mutex);

	// info(true) << __LINE__ << ":" << __FUNCTION__ << " -- Dropping Ship Agent: " << shipAgent->getDisplayedName() << " Current Size: " << squadronVector.size();

	squadronVector.drop(shipAgent);

	// info(true) << __LINE__ << ":" << __FUNCTION__ << " -- Dropping Ship Agent Complete - New Size: " << squadronVector.size();
}

void SquadronObserver::setRandomFormation() {
	int totalFormations = ShipManager::FORMATION::LAST_FORMATION - 2;

	formationType = System::random(totalFormations) + 1;
}

void SquadronObserver::setFormationType(uint32 formation) {\
	if (formation >= ShipManager::FORMATION::LAST_FORMATION) {
		return;
	}

	formationType = formation;
}

ShipAiAgent* SquadronObserver::getSquadronLeader() {
	Locker lock(&mutex);

	if (squadronVector.size() < 1) {
		return nullptr;
	}

	return squadronVector.get(0).get();
}

uint64 SquadronObserver::getSquadronLeaderID() {
	Locker lock(&mutex);

	if (squadronVector.size() < 1) {
		return 0;
	}

	auto squadronLeader = squadronVector.get(0).get();

	if (squadronLeader == nullptr) {
		return 0;
	}

	return squadronLeader->getObjectID();
}