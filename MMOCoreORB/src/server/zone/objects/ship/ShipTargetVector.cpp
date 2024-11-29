#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/ShipTargetVector.h"

#ifdef SHIPTARGETVECTOR_DEBUG
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/Zone.h"
#endif // SHIPTARGETVECTOR_DEBUG

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

	auto closeCopy = SortedVector<ManagedReference<TreeEntry*>>();
	closeObjects->safeCopyTo(closeCopy);

	targetMap.removeAll(closeCopy.size(), closeCopy.size());

	float maxRange = (ship->getActualMaxSpeed() * UPDATEMODIFIER) + ship->getBoundingRadius() + PROJECTILERANGEMAX;
	const auto& shipPosition = ship->getWorldPosition();

	for (int i = 0; i < closeCopy.size(); ++i) {
		auto target = closeCopy.getUnsafe(i).castTo<SceneObject*>();

		if (target == nullptr || !isTargetValid(ship, target)) {
			continue;
		}

		auto appearance = target->getAppearanceTemplate();

		if (appearance == nullptr) {
			continue;
		}

		auto bounding = appearance->getBoundingVolume();

		if (bounding == nullptr) {
			continue;
		}

		const Vector3& targetPosition = target->getWorldPosition();
		float targetRadius = bounding->getBoundingSphere().getRadius();
		float distanceSqr = shipPosition.squaredDistanceTo(targetPosition);

		if (distanceSqr > Math::sqr(targetRadius + maxRange)) {
			continue;
		}

		distanceSqr -= Math::sqr(targetRadius);
		targetMap.put(distanceSqr, target.get());
	}

	if (targetMap.size() > (int)TARGETVECTORMAX) {
		targetMap.removeRange((int)TARGETVECTORMAX, targetMap.size());
	}

#ifdef SHIPTARGETVECTOR_DEBUG
	if (ship->isPlayerShip()) { debugTargetVector(); }
#endif // SHIPTARGETVECTOR_DEBUG

	lastUpdateTime = updateTime;
}

bool ShipTargetVector::isTargetValid(ShipObject* ship, SceneObject* target) const {
	if (ship == nullptr || target == nullptr || ship == target || target->getLocalZone() == nullptr) {
		return false;
	}

	uint32 objectType = target->getGameObjectType();

	if (objectType == SceneObjectType::SHIPCAPITAL || objectType == SceneObjectType::SPACESTATION || objectType == SceneObjectType::ASTEROID || objectType == SceneObjectType::SPACEOBJECT) {
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

#ifdef SHIPTARGETVECTOR_DEBUG
void ShipTargetVector::debugTargetVector() {
	auto ship = shipRef.get();

	if (ship == nullptr) {
		return;
	}

	auto pilot = ship->getPilot();

	if (pilot == nullptr) {
		return;
	}

	const Vector3& sPosition = ship->getWorldPosition();
	auto path = new CreateClientPathMessage();

	for (int i = 0; i < targetMap.size(); ++i) {
		float distanceSqr = targetMap.elementAt(i).getKey();
		auto target = targetMap.elementAt(i).getValue().get();

		if (target == nullptr) {
			continue;
		}

		auto appearance = target->getAppearanceTemplate();

		if (appearance == nullptr) {
			continue;
		}

		auto bounding = appearance->getBoundingVolume();

		if (bounding == nullptr) {
			continue;
		}

		const Vector3& tPosition = target->getWorldPosition();

		Matrix4 rotation;
		rotation.setRotationMatrix(target->getDirection()->getConjugate().toMatrix3());

		const Sphere& sphere = bounding->getBoundingSphere();
		float boundingRadius = sphere.getRadius() + sphere.getCenter().length();

		path->addCoordinate(sPosition);
		path->addCoordinate(tPosition);
		path->drawBoundingSphere(tPosition, rotation, Sphere(Vector3::ZERO, boundingRadius));
		path->addCoordinate(tPosition);
		path->addCoordinate(sPosition);
	}

	StringBuffer msg;
	msg << "TargetVector: " << targetMap.size() << endl
		<< "--------------------------------" << endl;

	for (int i = 0; i < targetMap.size(); ++i) {
		auto distanceSqr = targetMap.elementAt(i).getKey();
		auto target = targetMap.elementAt(i).getValue().get();

		if (target == nullptr) {
			continue;
		}

		float distance = sqrt(fabs(distanceSqr)) * (distanceSqr >= 0.f ? 1.f : -1.f);
		msg << i << "  " << distance << "  " << target->getDisplayedName() << endl;
	}

	msg << "--------------------------------" << endl;

	auto smsg = new ChatSystemMessage(msg.toString());
	ship->broadcastMessage(smsg, true);
	ship->broadcastMessage(path, true);
}
#endif // SHIPTARGETVECTOR_DEBUG
