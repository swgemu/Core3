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

	static float getIntersection(const SpaceTransform& transform, const Vector3& position, float distance, float radius = 1.f);

	static float getRotationTime(const Vector3& rotationEnd, const Vector3 rotationStart = Vector3::ZERO, float maxY = M_PI, float maxP = M_PI);

	static float getVelocityTime(const Vector3& velocityEnd, const Vector3 velocityStart = Vector3::ZERO, float maxY = M_PI, float maxP = M_PI);

	static float getRotationRate(float rotationEnd, float rotationStart = 0.f);

	static Vector3 getRotationRate(const Vector3& rotationEnd, const Vector3 rotationStart = Vector3::ZERO);

	static Vector3 rotationToVelocity(const Vector3& rotation);

	static Vector3 velocityToRotation(const Vector3& velocity);

	static Vector3 matrixToRotation(const Matrix4& matrix);

	static Vector3 matrixToVelocity(const Matrix4& matrix);

	static Vector3 predictTransform(const SpaceTransform& transform, float timeSec);

	static Vector3 rotateVector(const Vector3 &velocity, const Vector3 &rotation);

	static Quaternion rotationToQuaternion(const Vector3& rotation, bool precision = true);
};

#endif // SPACEMATH_H_
