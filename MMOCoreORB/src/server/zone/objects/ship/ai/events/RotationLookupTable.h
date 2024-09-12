#ifndef ROTATIONLOOKUPTABLE_H_
#define ROTATIONLOOKUPTABLE_H_

#include "engine/engine.h"
#include "server/zone/packets/ship/PackedQuaternion.h"

class RotationLookupTable : public Singleton<RotationLookupTable>, public Object, public Logger {
protected:
    const static int Y_STEPS = 90;
    const static int P_STEPS = 90;
    const static int R_STEPS = 60;

    constexpr static float Y_INCREMENT = 360.f / Y_STEPS;
    constexpr static float P_INCREMENT = 360.f / P_STEPS;
    constexpr static float R_INCREMENT = 360.f / R_STEPS;

    constexpr static float Y_INVERSE_INCREMENT = 1.f / Y_INCREMENT;
    constexpr static float P_INVERSE_INCREMENT = 1.f / P_INCREMENT;
    constexpr static float R_INVERSE_INCREMENT = 1.f / R_INCREMENT;

    const static int YPR_TOTAL = Y_STEPS * P_STEPS * R_STEPS;

    Vector<PackedQuaternion> directionTable;

public:
    RotationLookupTable() : directionTable(YPR_TOTAL, YPR_TOTAL) {
        setLoggingName("RotationLookupTable");
        initialize();
    }

    void initialize();

    int combineIndices(int indexY, int indexP, int indexR) const;

    PackedQuaternion getPackedDirection(float yaw, float pitch, float roll);

    Quaternion getDirection(float yaw, float pitch, float roll);
};

#endif // ROTATIONLOOKUPTABLE_H_
