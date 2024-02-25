#ifndef SPACECOLLISIONRESULT_H_
#define SPACECOLLISIONRESULT_H_

//#define SPACECOLLISION_DEBUG

#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/managers/spacecombat/projectile/ShipProjectile.h"

#ifdef SPACECOLLISION_DEBUG
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#endif // SPACECOLLISION_DEBUG

class SpaceCollisionResult {
protected:
	ManagedWeakReference<ShipObject*> object;
	Vector3 position;
	float distance;
	bool front;
	int slot;

public:
	SpaceCollisionResult() {
		distance = FLT_MAX;
		front = false;
		slot = -1;
	}

	void setCollision(ShipObject* targetShip, const ShipProjectile* projectile, float intersection, int componentSlot = -1, bool hitFront = false) {
		object = targetShip;
		distance = projectile->getDistance() * intersection;
		position = (projectile->getDirection() * distance) + projectile->getLastPosition();
		front = hitFront;

		if (componentSlot != -1) {
			slot = componentSlot;
		}
	}

	ManagedWeakReference<ShipObject*> getObject() const {
		return object;
	}

	const Vector3& getPosition() const {
		return position;
	}

	float getDistance() const {
		return distance;
	}

	bool isHitFront() const {
		return front;
	}

	int getSlot() const {
		return slot;
	}

#ifdef SPACECOLLISION_DEBUG
	void debugCollision(ShipObject* ship, const ShipProjectile* projectile) {
		auto pilot = ship == nullptr ? nullptr : ship->getPilot();
		if (pilot == nullptr) {
			return;
		}

		auto targetShip = getObject().get();
		if (targetShip == nullptr) {
			return;
		}

		auto targetData = ShipManager::instance()->getCollisionData(targetShip);
		if (targetData == nullptr) {
			return;
		}

		auto path = new CreateClientPathMessage();
		path->addCoordinate(projectile->getLastPosition());
		path->addCoordinate(position);

		StringBuffer msg;
		msg << writeDebugResultMessage(targetShip);

		const Vector3& targetPosition = targetShip->getPosition();

		Matrix4 targetRotation;
		targetRotation.setRotationMatrix(targetShip->getDirection()->getConjugate().toMatrix3());

		float targetRadius = targetData->getBoundingSphere().getRadius();

		if (targetData->getVolumeType() == ShipCollisionData::CollisionVolumeType::MESH) {
			path->drawBoundingSphere(targetPosition, targetRotation, targetData->getBoundingSphere());
			msg << debugCollisionHardpoints(targetShip, targetPosition, targetRotation, targetData, path);
		}

		if (targetData->getVolumeType() == ShipCollisionData::CollisionVolumeType::BOX) {
			path->drawBoundingSphere(targetPosition, targetRotation, targetData->getBoundingSphere());
			path->drawBoundingBox(targetPosition, targetRotation, targetData->getChassisBox());
		}

		if (targetData->getVolumeType() == ShipCollisionData::CollisionVolumeType::RADIUS) {
			path->drawBoundingSphere(targetPosition, targetRotation, targetData->getBoundingSphere());
			path->drawBoundingSphere(targetPosition, targetRotation, targetData->getChassisSphere());
		}

		path->addCoordinate(position);
		path->addCoordinate(projectile->getThisPosition());

		msg << "--------------------------------";

		pilot->sendSystemMessage(msg.toString());
		pilot->sendMessage(path);
	}

	String writeDebugResultMessage(ShipObject* target) {
		auto targetData = ShipManager::instance()->getCollisionData(target);
		if (targetData == nullptr) {
			return "!targetData";
		}

		StringBuffer msg;
		msg << "SpaceCollisionResult" << endl
			<< "  distance:       " << distance << endl
			<< "  position:       " << position.toString() << endl
			<< "  front/back:     " << (front ? "FRONT" : "BACK") << endl
			<< "  chassisRadius:  " << targetData->getChassisSphere().getRadius() << endl
			<< "  boundingRadius: " << targetData->getBoundingSphere().getRadius() << endl
			<< "  volumeType:     " << targetData->getVolumeType() << endl
			<< "  slot:           " << slot << endl;

		return msg.toString();
	}

	String writeDebugHardpointMessage(const ShipCollisionHardpoint& hardpoint, int slot) {
		StringBuffer msg;
		msg << "  hardpoint:      " << hardpoint.getHardpointName()
			<< "  appearance:     " << hardpoint.getAppearanceName()
			<< "  position:       " << hardpoint.getSphere().getCenter().toString()
			<< "  radius:         " << hardpoint.getSphere().getRadius()
			<< "  slot:           " << slot << endl;

		return msg.toString();
	}

	String debugCollisionHardpoints(ShipObject* targetShip, const Vector3& targetPosition, const Matrix4& targetRotation, const ShipCollisionData* targetData, CreateClientPathMessage* path) {
		StringBuffer msg;
		float targetRadius = targetData->getBoundingSphere().getRadius();

		for (uint32 slot = 0; slot <= Components::FIGHTERSLOTMAX; ++slot) {
			String slotName = Components::shipComponentSlotToString(slot);
			uint32 compCrc = targetShip->getShipComponentMap()->get(slot);

			if (compCrc == 0) {
				continue;
			}

			const auto& hardPoints = targetData->getHardpoints(slotName);

			for (int i = 0; i < hardPoints.size(); ++i) {
				auto key = hardPoints.getUnsafe(i).getKey();
				if (key != compCrc) {
					continue;
				}

				const auto& hardPoint = hardPoints.getUnsafe(i).getValue();
				float hardpointRadius = hardPoint.getSphere().getRadius();

				path->drawBoundingSphere(targetPosition, targetRotation, hardPoint.getSphere());
				msg << slot << ": " << writeDebugHardpointMessage(hardPoint, slot);
			}
		}

		return msg.toString();
	}
#endif // SPACECOLLISION_DEBUG
};

#endif // SPACECOLLISIONRESULT_H_
