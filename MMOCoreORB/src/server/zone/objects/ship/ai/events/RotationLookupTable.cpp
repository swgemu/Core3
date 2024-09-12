#include "RotationLookupTable.h"

void RotationLookupTable::initialize() {
    for (int stepY = 0; stepY < Y_STEPS; ++stepY) {
        for (int stepP = 0; stepP < P_STEPS; ++stepP) {
            for (int stepR = 0; stepR < R_STEPS; ++stepR) {

            	float y = (stepY * Y_INCREMENT) - 180.f;
                float p = (stepP * P_INCREMENT) - 180.f;
                float r = (stepR * R_INCREMENT) - 180.f;

                Quaternion qY(Vector3::UNIT_Y, Math::deg2rad(y));
                Quaternion qP(Vector3::UNIT_X, Math::deg2rad(-p));
                Quaternion qR(Vector3::UNIT_Z, Math::deg2rad(-r));
                Quaternion direction = qY * qP * qR;

                if (direction == Quaternion::ZERO) {
                    direction = Quaternion::IDENTITY;
                } else {
                    direction.normalize();
                }

                int index = combineIndices(stepY, stepP, stepR);
                directionTable.add(index, PackedQuaternion(direction));
            }
        }
    }
}

int RotationLookupTable::combineIndices(int indexY, int indexP, int indexR) const {
    return (indexY * P_STEPS * R_STEPS) + (indexP * R_STEPS) + indexR;
}

PackedQuaternion RotationLookupTable::getPackedDirection(float yaw, float pitch, float roll) {
    int stepY = (int)round(Math::rad2deg(yaw + M_PI) * Y_INVERSE_INCREMENT) % Y_STEPS;
    int stepP = (int)round(Math::rad2deg(pitch + M_PI) * P_INVERSE_INCREMENT) % P_STEPS;
    int stepR = (int)round(Math::rad2deg(roll + M_PI) * R_INVERSE_INCREMENT) % R_STEPS;

    return directionTable.get(combineIndices(stepY, stepP, stepR));
}

Quaternion RotationLookupTable::getDirection(float yaw, float pitch, float roll) {
    return getPackedDirection(yaw, pitch, roll).get();
}
