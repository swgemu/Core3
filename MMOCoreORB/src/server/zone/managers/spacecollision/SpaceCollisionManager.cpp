#include "SpaceCollisionManager.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "server/zone/objects/ship/ComponentSlots.h"

float SpaceCollisionManager::getProjectileCollision(ShipObject* ship, const ShipProjectile* projectile, SpaceCollisionResult& result, Vector<ManagedReference<ShipObject*>>& targetVectorCopy) {
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

		Vector3 difference = target->getPosition() - rayStart;
		float targetRadius = target->getBoundingRadius() + rayRadius;

		float intersection = getPointIntersection(direction, difference, targetRadius, rayDistance);
		if (intersection == MISS) {
			continue;
		}

		auto data = ShipManager::instance()->getCollisionData(target);
		if (data == nullptr) {
			continue;
		}

		auto type = data->getVolumeType();

		switch (type) {
			case ShipCollisionData::CollisionVolumeType::SPHERE: {
				getChassisRadiusCollision(target, data, projectile, result);
				break;
			}

			case ShipCollisionData::CollisionVolumeType::BOX: {
				getChassisBoxCollision(target, data, projectile, result);
				break;
			}

			case ShipCollisionData::CollisionVolumeType::MESH: {
				getChassisAppearanceCollision(target, data, projectile, result);
				break;
			}
		}

		if (data->getHardpointSize() > 0) {
			getComponentHardpointCollision(target, data, projectile, result);
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

	bool hitFront = (((localEnd.getZ() - localStart.getZ()) * intersection) + localStart.getZ()) >= 0.f;

	result.setCollision(target, projectile, intersection, Components::CHASSIS, hitFront);

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

	bool hitFront = (((localEnd.getZ() - localStart.getZ()) * intersection) + localStart.getZ()) >= 0.f;

	result.setCollision(target, projectile, intersection, Components::CHASSIS, hitFront);

	return result.getDistance();
}

float SpaceCollisionManager::getChassisAppearanceCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	const auto shot = target->getObjectTemplate();
	if (shot == nullptr) {
		return MISS;
	}

	const auto appearance = shot->getAppearanceTemplate();
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

		bool hitFront = ((intersection * rayDistance * ray.getDirection().getZ()) + ray.getOrigin().getZ()) >= 0.f;

		result.setCollision(target, projectile, intersection, Components::CHASSIS, hitFront);
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

	for (int slot = -1; slot <= Components::CAPITALSLOTMAX; ++slot) {
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
				bool hitFront = (((localEnd.getZ() - localStart.getZ()) * intersection) + localStart.getZ()) >= 0.f;
				result.setCollision(target, projectile, intersection, slot, hitFront);
				return result.getDistance();
			}

			float hardpointRadius = hardpoint.getRadius() + rayRadius;

			if (resultIntersection != MISS && resultPosition.squaredDistanceTo(boundingPosition) <= Math::sqr(hardpointRadius)) {
				result.setCollision(target, projectile, resultIntersection, slot, resultPosition.getZ() >= 0.f);
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

Ray SpaceCollisionManager::getAxisAlignedRay(ShipObject* target, const ShipProjectile* projectile) {
	const Vector3& position = target->getPosition();
	const Matrix4& rotation = *target->getRotationMatrix();

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
