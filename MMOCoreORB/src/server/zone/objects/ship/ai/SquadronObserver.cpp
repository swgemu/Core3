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
	squadron.add(shipAgent);
}

SquadronObserver::~SquadronObserver() {

}

int SquadronObserver::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	return 0;
}

void SquadronObserver::addSquadronShip(ShipAiAgent* shipAgent) {
	Locker lock(&mutex);
	squadron.add(shipAgent);
}

void SquadronObserver::dropSquadronShip(ShipAiAgent* shipAgent) {
	Locker lock(&mutex);
	int index = squadron.find(shipAgent);

	if (index != -1) {
		squadron.remove(shipAgent);
	}
}

void SquadronObserver::setFormationType(int type, float radius) {
	Locker lock(&mutex);
	squadron.setFormationType(type, radius);
}

void SquadronObserver::setRandomFormation() {
	int type = System::random(ShipSquadronFormation::Type::SIZE - 1);
	setFormationType(type);
}

ShipAiAgent* SquadronObserver::getSquadronLeader() const {
	Locker lock(&mutex);
	return squadron.size() > 0 ? squadron.get(0)->asShipAiAgent() : nullptr;
}

ShipAiAgent* SquadronObserver::getSquadronMember(int index) const {
	Locker lock(&mutex);
	return squadron.size() > index ? squadron.get(index)->asShipAiAgent() : nullptr;
}

uint64 SquadronObserver::getSquadronLeaderID() const {
	Locker lock(&mutex);
	return squadron.size() > 0 ? squadron.get(0)->getObjectID() : 0ull;
}

uint64 SquadronObserver::getSquadronMemberID(int index) const {
	Locker lock(&mutex);
	return squadron.size() > index ? squadron.get(index)->getObjectID() : 0ull;
}

int SquadronObserver::getSquadronIndex(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadron.find(shipAgent);
}

int SquadronObserver::getSquadronSize() const {
	Locker lock(&mutex);
	return squadron.size();
}

int SquadronObserver::getFormationType() const {
	Locker lock(&mutex);
	return squadron.getFormationType();
}

float SquadronObserver::getFormationSpeed() const {
	Locker lock(&mutex);
	return squadron.getFormationSpeed();
}

bool SquadronObserver::isSquadronLeader(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadron.find(shipAgent) == 0;
}

bool SquadronObserver::isSquadronMember(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadron.find(shipAgent) >= 1;
}

Vector3 SquadronObserver::getPosition(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadron.getPosition(squadron.find(shipAgent));
}

float SquadronObserver::getSpeed(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadron.getSpeed(squadron.find(shipAgent));
}

void SquadronObserver::updateSquadron() {
	Locker lock(&mutex);

	auto leader = getSquadronLeader();

	if (leader == nullptr || !leader->isShipLaunched() || leader->isDisabled()) {
		return;
	}

	Locker lLock(leader);

	const auto& lMatrix = *leader->getConjugateMatrix();
	const auto& lTransform = leader->getNextTransform();

	for (int i = squadron.size(); 0 < --i;) {
		auto shipAgent = squadron.get(i);

		if (shipAgent == nullptr || !shipAgent->isShipLaunched() || shipAgent->isDisabled()) {
			continue;
		}

		Locker sLock(shipAgent, leader);

		const auto& sTransform = shipAgent->getCurrentTransform();
		const auto& sVelocity = sTransform.getVelocity();
		const auto& formation = squadron.getFormation(i);

		Vector3 fPosition = SpaceMath::getGlobalVector(formation, lMatrix);
		Vector3 tPosition = fPosition + leader->getPosition();
		Vector3 velocity = tPosition - shipAgent->getPosition();
		Vector3 position = (velocity * 2.f) + fPosition + lTransform.getPosition();

		float intersection = sVelocity.dotProduct(velocity);
		float interception = intersection + leader->getCurrentSpeed();
		float speed = Math::max((intersection * 0.5f) + leader->getCurrentSpeed(), 0.f);

		squadron.setPosition(i, position);
		squadron.setSpeed(i, speed);
	}

	const auto& nextPosition =  leader->getNextPosition().getWorldPosition();
	float nextSpeed = (getFormationSpeed() + leader->getActualMaxSpeed()) * 0.5f;

	squadron.setPosition(0, nextPosition);
	squadron.setSpeed(0, nextSpeed);
}


