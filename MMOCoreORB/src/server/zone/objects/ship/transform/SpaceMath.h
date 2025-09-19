#ifndef SPACEMATH_H_
#define SPACEMATH_H_

namespace server {
	namespace zone {
		namespace objects {
			namespace ship {
				class ShipObject;
			}
		}
	}
}

#include "engine/engine.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/ship/ai/events/RotationLookupTable.h"
#include "server/zone/objects/ship/transform/SpaceTransform.h"

class SpaceMath {
public:
	static float qInvSqrt(float x);

	static float qSqrt(float x);

	static float qNormalize(Vector3& value);

	static float qNormalize(Quaternion& value);

	static float getIntersection(ShipObject* ship, const Vector3& position, float distance, float radius = 1.f);

	static float getRotationTime(ShipObject* ship, const Vector3& rotation);

	static float getVelocityTime(ShipObject* ship, const Vector3& velocity);

	static float getRotationRate(float thisRadians, float lastRadians = 0.f);

	static Vector3 getRotationRate(Vector3 thisRadians, Vector3 lastRadians = Vector3::ZERO);

	static Vector3 rotationToVelocity(const Vector3& rotation);

	static Vector3 velocityToRotation(const Vector3& velocity);

	static Vector3 matrixToRotation(const Matrix4& matrix);

	static Vector3 matrixToVelocity(const Matrix4& matrix);

	static Vector3 predictTransform(const SpaceTransform& transform, float timeSec);

	static Vector3 rotateVector(const Vector3 &velocity, const Vector3 &rotation);

	static Quaternion rotationToQuaternion(const Vector3& rotation, bool precision = true);
};

#endif // SPACEMATH_H_
