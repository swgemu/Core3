#include "SpaceCollisionManager.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "server/zone/objects/ship/ComponentSlots.h"

float SpaceCollisionManager::getProjectileCollision(ShipObject* ship, const ShipProjectile* projectile, SpaceCollisionResult& result, Vector<ManagedReference<SceneObject*>>& targetVectorCopy) {
	if (ship == nullptr || projectile == nullptr || targetVectorCopy.size() == 0) {
		return MISS;
	}

	const Vector3& rayStart = projectile->getLastPosition();
	const Vector3& rayEnd =  projectile->getThisPosition();

	float rayDistance = projectile->getDistance();
	float rayRadius = projectile->getRadius();

	Vector3 direction = rayEnd - rayStart;

	for (int i = 0; i < targetVectorCopy.size(); ++i) {
		auto target = targetVectorCopy.get(i);

		if (target == nullptr) {
			continue;
		}

		if (target->isShipObject()) {
			auto targetShip = target->asShipObject();

			if (targetShip == nullptr) {
				continue;
			}

			Vector3 difference = targetShip->getPosition() - rayStart;
			float targetRadius = targetShip->getBoundingRadius() + rayRadius;

			float intersection = getPointIntersection(direction, difference, targetRadius, rayDistance);

			if (intersection == MISS) {
				continue;
			}

			auto data = ShipManager::instance()->getCollisionData(targetShip);

			if (data == nullptr) {
				continue;
			}

			auto type = data->getVolumeType();

			switch (type) {
				case ShipCollisionData::CollisionVolumeType::SPHERE: {
					getChassisRadiusCollision(targetShip, data, projectile, result);
					break;
				}

				case ShipCollisionData::CollisionVolumeType::BOX: {
					getChassisBoxCollision(targetShip, data, projectile, result);
					break;
				}

				case ShipCollisionData::CollisionVolumeType::MESH: {
					getChassisAppearanceCollision(targetShip, data, projectile, result);
					break;
				}
			}

			if (data->getTargetableSlots().size() > 0) {
				getComponentHardpointCollision(targetShip, data, projectile, result);
			}
		} else {
			auto appearance = target->getAppearanceTemplate();

			if (appearance == nullptr) {
				continue;
			}

			auto bounding = appearance->getBoundingVolume();

			if (bounding == nullptr) {
				continue;
			}

			const Sphere& sphere = bounding->getBoundingSphere();

			Vector3 difference = (target->getPosition() + sphere.getCenter()) - rayStart;
			float targetRadius = sphere.getRadius() + rayRadius;

			float intersection = getPointIntersection(direction, difference, targetRadius, rayDistance);

			if (intersection == MISS) {
				continue;
			}

			auto collision = appearance->getCollisionVolume();

			if (collision == nullptr) {
				collision = bounding;
			}

			if (collision->isBoundingSphere()) {
				getRadiusCollision(target, collision->getBoundingSphere(), projectile, result);
			} else if (collision->isBoundingBox()) {
				getBoxCollision(target, collision->getBoundingBox(), projectile, result);
			} else {
				getAppearanceCollision(target, appearance, projectile, result);
			}
		}

		if (result.getDistance() != MISS) {
			break;
		}
	}

	return result.getDistance();
}

float SpaceCollisionManager::getChassisRadiusCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	const Matrix4& rotation = *target->getRotationMatrix();
	const Vector3& rayStart = projectile->getLastPosition();
	const Vector3& rayEnd = projectile->getThisPosition();
	const Vector3& targetPosition = target->getPosition();

	Vector3 localStart = getAxisAlignedVector(rayStart - targetPosition, rotation);
	Vector3 localEnd = getAxisAlignedVector(rayEnd - targetPosition, rotation);

	const Sphere& sphere = data->getChassisSphere();
	float distance = projectile->getDistance();
	float radius = projectile->getRadius();

	float intersection = getSphereIntersection(localStart, localEnd, sphere, radius, distance);
	if (intersection == MISS) {
		return MISS;
	}

	Vector3 collisionPoint = ((localEnd - localStart) * intersection) + localStart;

	result.setCollision(target, projectile, collisionPoint, intersection, Components::CHASSIS);

	return result.getDistance();
}

