#ifndef SHIPOBJECTTRANSFORM_H_
#define SHIPOBJECTTRANSFORM_H_

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
#include "server/zone/objects/ship/transform/SpaceMath.h"
#include "server/zone/objects/ship/transform/SpaceTransform.h"
#include "server/zone/objects/ship/transform/SpaceTransformType.h"

class ShipObjectTransform : public Object {
public:
	constexpr static float VELOCITY_MAX = 512.f;
	constexpr static float DELTA_MAX = 0.5f;
	constexpr static float DELTA_MIN = 0.1f;

	constexpr static float POSITION_EPSILON = 0.25f;
	constexpr static float ROTATION_EPSILON = 0.25f * (M_PI / 180.0f);

private:
	mutable ReadWriteLock mutex;
	uint64 serverTime;
	float deltaTime;

protected:
	SpaceTransform previousTransform;
	SpaceTransform currentTransform;
	SpaceTransform nextTransform;

	SpaceTransformType transformType;
	float nextDistance;
	float nextRotation;

public:
	ShipObjectTransform() : Object() {
		serverTime = 0ull;
		deltaTime = 0.f;

		nextDistance = 0.f;
		nextRotation = 0.f;
	}

	ShipObjectTransform(ShipObject* ship);

	void initializeTransform(ShipObject* ship);

	void setCurrentTransform(ShipObject* ship);

	void setNextTransform(const Vector3& position, float speed = VELOCITY_MAX, int model = SpaceTransformType::AUTO);

	void setNextTransform(const SpaceTransform& transform, int model = SpaceTransformType::AUTO);

	void updateTransform(ShipObject* ship, bool lightUpdate = false, bool notifyClient = true);

	void broadcastTransform(ShipObject* ship);

	const SpaceTransform& getPreviousTransform() const {
		return previousTransform;
	}

	const SpaceTransform& getCurrentTransform() const {
		return currentTransform;
	}

	const SpaceTransform& getNextTransform() const {
		return nextTransform;
	}

	float getNextDistance() const {
		return nextDistance;
	}

	float getNextRotation() const {
		return nextRotation;
	}

private:
	void setTransform(ShipObject* ship);

	void setSpeed(ShipObject* ship);

	void setRotation(ShipObject* ship);

	void setPosition(ShipObject* ship);

	void setVelocity(ShipObject* ship);

	void updateCurrentTransform(ShipObject* ship);

	void updateNextTransform(ShipObject* ship);

	void updateShip(ShipObject* ship);

	void setDeltaTime() {
		uint64 miliTime = System::getMiliTime();
		uint64 miliDiff = miliTime - serverTime;

		serverTime = miliTime;
		deltaTime = Math::clamp(0.f, miliDiff * 0.001f, (float)DELTA_MAX);
	}

	bool isScheduled() const {
		return (System::getMiliTime() - serverTime) >= (uint64)(DELTA_MIN * 1000);
	}

	bool isStaticUpdate() const {
		return deltaTime < DELTA_MIN || (nextRotation <= ROTATION_EPSILON && nextDistance <= POSITION_EPSILON && currentTransform.getSpeed() <= 0.f);
	}

	bool isInertiaUpdate() const {
		return currentTransform.getSpeed() == previousTransform.getSpeed() && currentTransform.getRotation() == previousTransform.getRotation() && currentTransform.getVelocity() == previousTransform.getVelocity();
	}

public:
	String toDebugString() const {
		StringBuffer msg;
		msg << "ShipObjectTransform: "
			<< "  deltaTime:         " << deltaTime << endl
			<< "  currentTransform:  " << endl << currentTransform.toDebugString() << endl
			<< "  nextTransform:     " << endl << nextTransform.toDebugString() << endl
			<< "  transformType:     " << endl << transformType.toDebugString() << endl
			<< "  nextRotation:      " << nextRotation << endl
			<< "  nextDistance:      " << nextDistance << endl;

		return msg.toString();
	}
};

#endif // SHIPOBJECTTRANSFORM_H_
