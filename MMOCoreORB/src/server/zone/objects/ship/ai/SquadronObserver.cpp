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

	addSquadronShip(shipAgent);

#ifdef DEBUG_SQUADRONS
	info(true) << "SquadronObserver:" << __FUNCTION__ << "() -- CONSTRUCTOR New Squadron Size: " << squadronAgents.size() << " Formation Type: " << squadronData.getFormationType() << " Formation Radius: " << squadronData.getFormationRadius();
#endif // DEBUG_SQUADRONS
}

SquadronObserver::~SquadronObserver() {
	squadronAgents.removeAll();

#ifdef DEBUG_SQUADRONS
	info(true) << "SquadronObserver:" << __FUNCTION__ << "() -- DESTRUCTOR";
#endif // DEBUG_SQUADRONS
}

int SquadronObserver::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	return 0;
}

void SquadronObserver::addSquadronShip(ShipAiAgent* shipAgent) {
	Locker lock(&mutex);

	if (shipAgent == nullptr || squadronAgents.find(shipAgent) != -1) {
		return;
	}

	squadronAgents.add(shipAgent);
	squadronData.add(shipAgent);

	setFormationType(squadronData.getFormationType(), squadronData.getFormationRadius());

#ifdef DEBUG_SQUADRONS
	info(true) << "SquadronObserver:" << __FUNCTION__ << "() -- New Squadron Size: " << squadronAgents.size() << " Formation Type: " << squadronData.getFormationType() << " Formation Radius: " << squadronData.getFormationRadius();
#endif // DEBUG_SQUADRONS
}

void SquadronObserver::dropSquadronShip(ShipAiAgent* shipAgent) {
	Locker lock(&mutex);

	int index = squadronAgents.find(shipAgent);

	if (index != -1) {
		squadronAgents.remove(index);
		squadronData.remove(index);

		setFormationType(squadronData.getFormationType(), squadronData.getFormationRadius());

#ifdef DEBUG_SQUADRONS
		info(true) << "SquadronObserver:" << __FUNCTION__ << "() -- New Squadron Size: " << squadronAgents.size() << " Formation Type: " << squadronData.getFormationType() << " Formation Radius: " << squadronData.getFormationRadius();
#endif // DEBUG_SQUADRONS
	}
}

void SquadronObserver::setFormationType(int type, float radius) {
	Locker lock(&mutex);

	if (type <= ShipSquadronFormation::NONE || type >= ShipSquadronFormation::SIZE) {
		type = System::random(ShipSquadronFormation::SIZE - 1);
	}

	squadronData.setFormationRadius(radius);
	squadronData.setFormationType(type);

	for (int i = 0; i < squadronAgents.size(); ++i) {
		auto shipAgent = squadronAgents.get(i).get();

		if (shipAgent != nullptr) {
			squadronData.setFormation(i, shipAgent->getBoundingRadius());
		}
	}

#ifdef DEBUG_SQUADRONS
	info(true) << "SquadronObserver:" << __FUNCTION__ << "() -- Squadron Size: " << squadronAgents.size() << " Formation Type: " << squadronData.getFormationType() << " Formation Radius: " << squadronData.getFormationRadius();
#endif // DEBUG_SQUADRONS
}

void SquadronObserver::setRandomFormation() {
	int type = System::random(ShipSquadronFormation::Type::SIZE - 1);

#ifdef DEBUG_SQUADRONS
	info(true) << "SquadronObserver:" << __FUNCTION__ << "() -- Squadron Size: " << squadronAgents.size() << " Formation Type: " << type << " Formation Radius: " << squadronData.getFormationRadius();
#endif // DEBUG_SQUADRONS

	setFormationType(type);
}

ShipAiAgent* SquadronObserver::getSquadronLeader() const {
	Locker lock(&mutex);
	return squadronAgents.size() > 0 ? squadronAgents.get(0) : nullptr;
}

ShipAiAgent* SquadronObserver::getSquadronMember(int index) const {
	Locker lock(&mutex);
	return squadronAgents.size() > index ? squadronAgents.get(index) : nullptr;
}

uint64 SquadronObserver::getSquadronLeaderID() const {
	Locker lock(&mutex);
	return squadronAgents.size() > 0 ? squadronAgents.get(0)->getObjectID() : 0ull;
}

uint64 SquadronObserver::getSquadronMemberID(int index) const {
	Locker lock(&mutex);
	return squadronAgents.size() > index ? squadronAgents.get(index)->getObjectID() : 0ull;
}

int SquadronObserver::getSquadronIndex(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadronAgents.find(shipAgent);
}

int SquadronObserver::getSquadronSize() const {
	Locker lock(&mutex);
	return squadronAgents.size();
}

int SquadronObserver::getFormationType() const {
	Locker lock(&mutex);
	return squadronData.getFormationType();
}

float SquadronObserver::getFormationSpeed() const {
	Locker lock(&mutex);
	return squadronData.getFormationSpeed();
}

bool SquadronObserver::isSquadronLeader(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadronAgents.find(shipAgent) == 0;
}

bool SquadronObserver::isSquadronMember(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadronAgents.find(shipAgent) >= 1;
}

Vector3 SquadronObserver::getPosition(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadronData.getPosition(squadronAgents.find(shipAgent));
}

float SquadronObserver::getSpeed(ShipAiAgent* shipAgent) const {
	Locker lock(&mutex);
	return squadronData.getSpeed(squadronAgents.find(shipAgent));
}

void SquadronObserver::updateSquadron() {
	Locker lock(&mutex);

	auto leader = getSquadronLeader();

	if (leader == nullptr || !leader->isShipLaunched() || leader->isDisabled()) {
		return;
	}

	const auto& lMatrix = *leader->getConjugateMatrix();
	const auto& lTransform = leader->getNextTransform();

	for (int i = squadronAgents.size(); 0 < --i;) {
		auto shipAgent = squadronAgents.get(i);

		if (shipAgent == nullptr || !shipAgent->isShipLaunched() || shipAgent->isDisabled()) {
			continue;
		}

		Locker sLock(shipAgent, leader);

		const auto& sTransform = shipAgent->getCurrentTransform();
		const auto& sVelocity = sTransform.getVelocity();
		const auto& formation = squadronData.getFormation(i);

		Vector3 fPosition = SpaceMath::getGlobalVector(formation, lMatrix);
		Vector3 tPosition = fPosition + leader->getPosition();
		Vector3 velocity = tPosition - shipAgent->getPosition();

		float errorScale = leader->getNextDistance() / Math::max(shipAgent->getCurrentSpeed(), 1.f) * 0.5f;
		Vector3 position = (velocity * errorScale) + fPosition + lTransform.getPosition();

		float intersection = sVelocity.dotProduct(velocity);
		float speed = Math::max((intersection * 0.5f) + leader->getCurrentSpeed(), 0.f);

		squadronData.setPosition(i, position);
		squadronData.setSpeed(i, speed);
	}

	const auto& nextPosition =  leader->getNextPosition().getWorldPosition();
	float nextSpeed = (getFormationSpeed() + leader->getActualMaxSpeed()) * 0.5f;

	squadronData.setPosition(0, nextPosition);
	squadronData.setSpeed(0, nextSpeed);
}


