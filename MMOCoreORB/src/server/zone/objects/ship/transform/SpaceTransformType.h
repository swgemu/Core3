#ifndef SPACETRANSFORMTYPE_H_
#define SPACETRANSFORMTYPE_H_

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

class SpaceTransformType : public Object {
public:
	enum Type : int {
		NONE = -1,
		SLOW = 0,
		AUTO = 1,
		FAST = 2,
		DOCK = 3,
		FORM = 4,
		SIZE
	};

	enum Rotation : int {
		YAW = 0,
		PITCH = 1,
		ROLL = 2
	};

	constexpr static float DAMP_RADIUS_MAX = 128.f;
	constexpr static float DAMP_RADIUS_MIN = 32.f;

protected:
	Vector3 rotationDamp;
	Vector3 rotationRate;

	float throttleMin;
	float throttleMax;

	int transformType;

public:
	SpaceTransformType() {
		rotationDamp = Vector3(1.f, 1.f, 1.f);
		rotationRate = Vector3(1.f, 1.f, 0.5f);

		throttleMin = 0.f;
		throttleMax = 1.f;

		transformType = NONE;
	}

	SpaceTransformType(ShipObject* ship, int type = AUTO);

	void initializeType(ShipObject* ship, int type = AUTO);

	void setTransformType(int type) {
		if (transformType == type) {
			return;
		}

		transformType = type;
		setThrottleRate();
		setRotationRate();
	}

	const Vector3& getRotationRate() const {
		return rotationRate;
	}

	float getThrottleMin() const {
		return throttleMin;
	}

	float getThrottleMid() const {
		return (throttleMax + throttleMin) * 0.5f;
	}

	float getThrottleMax() const {
		return throttleMax;
	}

	int getTransformType() const {
		return transformType;
	}

private:
	void setThrottleRate();

	void setRotationRate();

	void setRotationDamp(float radius);

public:
	String toDebugString(bool includePrivate = false) const {
		String typeStr = "NONE";

		if (transformType == SLOW) {
			typeStr = "SLOW";
		} else if (transformType == AUTO) {
			typeStr = "AUTO";
		} else if (transformType == FAST) {
			typeStr = "FAST";
		} else if (transformType == DOCK) {
			typeStr = "DOCK";
		} else if (transformType == FORM) {
			typeStr = "FORM";
		}

		StringBuffer msg;
		msg << "SpaceTransformType: " << typeStr << endl
			<< "  throttleMin:      " << throttleMin << endl
			<< "  throttleMax:      " << throttleMax << endl
			<< "  rotationRate:     " << rotationRate.toString() << endl;


		return msg.toString();
	}
};

#endif // SPACETRANSFORMTYPE_H_