float SpaceCollisionManager::getChassisBoxCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	const Matrix4& rotation = *target->getRotationMatrix();
	const Vector3& rayStart = projectile->getLastPosition();
	const Vector3& rayEnd = projectile->getThisPosition();
	const Vector3& targetPosition = target->getPosition();

	Vector3 localStart = getAxisAlignedVector(rayStart - targetPosition, rotation);
	Vector3 localEnd = getAxisAlignedVector(rayEnd - targetPosition, rotation);

	const AABB& aabBox = data->getChassisBox();
	float radius = projectile->getRadius();
	float distance = projectile->getDistance();

	float intersection = getBoxIntersection(localStart, localEnd, aabBox, radius, distance);
	if (intersection == MISS) {
		return MISS;
	}

	Vector3 collisionPoint = ((localEnd - localStart) * intersection) + localStart;

	result.setCollision(target, projectile, collisionPoint, intersection, Components::CHASSIS);

	return result.getDistance();
}

float SpaceCollisionManager::getChassisAppearanceCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	auto appearance = target->getAppearanceTemplate();
	if (appearance == nullptr) {
		return MISS;
	}

	Ray ray = getAxisAlignedRay(target, projectile);
	float rayDistance = projectile->getDistance();
	float rayRadius = projectile->getRadius();

	SortedVector<IntersectionResult> results;
	appearance->intersects(ray, rayDistance, results);

	if (results.size() > 0) {
		float intersection = Math::max(results.getUnsafe(0).getIntersectionDistance() - rayRadius, 0.f) / Math::max(rayDistance, 1.f);
		Vector3 collisionPoint = (intersection * rayDistance * ray.getDirection()) + ray.getOrigin();

		result.setCollision(target, projectile, collisionPoint, intersection, Components::CHASSIS);
	}

	return result.getDistance();
}

float SpaceCollisionManager::getRadiusCollision(SceneObject* target, const Sphere& sphere, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	Matrix4 rotation = Matrix4();
	rotation.setRotationMatrix(target->getDirection()->toMatrix3());

	const Vector3& rayStart = projectile->getLastPosition();
	const Vector3& rayEnd = projectile->getThisPosition();
	const Vector3& targetPosition = target->getPosition();

	Vector3 localStart = getAxisAlignedVector(rayStart - targetPosition, rotation);
	Vector3 localEnd = getAxisAlignedVector(rayEnd - targetPosition, rotation);

	float distance = projectile->getDistance();
	float radius = projectile->getRadius();

	float intersection = getSphereIntersection(localStart, localEnd, sphere, radius, distance);

	if (intersection == MISS) {
		return MISS;
	}

	Vector3 collisionPoint = ((localEnd - localStart) * intersection) + localStart;

	result.setCollision(target, projectile, collisionPoint, intersection, Components::CHASSIS);

	return result.getDistance();
}

float SpaceCollisionManager::getBoxCollision(SceneObject* target, const AABB& box, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	Matrix4 rotation = Matrix4();
	rotation.setRotationMatrix(target->getDirection()->toMatrix3());

	const Vector3& rayStart = projectile->getLastPosition();
	const Vector3& rayEnd = projectile->getThisPosition();
	const Vector3& targetPosition = target->getPosition();

	Vector3 localStart = getAxisAlignedVector(rayStart - targetPosition, rotation);
	Vector3 localEnd = getAxisAlignedVector(rayEnd - targetPosition, rotation);

	float radius = projectile->getRadius();
	float distance = projectile->getDistance();

	float intersection = getBoxIntersection(localStart, localEnd, box, radius, distance);

	if (intersection == MISS) {
		return MISS;
	}

	Vector3 collisionPoint = ((localEnd - localStart) * intersection) + localStart;

	result.setCollision(target, projectile, collisionPoint, intersection, Components::CHASSIS);

	return result.getDistance();
}

float SpaceCollisionManager::getAppearanceCollision(SceneObject* target, const AppearanceTemplate* appearance, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	Ray ray = getAxisAlignedRay(target, projectile);
	float rayDistance = projectile->getDistance();
	float rayRadius = projectile->getRadius();

	SortedVector<IntersectionResult> results;
	appearance->intersects(ray, rayDistance, results);

	if (results.size() > 0) {
		float intersection = Math::max(results.getUnsafe(0).getIntersectionDistance() - rayRadius, 0.f) / Math::max(rayDistance, 1.f);
		Vector3 collisionPoint = (intersection * rayDistance * ray.getDirection()) + ray.getOrigin();

		result.setCollision(target, projectile, collisionPoint, intersection, Components::CHASSIS);
	}

	return result.getDistance();
}

