/*
*	RotationLookupTable.cpp
*	By: Smoki
*/


#include "RotationLookupTable.h"

void RotationLookupTable::initialize() {
	for (int stepY = 0; stepY < ANGLE_STEPS; ++stepY) {
		for (int stepP = 0; stepP < ANGLE_STEPS; ++stepP) {
			for (int stepR = 0; stepR < ANGLE_STEPS; ++stepR) {
				float yaw   = (stepY * ANGLE_INCREMENT) - 180.f;
				float pitch = (stepP * ANGLE_INCREMENT) - 180.f;
				float roll  = (stepR * ANGLE_INCREMENT) - 180.f;

				Quaternion qY(Vector3::UNIT_Y, Math::deg2rad(yaw));
				Quaternion qP(Vector3::UNIT_X, Math::deg2rad(-pitch));
				Quaternion qR(Vector3::UNIT_Z, Math::deg2rad(-roll));
				Quaternion direction = qY * qP * qR;

				if (direction == Quaternion::ZERO) {
					direction = Quaternion::IDENTITY;
				} else {
					direction.normalize();
				}

				uint32 dKey = combineIndices(stepY, stepP, stepR);
				directionTable.put(dKey, direction);
			}
		}
	}
}

uint32 RotationLookupTable::combineIndices(int indexY, int indexP, int indexR) {
	uint32 key = 0;
	key |= (indexY << 16);
	key |= (indexP << 8);
	key |= indexR;
	return key;
}

const Quaternion& RotationLookupTable::getDirection(float yaw, float pitch, float roll) {
	float stepY = (Math::rad2deg(yaw) + 180.f) * INVERSE_INCREMENT;
	float stepP = (Math::rad2deg(pitch) + 180.f) * INVERSE_INCREMENT;
	float stepR = (Math::rad2deg(roll) + 180.f) * INVERSE_INCREMENT;

	uint32 key = combineIndices(stepY, stepP, stepR);

	return directionTable.get(key);
}
