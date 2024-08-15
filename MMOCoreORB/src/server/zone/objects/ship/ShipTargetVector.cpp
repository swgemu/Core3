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
	closeObjects->safeCopyReceiversTo(closeCopy, CloseObjectsVector::SHIPTYPE);

	targetMap.removeAll(closeCopy.size(), closeCopy.size());

	float maxRange = (ship->getActualMaxSpeed() * UPDATEMODIFIER) + PROJECTILERANGEMAX;
	const auto& shipPosition = ship->getPosition();

	for (int i = 0; i < closeCopy.size(); ++i) {
		auto targetShip = static_cast<ShipObject*>(closeCopy.getUnsafe(i).get());

		if (targetShip == nullptr || targetShip == ship || !isTargetValid(ship, targetShip)) {
			continue;
		}

		float sqrDistance = shipPosition.squaredDistanceTo(targetShip->getPosition());

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

	if (targetType == SceneObjectType::SHIPCAPITAL || targetType == SceneObjectType::SPACESTATION) {
		return true;
	}

	return target->isAttackableBy(ship);
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
