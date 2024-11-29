#ifndef SPACECOLLISIONRESULT_H_
#define SPACECOLLISIONRESULT_H_

//#define SPACECOLLISION_DEBUG

#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/managers/spacecombat/projectile/ShipProjectile.h"

#ifdef SPACECOLLISION_DEBUG
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#endif // SPACECOLLISION_DEBUG

class SpaceCollisionEntry {
protected:
	ManagedWeakReference<SceneObject*> object;
	Vector3 position;
	Vector3 direction;

	float distance;
	int slot;

public:
	SpaceCollisionEntry() {
		distance = FLT_MAX;
		slot = -1;
	}

	SpaceCollisionEntry(SceneObject* target, const ShipProjectile* projectile, const Vector3& localDirection, float intersection, int componentSlot = -1) {
		object = target;
		distance = projectile->getDistance() * Math::clamp(0.f, intersection, 1.f);

		position = (projectile->getDirection() * distance) + projectile->getLastPosition();
		direction = localDirection;

		slot = componentSlot;
	}

	ManagedWeakReference<SceneObject*> getObject() const {
		return object;
	}

	const Vector3& getPosition() const {
		return position;
	}

	const Vector3& getDirection() const {
		return direction;
	}

	float getDistance() const {
		return distance;
	}

	bool isHitFront() const {
		return direction.getZ() >= 0.f;
	}

	int getSlot() const {
		return slot;
	}
};

class SpaceCollisionResult {
protected:
	VectorMap<float, SpaceCollisionEntry> collisionMap;

public:
	SpaceCollisionResult() {

	}

	void setCollision(SceneObject* target, const ShipProjectile* projectile, const Vector3& localDirection, float intersection, int componentSlot = Components::CHASSIS) {
		collisionMap.put(intersection, SpaceCollisionEntry(target, projectile, localDirection, intersection, componentSlot));
	}

	ManagedWeakReference<SceneObject*> getObject(int index = 0) const {
		return collisionMap.size() > index ? collisionMap.elementAt(index).getValue().getObject() : nullptr;
	}

	const Vector3& getPosition(int index = 0) const {
		return collisionMap.size() > index ? collisionMap.elementAt(index).getValue().getPosition() : Vector3::ZERO;
	}

	const Vector3& getDirection(int index = 0) const {
		return collisionMap.size() > index ? collisionMap.elementAt(index).getValue().getDirection() : Vector3::ZERO;
	}

	float getDistance(int index = 0) const {
		return collisionMap.size() > index ? collisionMap.elementAt(index).getValue().getDistance() : FLT_MAX;
	}

	bool isHitFront(int index = 0) const {
		return collisionMap.size() > index ? collisionMap.elementAt(index).getValue().isHitFront() : false;
	}

	int getSlot(int index = 0) const {
		return collisionMap.size() > index ? collisionMap.elementAt(index).getValue().getSlot() : -1;
	}

