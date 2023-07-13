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
	uint32 syncStamp = ship->getSyncStamp();

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

    Vector3 intersectionPoint = ((localEnd - localStart) * intersection) + localStart;
    bool hitFront = intersectionPoint.dotProduct(targetPosition) >= 0.f;

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

    Vector3 intersectionPoint = ((localEnd - localStart) * intersection) + localStart;
    bool hitFront = intersectionPoint.dotProduct(targetPosition) >= 0.f;

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

	SortedVector<IntersectionResult> results;
	appearance->intersects(ray, distance, results);

	if (results.size() > 0) {
		float intersection = results.getUnsafe(0).getIntersectionDistance();

	    Vector3 intersectionPoint = (ray.getDirection() * distance * intersection) + ray.getOrigin();
	    bool hitFront = intersectionPoint.dotProduct(target->getPosition()) >= 0.f;

		result.setCollision(target, projectile, intersection / distance, Components::CHASSIS);
	}

	return result.getDistance();
}

float SpaceCollisionManager::getComponentHardpointCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result) {
	auto hitpointsMap = target->getCurrentHitpointsMap();
	if (hitpointsMap == nullptr) {
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

		auto compCrc = target->getShipComponentMap()->get(slot);
		if (compCrc == 0) {
			continue;
		}

		float hitpoints = target->getCurrentHitpointsMap()->get(slot);
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

		    Vector3 intersectionPoint = ((localEnd - localStart) * intersection) + localStart;
		    bool hitFront = intersectionPoint.dotProduct(targetPosition) >= 0.f;

			result.setCollision(target, projectile, intersection, slot);
			break;
		}
	}

	return result.getDistance();
}

float SpaceCollisionManager::getPointIntersection(const Vector3& direction, const Vector3& difference, float radius, float distance) {
	float dotProduct = difference.dotProduct(direction);
	float sqrDistance = distance * distance;
	float sqrRadius = radius * radius;

	if (dotProduct < -sqrRadius || dotProduct > (sqrRadius + sqrDistance)) {
		return FLT_MAX;
	}

	float intersection = dotProduct >= sqrDistance ? 1.f : dotProduct > 0.f ? dotProduct / sqrDistance : 0.f;
	Vector3 position = intersection >= 1.f ? direction : intersection > 0.f ? direction * intersection : Vector3::ZERO;

	float sqrDifference = difference.squaredDistanceTo(position);
	if (sqrDifference > sqrRadius) {
		return FLT_MAX;
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
		return FLT_MAX;
	}

	float intersection = dotProduct >= sqrDistance ? 1.f : dotProduct > 0.f ? dotProduct / sqrDistance : 0.f;
	Vector3 position = intersection >= 1.f ? direction : intersection > 0.f ? direction * intersection : Vector3::ZERO;

	float sqrDifference = difference.squaredDistanceTo(position);
	if (sqrDifference > sqrRadius) {
		return FLT_MAX;
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

	Vector3 vMin = (minBounds - rayStart) * invDirection;
	Vector3 vMax = (maxBounds - rayStart) * invDirection;

	float tMin = Math::max(Math::max(Math::min(vMin.getX(), vMax.getX()), Math::min(vMin.getY(), vMax.getY())), Math::min(vMin.getZ(), vMax.getZ()));
	float tMax = Math::min(Math::min(Math::max(vMin.getX(), vMax.getX()), Math::max(vMin.getY(), vMax.getY())), Math::max(vMin.getZ(), vMax.getZ()));

	if (tMin > tMax || tMax > 1.f) {
		return MISS;
	}

	Vector3 intersectionPoint = (direction * tMin) + rayStart;
	float epsilon = 0.1f;

	if (intersectionPoint.getX() < (minBounds.getX() - epsilon) || intersectionPoint.getX() > (maxBounds.getX() + epsilon)
	 || intersectionPoint.getY() < (minBounds.getY() - epsilon) || intersectionPoint.getY() > (maxBounds.getY() + epsilon)
	 || intersectionPoint.getZ() < (minBounds.getZ() - epsilon) || intersectionPoint.getZ() > (maxBounds.getZ() + epsilon)) {
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
