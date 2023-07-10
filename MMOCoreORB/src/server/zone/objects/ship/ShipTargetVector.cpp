#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/ShipTargetVector.h"

void ShipTargetVector::update() {
	Locker tLock(&targetLock);

	uint64 updateTime = System::getMiliTime();
	uint64 deltaTime = updateTime - lastUpdateTime;

	if (deltaTime < UPDATEINTERVAL) {
		return;
	}

	auto ship = shipRef.get();

	if (ship == nullptr) {
		return;
	}

	auto closeObjects = ship->getCloseObjects();

	if (closeObjects == nullptr || closeObjects->size() == 0) {
		return;
	}

	SortedVector<ManagedReference<TreeEntry*> > closeCopy;
	closeObjects->safeCopyTo(closeCopy);

	targetMap.removeAll(closeCopy.size(), closeCopy.size());

	float maxRange = (ship->getActualSpeed() * UPDATEMODIFIER) + PROJECTILERANGEMAX;
	float covRange = ship->getOutOfRangeDistance();
	const auto& shipPosition = ship->getPosition();

	for (int i = 0; i < closeCopy.size(); ++i) {
		auto scno = static_cast<SceneObject*>(closeCopy.getUnsafe(i).get());

		if (scno == nullptr || scno == ship) {
			continue;
		}

		float sqrDistance = shipPosition.squaredDistanceTo(scno->getPosition());
		float outRange = Math::max(covRange, scno->getOutOfRangeDistance());

		if (sqrDistance > (outRange * outRange)) {
			removeInRangeObject(ship, scno);
			continue;
		}

		auto targetShip = scno->isShipObject() ? scno->asShipObject() : nullptr;

		if (targetShip == nullptr || !isTargetValid(ship, targetShip)) {
			continue;
		}

		float targetRadius = targetShip->getBoundingRadius();

		if (targetRadius <= 0.f) {
			continue;
		}

		float maxRadius = targetRadius + maxRange;

		if (sqrDistance > (maxRadius * maxRadius)) {
			continue;
		}

		sqrDistance -= (targetRadius * targetRadius);
		targetMap.put(sqrDistance, targetShip);
	}

	if (targetMap.size() > (int)TARGETVECTORMAX) {
		targetMap.removeRange((int)TARGETVECTORMAX, targetMap.size());
	}

	lastUpdateTime = updateTime;
}

bool ShipTargetVector::isTargetValid(ShipObject* ship, ShipObject* target) const {
	if (ship == nullptr || target == nullptr) {
		return false;
	}

	auto targetType = target->getGameObjectType();

	if (targetType == SceneObjectType::SHIPCAPITAL || targetType == SceneObjectType::SHIPSTATION) {
		return true;
	}

	return target->isAttackableBy(ship);
}

void ShipTargetVector::removeInRangeObject(ShipObject* ship, SceneObject* target) const {
	if (ship == nullptr || target == nullptr) {
		return;
	}

	ship->removeInRangeObject(target, false);

	auto pilot = ship->getPilot();

	if (pilot != nullptr) {
		pilot->removeInRangeObject(target, true);
	}

	if (target->getCloseObjects() != nullptr) {
		target->removeInRangeObject(ship, false);
	}

	if (target->isShipObject()) {
		auto targetShip = target->asShipObject();

		if (targetShip != nullptr) {
			auto targetPilot = targetShip->getPilot();

			if (targetPilot != nullptr) {
				targetPilot->removeInRangeObject(ship, true);

				if (pilot != nullptr) {
					pilot->removeInRangeObject(targetPilot, true);
					targetPilot->removeInRangeObject(pilot, true);
				}
			}
		}
	}
}

void ShipTargetVector::safeCopyTo(Vector<ManagedReference<ShipObject*>>& vector) const {
	ReadLocker tLock(&targetLock);

	int allocation = Math::min((int)TARGETVECTORMAX, targetMap.size());
	vector.removeAll(allocation, allocation);

	for (int i = 0; i < allocation; ++i) {
		auto object = targetMap.getUnsafe(i).getValue().get();

		if (object != nullptr) {
			vector.add(std::move(object));
		}
	}
}

int ShipTargetVector::size() const {
	ReadLocker tLock(&targetLock);

	return targetMap.size();
}
