#include "SpaceMath.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/managers/ship/ShipManager.h"

float SpaceMath::qInvSqrt(float x) {
	float xHalf = 0.5f * x;
	int32_t i = 0;

	memcpy(&i, &x, sizeof(int32_t));
	i = 1597463007 - (i >> 1);
	memcpy(&x, &i, sizeof(float));
	x = x * (1.5f - xHalf * x * x);

	return x;
}

float SpaceMath::qSqrt(float x) {
	return x <= FLT_EPSILON  ? 0.f : 1.f / qInvSqrt(x);
}

float SpaceMath::qNormalize(Vector3& value) {
	float sqrLength = value.squaredLength();

	if (sqrLength <= FLT_EPSILON) {
		return 0.f;
	}

	float invLength = qInvSqrt(sqrLength);
	value = value * invLength;

	return 1.f / invLength;
}

float SpaceMath::qNormalize(Quaternion& value) {
	float sqrLength = value.lengthSquared();

	if (sqrLength <= FLT_EPSILON) {
		return 0.f;
	}

	float invLength = qInvSqrt(sqrLength);
	value = value * invLength;

	return 1.f / invLength;
}

float SpaceMath::getIntersection(ShipObject* ship, const Vector3& position, float distance, float radius) {
	Vector3 difference = ship->getCurrentTransform().getVelocity() * distance;
	Vector3 direction = position - ship->getPosition();

	float dotProduct = difference.dotProduct(direction);
	float sqrDistance = distance * distance;
	float sqrRadius = radius * radius;

	if (dotProduct < -sqrRadius || dotProduct > (sqrRadius + sqrDistance)) {
		return FLT_MAX;
	}

	float intersection = dotProduct >= sqrDistance ? 1.f : dotProduct > 0.f ? dotProduct / sqrDistance : 0.f;
	Vector3 iPosition = intersection >= 1.f ? direction : intersection > 0.f ? direction * intersection : Vector3::ZERO;
	float sqrDifference = difference.squaredDistanceTo(iPosition);

	return sqrDifference > sqrRadius ? FLT_MAX : intersection;
}

float SpaceMath::getRotationTime(ShipObject* ship, const Vector3& rotation) {
	const auto& currentTransform = ship->getCurrentTransform();
	const auto& currentRotation = currentTransform.getRotation();

	float nextY = fabs(SpaceMath::getRotationRate(rotation.getX(), currentRotation.getX()));
	float nextP = fabs(SpaceMath::getRotationRate(rotation.getY(), currentRotation.getY()));

	if (nextY <= 0.001f && nextP <= 0.001f) {
		return 0.f;
	}

	float maxY = Math::max(ship->getActualYawRate(), 1.f);
	float maxP = Math::max(ship->getActualPitchRate(), 1.f);

	return Math::max(nextY / maxY, nextP / maxP);
}

float SpaceMath::getVelocityTime(ShipObject* ship, const Vector3& velocity) {
	return getRotationTime(ship, velocityToRotation(velocity));
}

float SpaceMath::getRotationRate(float thisRadians, float lastRadians) {
	float radians = thisRadians - lastRadians;

	if (radians > M_PI) {
		return radians - (M_PI * 2.f);
	}

	if (radians < -M_PI) {
		return radians + (M_PI * 2.f);
	}

	return radians;
}

Vector3 SpaceMath::getRotationRate(Vector3 thisRadians, Vector3 lastRadians) {
	return Vector3(getRotationRate(thisRadians.getX(), lastRadians.getX()),
				   getRotationRate(thisRadians.getY(), lastRadians.getY()),
				   getRotationRate(thisRadians.getZ(), lastRadians.getZ()));
}

Vector3 SpaceMath::rotationToVelocity(const Vector3& rotation) {
	float yaw = rotation.getX();
	float pitch = rotation.getY();

	float cosY = cos(yaw);
	float sinY = sin(yaw);
	float cosP = cos(pitch);
	float sinP = sin(pitch);

	Vector3 thrustV(cosY * cosP, sinY * cosP, sinP);
	qNormalize(thrustV);

	return thrustV;
}

Vector3 SpaceMath::velocityToRotation(const Vector3& velocity) {
	return Vector3(atan2(velocity.getY(),velocity.getX()), asin(velocity.getZ()), 0.f);
}

Vector3 SpaceMath::matrixToRotation(const Matrix4& m) {
	float yaw   = atan2(m[2][2], m[2][0]);
	float pitch = asin(m[2][1]);
	float roll  = atan2(-m[0][1], m[1][1]);

	return Vector3(yaw, pitch, roll);
}

Vector3 SpaceMath::matrixToVelocity(const Matrix4& matrix) {
	return Vector3(matrix[2][0], matrix[2][2], matrix[2][1]);
}

Vector3 SpaceMath::predictTransform(const SpaceTransform& transform, float timeSec) {
	Vector3 rotation = getRotationRate(transform.getYprDelta() * timeSec);
	Vector3 direction = rotateVector(transform.getVelocity(), rotation);

	return (direction * transform.getSpeed() * timeSec) + transform.getPosition();
}

Vector3 SpaceMath::rotateVector(const Vector3 &velocity, const Vector3 &rotation) {
	float yaw = rotation.getX();
	float pitch = rotation.getY();

	float vX = velocity.getX();
	float vY = velocity.getY();
	float vZ = velocity.getZ();

	if (fabs(yaw) >= 0.001f) {
		float cosY = cos(yaw);
		float sinY = sin(yaw);
		float x = cosY * vX - sinY * vY;
		float y = sinY * vX + cosY * vY;

		vX = x;
		vY = y;
	}

	if (fabs(pitch) >= 0.001f) {
		float cosP = cos(pitch);
		float sinP = sin(pitch);
		float y = cosP * vY - sinP * vZ;
		float z = sinP * vY + cosP * vZ;

		vY = y;
		vZ = z;
	}

	return Vector3(vX, vY, vZ);
}

Quaternion SpaceMath::rotationToQuaternion(const Vector3& rotation, bool precision) {
	float radY = getRotationRate(-rotation.getX() + M_PI_2);
	float radP = getRotationRate(rotation.getY());
	float radR = getRotationRate(rotation.getZ());

	if (!precision) {
		return RotationLookupTable::instance()->getDirection(radY, radP, radR);
	}

	int degY = Math::rad2deg(radY);
	int degP = Math::rad2deg(radP);
	int degR = Math::rad2deg(radR);

	Quaternion qDirection;
	qDirection.rotate(Vector3::UNIT_Z, -degR);
	qDirection.rotate(Vector3::UNIT_X, -degP);
	qDirection.rotate(Vector3::UNIT_Y, degY);
	qNormalize(qDirection);

	return qDirection;
}