float SpaceCollisionManager::getComponentHardpointCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	auto componentMap = target->getShipComponentMap();
	auto hitpointsMap = target->getCurrentHitpointsMap();

	if (componentMap == nullptr || hitpointsMap == nullptr) {
		return MISS;
	}

	const Matrix4& targetRotation = *target->getRotationMatrix();
	const Vector3& targetPosition = target->getPosition();
	const Vector3& rayStart = projectile->getLastPosition();
	const Vector3& rayEnd = projectile->getThisPosition();

	float rayDistance = projectile->getDistance();
	float rayRadius = projectile->getRadius();

	Vector3 localStart = getAxisAlignedVector(rayStart - targetPosition, targetRotation);
	Vector3 localEnd = getAxisAlignedVector(rayEnd - targetPosition, targetRotation);
	Vector3 localDirection = localEnd - localStart;

	Vector3 resultPosition = Vector3(MISS);
	float resultIntersection = MISS;

	if (result.getDistance() != MISS) {
		resultIntersection =  result.getDistance() / Math::max(rayDistance, 1.f);
		resultPosition = (localDirection * resultIntersection) + localStart;
	}

	const auto& targetableSlots = data->getTargetableSlots();

	for (int i = Components::CHASSIS; i < targetableSlots.size(); ++i) {
		int slot = i < 0 ? i : targetableSlots.get(i);

		String slotName = Components::shipComponentSlotToString(slot);
		uint32 compCrc = componentMap->get(slot);
		float hitpoints = hitpointsMap->get(slot);

		if (slot != Components::CHASSIS && (compCrc == 0 || hitpoints == 0)) {
			continue;
		}

		const auto& hardPoints = data->getHardpoints(slotName);

		for (int i = 0; i < hardPoints.size(); ++i) {
			const auto& key = hardPoints.elementAt(i).getKey();

			if (slot != Components::CHASSIS && key != compCrc) {
				continue;
			}

			const auto& hardpoint = hardPoints.elementAt(i).getValue();

			if (!hardpoint.isTargetable()) {
				continue;
			}

			const auto& boundingPosition = hardpoint.getSphere().getCenter();
			float boundingRadius = hardpoint.getSphere().getRadius();

			Vector3 localDifference = boundingPosition - localStart;
			float targetRadius = boundingRadius + rayRadius;

			float intersection = getPointIntersection(localDirection, localDifference, targetRadius, rayDistance);

			if (intersection == MISS) {
				continue;
			}

			auto volumeType = hardpoint.getVolumeType();

			switch (volumeType) {
				case ShipCollisionData::CollisionVolumeType::SPHERE: {
					intersection = getSphereIntersection(localStart, localEnd, hardpoint.getSphere(), rayRadius, rayDistance);
					break;
				}

				case ShipCollisionData::CollisionVolumeType::BOX: {
					intersection = getBoxIntersection(localStart, localEnd, hardpoint.getBox(), rayRadius, rayDistance);
					break;
				}

				case ShipCollisionData::CollisionVolumeType::MESH: {
					intersection = getHardpointIntersection(localStart, localEnd, hardpoint, rayRadius, rayDistance);
					break;
				}

				default: {
					intersection = MISS;
					break;
				}
			}

			if (intersection != MISS) {
				Vector3 collisionPoint = resultIntersection != MISS ? resultPosition : hardpoint.getPosition();
				result.setCollision(target, projectile, collisionPoint, intersection, slot);
				return result.getDistance();
			}

			float hardpointRadius = hardpoint.getRadius() + rayRadius;

			if (resultIntersection != MISS && resultPosition.squaredDistanceTo(boundingPosition) <= Math::sqr(hardpointRadius)) {
				result.setCollision(target, projectile, resultPosition, resultIntersection, slot);
				return result.getDistance();
			}
		}
	}

	return result.getDistance();
}

float SpaceCollisionManager::getPointIntersection(const Vector3& direction, const Vector3& difference, float radius, float distance) {
	float dotProduct = difference.dotProduct(direction);
	float sqrDistance = distance * distance;
	float sqrRadius = radius * radius;

	if (dotProduct < -sqrRadius || dotProduct > (sqrRadius + sqrDistance)) {
		return MISS;
	}

	float intersection = dotProduct >= sqrDistance ? 1.f : dotProduct > 0.f ? dotProduct / sqrDistance : 0.f;
	Vector3 position = intersection >= 1.f ? direction : intersection > 0.f ? direction * intersection : Vector3::ZERO;

	float sqrDifference = difference.squaredDistanceTo(position);
	if (sqrDifference > sqrRadius) {
		return MISS;
	}

	return intersection;
}

