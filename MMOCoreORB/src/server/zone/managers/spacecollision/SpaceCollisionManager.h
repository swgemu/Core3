#ifndef SPACECOLLISIONMANAGER_H_
#define SPACECOLLISIONMANAGER_H_

#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/managers/spacecollision/SpaceCollisionResult.h"

#define SPACE_COLLISION_DEBUG

class SpaceCollisionManager : public Singleton<SpaceCollisionManager> {
public:
	const static constexpr float MISS = FLT_MAX;

	static float getProjectileCollision(ShipObject* ship, const ShipProjectile* projectile, SpaceCollisionResult& result, Vector<ManagedReference<ShipObject*>>& targetVectorCopy);

	static float getPointIntersection(const Vector3& rayStart, const Vector3& rayEnd, float radius, float distance);

private:
	static float getChassisRadiusCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result);

	static float getChassisBoxCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result);

	static float getChassisAppearanceCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result);

	static float getComponentHardpointCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result);

	static float getSphereIntersection(const Vector3& rayStart, const Vector3& rayEnd, const Sphere& targetPosition, float radius, float distance);

	static float getBoxIntersection(const Vector3& rayStart, const Vector3& rayEnd, const AABB& box, float radius, float distance);

	static float getHardpointIntersection(const Vector3& localStart, const Vector3& localEnd, const ShipCollisionHardpoint& hardpoint, float radius, float distance);

	static Ray getAxisAlignedRay(ShipObject* target, const ShipProjectile* projectile);

	static Vector3 getAxisAlignedVector(const Vector3& vector, const Matrix4& rotation);
};

#endif // SPACECOLLISIONMANAGER_H_
