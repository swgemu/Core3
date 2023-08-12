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
			case ShipCollisionData::CollisionVolumeType::RADIUS: {
				getChassisRadiusCollision(target, data, projectile, result);
				break;
			}

			case ShipCollisionData::CollisionVolumeType::BOX: {
				getChassisBoxCollision(target, data, projectile, result);
				break;
			}

			case ShipCollisionData::CollisionVolumeType::MESH: {
				getChassisAppearanceCollision(target, data, projectile, result);
				getComponentHardpointCollision(target, data, projectile, result);
				break;
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

	float intersection = getBoxIntersection(localStart, localEnd, aabBox, radius);
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
	float distance = projectile->getDistance();
	float radius = projectile->getRadius();

	SortedVector<IntersectionResult> results;
	appearance->intersects(ray, distance, results);

	if (results.size() > 0) {
		float intersection = Math::max(results.getUnsafe(0).getIntersectionDistance() - radius, 0.f);
		bool hitFront = ((intersection * ray.getDirection().getZ()) + ray.getOrigin().getZ()) <= 0.f;

		result.setCollision(target, projectile, intersection / distance, Components::CHASSIS, hitFront);
	}

	return result.getDistance();
}

float SpaceCollisionManager::getComponentHardpointCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	auto componentMap = target->getShipComponentMap();
	auto hitpointsMap = target->getCurrentHitpointsMap();

	if (componentMap == nullptr || hitpointsMap == nullptr) {
		return MISS;
	}

	const Matrix4& rotation = *target->getRotationMatrix();
	const Vector3& rayStart = projectile->getLastPosition();
	const Vector3& rayEnd = projectile->getThisPosition();
	const Vector3& targetPosition = target->getPosition();

	float distance = projectile->getDistance();
	float radius = projectile->getRadius();

	Vector3 localStart = getAxisAlignedVector(rayStart - targetPosition, rotation);
	Vector3 localEnd = getAxisAlignedVector(rayEnd - targetPosition, rotation);

	for (uint32 slot = 0; slot <= Components::FIGHTERSLOTMAX; ++slot) {
		String slotName = Components::shipComponentSlotToString(slot);

		auto compCrc = componentMap->get(slot);
		if (compCrc == 0) {
			continue;
		}

		float hitpoints = hitpointsMap->get(slot);
		if (hitpoints == 0) {
			continue;
		}

		const auto& hardPoints = data->getHardpoints(slotName);

		for (int i = 0; i < hardPoints.size(); ++i) {
			auto key = hardPoints.getUnsafe(i).getKey();
			if (key != compCrc) {
				continue;
			}

			const auto& hardPoint = hardPoints.getUnsafe(i).getValue();
			const auto& sphere = hardPoint.getSphere();

			float intersection = getSphereIntersection(localStart, localEnd, sphere, radius, distance);
			if (intersection == MISS) {
				continue;
			}

			bool hitFront = (((localEnd.getZ() - localStart.getZ()) * intersection) + localStart.getZ()) >= 0.f;

			result.setCollision(target, projectile, intersection, slot, hitFront);

			return result.getDistance();
		}
	}

	return MISS;
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

float SpaceCollisionManager::getBoxIntersection(const Vector3& rayStart, const Vector3& rayEnd, const AABB& box, float radius) {
	Vector3 radiusV = Vector3(radius);
	Vector3 direction = rayEnd - rayStart;
	Vector3 invDirection = Vector3(1.f / direction.getX(), 1.f / direction.getY(), 1.f / direction.getZ());

	Vector3 minBounds = *box.getMinBound() - radiusV;
	Vector3 maxBounds = *box.getMaxBound() + radiusV;

	float tMin = -FLT_MAX;
	float tMax = FLT_MAX;
	float epsilon = 0.1f;

	for (int axis = 0; axis < 3; ++axis) {
		float tNear = (minBounds[axis] - rayStart[axis]) * invDirection[axis];
		float tFar = (maxBounds[axis] - rayStart[axis]) * invDirection[axis];

		if (tNear > tFar) {
			float temp = tNear;
			tNear = tFar;
			tFar = temp;
		}

		if (tNear > tMax + epsilon || tFar < tMin - epsilon) {
			return MISS;
		}

		tMin = Math::max(tMin, tNear);
		tMax = Math::min(tMax, tFar);

		float intersectionPoint = (direction[axis] * tMin) + rayStart[axis];
		if (intersectionPoint < (minBounds[axis] - epsilon) || intersectionPoint > (maxBounds[axis] + epsilon)) {
			return MISS;
		}
	}

	if (tMin > tMax + epsilon || tMax < (0.f - epsilon) || tMin > (1.f + epsilon)) {
		return MISS;
	}

	return tMin;
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