float SpaceCollisionManager::getSphereIntersection(const Vector3& rayStart, const Vector3& rayEnd, const Sphere& sphere, float radius, float distance) {
	Vector3 difference = sphere.getCenter() - rayStart;
	Vector3 direction = rayEnd - rayStart;

	float dotProduct = difference.dotProduct(direction);
	float sphereRadius = sphere.getRadius() + radius;
	float sqrRadius = sphereRadius * sphereRadius;
	float sqrDistance = distance * distance;

	if (dotProduct < -sqrRadius || dotProduct > (sqrRadius + sqrDistance)) {
		return MISS;
	}

	float intersection = dotProduct >= sqrDistance ? 1.f : dotProduct > 0.f ? dotProduct / sqrDistance : 0.f;
	Vector3 position = intersection >= 1.f ? direction : intersection > 0.f ? direction * intersection : Vector3::ZERO;

	float sqrDifference = difference.squaredDistanceTo(position);
	if (sqrDifference > sqrRadius) {
		return MISS;
	}

	float surface = distance > sphereRadius ? sphereRadius / distance : 0.f;
	float bounding = (1.f - (sqrDifference / sqrRadius)) * surface;

	return intersection - bounding;
}

float SpaceCollisionManager::getBoxIntersection(const Vector3& rayStart, const Vector3& rayEnd, const AABB& box, float radius, float distance) {
	Vector3 radiusV = Vector3(radius);
	Vector3 direction = rayEnd - rayStart;
	Vector3 invDirection = Vector3(
			direction.getX() == 0.f ? MISS : 1.f / direction.getX(),
			direction.getY() == 0.f ? MISS : 1.f / direction.getY(),
			direction.getZ() == 0.f ? MISS : 1.f / direction.getZ());

	Vector3 minBounds = *box.getMinBound() - radiusV;
	Vector3 maxBounds = *box.getMaxBound() + radiusV;

	float tMin = 0.0f;
	float tMax = distance;
	float epsilon = 0.1f;

	for (int axis = 0; axis < 3; ++axis) {
		float tNear = (minBounds[axis] - rayStart[axis]) * invDirection[axis];
		float tFar = (maxBounds[axis] - rayStart[axis]) * invDirection[axis];

		if (tNear > tFar) {
			std::swap(tNear, tFar);
		}

		if (tNear > tMax + epsilon || tFar < tMin - epsilon) {
			return MISS;
		}

		tMin = std::max(tMin, tNear);
		tMax = std::min(tMax, tFar);
	}

	if (tMin > tMax + epsilon || tMax < (0.f - epsilon) || tMin > (1.f + epsilon)) {
		return MISS;
	}

	return tMin;
}

float SpaceCollisionManager::getHardpointIntersection(const Vector3& localStart, const Vector3& localEnd, const ShipCollisionHardpoint& hardpoint, float radius, float distance) {
	const auto appearance = hardpoint.getAppearanceTemplate();
	if (appearance == nullptr) {
		return MISS;
	}

	const Matrix4* rotation = hardpoint.getRotation();
	const Vector3&  position = hardpoint.getPosition();

	Vector3 offsetStart = localStart - position;
	Vector3 offsetEnd = localEnd - position;

	if (rotation != nullptr) {
		const Matrix4& matrix = *rotation;
		offsetStart = offsetStart * matrix;
		offsetEnd = offsetEnd * matrix;
	}

	Vector3 offsetDirection = (offsetEnd - offsetStart) * (1.f / distance);
	Ray ray = Ray(offsetStart, offsetDirection);

	SortedVector<IntersectionResult> results;
	appearance->intersects(ray, distance, results);

	if (results.size() > 0) {
		return Math::max(results.getUnsafe(0).getIntersectionDistance() - radius, 0.f) / Math::max(distance, 1.f);
	}

	return MISS;
}

Ray SpaceCollisionManager::getAxisAlignedRay(SceneObject* target, const ShipProjectile* projectile) {
	const Vector3& position = target->getPosition();
	Matrix4 rotation;

	if (target->isShipObject()) {
		auto targetShip = target->asShipObject();

		if (targetShip != nullptr) {
			rotation = *targetShip->getRotationMatrix();
		}
	} else {
		rotation.setRotationMatrix(target->getDirection()->toMatrix3());
	}

	const Vector3& rayStart = projectile->getLastPosition();
	const Vector3& rayEnd = projectile->getThisPosition();
	float inverseDistance = 1.f / projectile->getDistance();

	Vector3 localStart = getAxisAlignedVector(rayStart - position, rotation);
	Vector3 localEnd = getAxisAlignedVector(rayEnd - position, rotation);
	Vector3 localDirection = (localEnd - localStart) * inverseDistance;

	return Ray(localStart, localDirection);
}

Vector3 SpaceCollisionManager::getAxisAlignedVector(const Vector3& position, const Matrix4& rotation) {
	return Vector3(position.getX(), position.getZ(), position.getY()) * rotation;
}