	int size() const {
		return collisionMap.size();
	}

#ifdef SPACECOLLISION_DEBUG
	void debugCollision(ShipObject* ship, const ShipProjectile* projectile) {
		auto pilot = ship == nullptr ? nullptr : ship->getPilot();
		if (pilot == nullptr) {
			return;
		}

		auto target = getObject().get();
		if (target == nullptr) {
			return;
		}

		const auto& position = getPosition();

		auto path = new CreateClientPathMessage();
		path->addCoordinate(ship->getPosition());
		path->addCoordinate(projectile->getLastPosition());
		path->addCoordinate(position);

		StringBuffer msg;
		msg
		<< "  distance:       " << getDistance() << endl
		<< "  position:       " << getPosition().toString() << endl
		<< "  front/back:     " << (isHitFront() ? "FRONT" : "BACK") << endl
		<< "  slot:           " << getSlot() << endl;

		if (target->isShipObject()) {
			auto targetShip = target->asShipObject();
			if (targetShip == nullptr) {
				return;
			}

			auto targetData = ShipManager::instance()->getCollisionData(targetShip);
			if (targetData == nullptr) {
				return;
			}

			const Vector3& targetPosition = targetShip->getPosition();
			const Matrix4& targetRotation = *targetShip->getConjugateMatrix();

			if (targetData->getVolumeType() == ShipCollisionData::CollisionVolumeType::MESH) {
				path->drawBoundingSphere(targetPosition, targetRotation, targetData->getBoundingSphere());
				msg << debugCollisionHardpoints(targetShip, targetPosition, targetRotation, targetData, path);
			}

			if (targetData->getVolumeType() == ShipCollisionData::CollisionVolumeType::BOX) {
				path->drawBoundingSphere(targetPosition, targetRotation, targetData->getBoundingSphere());
				path->drawBoundingBox(targetPosition, targetRotation, targetData->getChassisBox());
			}

			if (targetData->getVolumeType() == ShipCollisionData::CollisionVolumeType::SPHERE) {
				path->drawBoundingSphere(targetPosition, targetRotation, targetData->getBoundingSphere());
				path->drawBoundingSphere(targetPosition, targetRotation, targetData->getChassisSphere());
			}

			path->addCoordinate(position);
			path->addCoordinate(projectile->getThisPosition());

			msg << targetData->toDebugString(false) << endl;
		} else {
			auto appearance = target->getAppearanceTemplate();
			if (appearance == nullptr) {
				return;
			}

			auto bounding = appearance->getBoundingVolume();
			if (bounding == nullptr) {
				return;
			}

			auto collision = appearance->getCollisionVolume();
			if (collision == nullptr) {
				collision = bounding;
			}

			const Vector3& targetPosition = target->getPosition();
			Matrix4 targetRotation;
			targetRotation.setRotationMatrix(target->getDirection()->getConjugate().toMatrix3());

			if (collision->isBoundingBox()) {
				path->drawBoundingSphere(targetPosition, targetRotation, bounding->getBoundingSphere());
				path->drawBoundingBox(targetPosition, targetRotation, collision->getBoundingBox());
			} else if (collision->isBoundingSphere()) {
				path->drawBoundingSphere(targetPosition, targetRotation, bounding->getBoundingSphere());
				path->drawBoundingSphere(targetPosition, targetRotation, collision->getBoundingSphere());
			} else {
				path->drawBoundingSphere(targetPosition, targetRotation, bounding->getBoundingSphere());
			}
		}

		msg << "--------------------------------";
		pilot->sendSystemMessage(msg.toString());
		pilot->sendMessage(path);
	}

	String debugCollisionHardpoints(ShipObject* targetShip, const Vector3& targetPosition, const Matrix4& targetRotation, const ShipCollisionData* targetData, CreateClientPathMessage* path) {
		StringBuffer msg;

		for (int slot = -1; slot <= Components::CAPITALSLOTMAX; ++slot) {
			String slotName = Components::shipComponentSlotToString(slot);
			uint32 compCrc = targetShip->getShipComponentMap()->get(slot);

			if (slot != Components::CHASSIS && compCrc == 0) {
				continue;
			}

			const auto& hardPoints = targetData->getHardpoints(slotName);

			for (int i = 0; i < hardPoints.size(); ++i) {
				auto key = hardPoints.getUnsafe(i).getKey();
				if (slot != Components::CHASSIS && (key != compCrc || slot != getSlot())) {
					continue;
				}

				const auto& hardPoint = hardPoints.getUnsafe(i).getValue();
				int volumeType = hardPoint.getVolumeType();

				if (volumeType == ShipCollisionData::CollisionVolumeType::SPHERE) {
					path->drawBoundingSphere(targetPosition, targetRotation, hardPoint.getSphere());
					path->drawBoundingSphere(targetPosition, targetRotation, Sphere(hardPoint.getSphere().getCenter(), hardPoint.getRadius()));
					msg << slotName << ": " << hardPoint.toDebugString();
				}

				if (volumeType == ShipCollisionData::CollisionVolumeType::BOX) {
					path->drawBoundingBox(targetPosition, targetRotation, hardPoint.getBox());
					path->drawBoundingSphere(targetPosition, targetRotation, Sphere(hardPoint.getSphere().getCenter(), hardPoint.getRadius()));
					msg << slotName << ": " << hardPoint.toDebugString();
				}

				if (volumeType == ShipCollisionData::CollisionVolumeType::MESH) {
					path->drawBoundingSphere(targetPosition, targetRotation, hardPoint.getSphere());
					path->drawBoundingSphere(targetPosition, targetRotation, Sphere(hardPoint.getSphere().getCenter(), hardPoint.getRadius()));
					msg << slotName << ": " << hardPoint.toDebugString();
				}

				if (volumeType == ShipCollisionData::CollisionVolumeType::RADIUS) {
					path->drawBoundingSphere(targetPosition, targetRotation, hardPoint.getSphere());
					msg << slotName << ": " << hardPoint.toDebugString();
				}
			}
		}

		return msg.toString();
	}
#endif // SPACECOLLISION_DEBUG
};

#endif // SPACECOLLISIONRESULT_H_
