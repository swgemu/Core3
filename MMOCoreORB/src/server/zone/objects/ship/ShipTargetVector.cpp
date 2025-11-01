#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/ShipTargetVector.h"

void ShipTargetVector::update(ShipObject* ship) {
	if (!isScheduled()) {
		return;
	}

	if (ship == nullptr || !ship->isShipLaunched()) {
		targetMap.removeAll();
		return;
	}

	Locker tLock(&targetLock);
	setServerTime();

	auto closeObjects = ship->getCloseObjects();

	if (closeObjects == nullptr) {
		return;
	}

	auto closeCopy = SortedVector<ManagedReference<TreeEntry*>>();
	closeObjects->safeCopyTo(closeCopy);
	targetMap.removeAll();

	for (int i = 0; i < closeCopy.size(); ++i) {
		auto target = closeCopy.getUnsafe(i).castTo<SceneObject*>();

		if (target == nullptr || !isTargetValid(ship, target)) {
			continue;
		}

		float distanceSqr = getTargetDistanceSqr(ship, target);

		if (distanceSqr > TARGET_DISTANCE_SQR) {
			continue;
		}

		targetMap.put(distanceSqr, target.get());
	}

	if (targetMap.size() > (int)TARGETVECTORMAX) {
		targetMap.removeRange((int)TARGETVECTORMAX, targetMap.size());
	}
}

float ShipTargetVector::getTargetDistanceSqr(ShipObject* ship, SceneObject* target) const {
	float radius = ship->getBoundingRadius() + target->getBoundingRadius();
	return ship->getPosition().squaredDistanceTo(target->getPosition()) - Math::sqr(radius);
}

bool ShipTargetVector::isTargetValid(ShipObject* ship, SceneObject* target) const {
	if (target == nullptr || ship == target || target->getLocalZone() == nullptr) {
		return false;
	}

	if (isCollidableType(target->getGameObjectType())) {
		return true;
	}

	auto targetTano = target->isTangibleObject() ? target->asTangibleObject() : nullptr;

	if (targetTano == nullptr) {
		return false;
	}

	return targetTano->isAttackableBy(ship);
}

void ShipTargetVector::safeCopyTo(Vector<ManagedReference<SceneObject*>>& vector) const {
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

void ShipTargetVector::safeCopyTo(Vector<ManagedReference<ShipObject*>>& vector) const {
	ReadLocker tLock(&targetLock);

	int allocation = Math::min((int)TARGETVECTORMAX, targetMap.size());
	vector.removeAll(allocation, allocation);

	for (int i = 0; i < allocation; ++i) {
		auto object = targetMap.getUnsafe(i).getValue().get();

		if (object == nullptr || !object->isShipObject()) {
			continue;
		}

		auto ship = object.castTo<ShipObject*>();

		if (ship != nullptr) {
			vector.add(std::move(ship));
		}
	}
}

int ShipTargetVector::size() const {
	ReadLocker tLock(&targetLock);

	return targetMap.size();
}
