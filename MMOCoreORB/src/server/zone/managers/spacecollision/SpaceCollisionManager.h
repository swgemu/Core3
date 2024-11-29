#ifndef SPACECOLLISIONMANAGER_H_
#define SPACECOLLISIONMANAGER_H_

#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/managers/spacecollision/SpaceCollisionResult.h"

#define SPACE_COLLISION_DEBUG

class SpaceCollisionManager : public Singleton<SpaceCollisionManager>, public Logger, public Object {
public:
	const static constexpr float MISS = FLT_MAX;

	SpaceCollisionManager() {
		setLoggingName("SpaceCollisionManager");
	}

	float getProjectileCollision(ShipObject* ship, const ShipProjectile* projectile, SpaceCollisionResult& result, Vector<ManagedReference<SceneObject*>>& targetVectorCopy);

	float getPointIntersection(const Vector3& rayStart, const Vector3& rayEnd, float radius, float distance);

private:
	float getChassisRadiusCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result);

	float getChassisBoxCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result);

	float getChassisAppearanceCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result);

	float getRadiusCollision(SceneObject* target, const Sphere& sphere, const ShipProjectile* projectile, SpaceCollisionResult& result);

	float getBoxCollision(SceneObject* target, const AABB& box, const ShipProjectile* projectile, SpaceCollisionResult& result);

	float getAppearanceCollision(SceneObject* target, const AppearanceTemplate* appearance, const ShipProjectile* projectile, SpaceCollisionResult& result);

	float getComponentHardpointCollision(ShipObject* target, const ShipCollisionData* data, const ShipProjectile* projectile, SpaceCollisionResult& result);

	float getSphereIntersection(const Vector3& rayStart, const Vector3& rayEnd, const Sphere& targetPosition, float radius, float distance);

	float getBoxIntersection(const Vector3& rayStart, const Vector3& rayEnd, const AABB& box, float radius, float distance);

	float getHardpointIntersection(const Vector3& localStart, const Vector3& localEnd, const ShipCollisionHardpoint& hardpoint, float radius, float distance);

	Ray getAxisAlignedRay(SceneObject* target, const ShipProjectile* projectile);

	Vector3 getAxisAlignedVector(const Vector3& vector, const Matrix4& rotation);
};

#endif // SPACECOLLISIONMANAGER_H_
