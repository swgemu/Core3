#ifndef ROTATIONLOOKUPTABLE_H_
#define ROTATIONLOOKUPTABLE_H_

#include "engine/engine.h"

class RotationLookupTable: public Singleton<RotationLookupTable>, public Object, public Logger {
protected:
	const static int ANGLE_STEPS = 72;
	const static int ANGLE_INCREMENT = 5;
	constexpr static float INVERSE_INCREMENT = 1.f / ANGLE_INCREMENT;

	HashTable<uint32, Quaternion> directionTable;

public:
	RotationLookupTable() {
		setLoggingName("RotationLookupTable");
		initialize();
	}

	void initialize();

	uint32 combineIndices(int indexY, int indexP, int indexR);

	const Quaternion& getDirection(float yaw, float pitch, float roll);
};

#endif // MATRIX4LOOKUPTABLE_H_
