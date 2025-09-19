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
#include "server/zone/objects/ship/ai/events/RotationLookupTable.h"

class ShipObjectTransform : public Object {
public:
	constexpr static float VELOCITY_MAX = 512.f;

	enum RotationAxis : int {
		YAW = 0,
		PITCH = 1,
		ROLL = 2
	};

	enum FlightModel : int {
		SLOW = 0,
		AUTO = 1,
		FAST = 2,
		DOCK = 3,
	};

private:
	mutable ReadWriteLock mutex;
	uint64 serverTime;
	float deltaTime;

protected:
	SpaceTransform previousTransform;
	SpaceTransform currentTransform;
	SpaceTransform nextTransform;

	float nextDistance;
	int flightModel;

public:
	ShipObjectTransform() : Object() {
		serverTime = 0ull;
		deltaTime = 0.f;

		nextDistance = 0.f;
		flightModel = AUTO;
	}

	ShipObjectTransform(ShipObject* ship);

	void initializeTransform(ShipObject* ship);

	void setCurrentTransform(ShipObject* ship);

	void setNextTransform(const Vector3& position, float speed = VELOCITY_MAX, int model = FlightModel::AUTO);

	void setNextTransform(const SpaceTransform& transform, int model = FlightModel::AUTO);

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

	float getFlightModel() const {
		return flightModel;
	}

private:
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
		deltaTime = Math::clamp(0.f, miliDiff * 0.001f, 10000.f);
	}

	bool isStaticUpdate() const {
		return deltaTime <= 0.f || (nextDistance <= 1.f && currentTransform.getSpeed() <= 0.f && previousTransform.getSpeed() <= 0.f);
	}

	bool isInertiaUpdate() const {
		return currentTransform.getSpeed() == previousTransform.getSpeed()
			&& currentTransform.getRotation() == previousTransform.getRotation()
			&& currentTransform.getVelocity() == previousTransform.getVelocity();
	}

	float getThrottleMin() {
		switch (flightModel) {
			case FlightModel::SLOW:	return 0.f;
			case FlightModel::AUTO:	return 0.f;
			case FlightModel::FAST:	return 0.5f;
			case FlightModel::DOCK:	return 0.f;
			default:				return 0.f;
		}
	}

	float getThrottleMax() {
		switch (flightModel) {
			case FlightModel::SLOW:	return 0.5f;
			case FlightModel::AUTO:	return 1.f;
			case FlightModel::FAST:	return 1.f;
			case FlightModel::DOCK:	return 0.5f;
			default:				return 1.f;
		}
	}

public:
	String toDebugString() const {
		String flightStr = "";

		switch (flightModel) {
			case FlightModel::SLOW:	flightStr = "SLOW"; break;
			case FlightModel::AUTO:	flightStr = "AUTO"; break;
			case FlightModel::FAST:	flightStr = "FAST"; break;
			case FlightModel::DOCK:	flightStr = "DOCK"; break;
		}

		StringBuffer msg;
		msg << "ShipObjectTransform: "
			<< "  deltaTime:         " << deltaTime << endl
			<< "  currentTransform:  " << endl << currentTransform.toDebugString() << endl
			<< "  nextTransform:     " << endl << nextTransform.toDebugString() << endl
			<< "  nextDistance:      " << nextDistance << endl
			<< "  flightModel:       " << flightStr << endl;

		return msg.toString();

	}
};

#endif // SHIPOBJECTTRANSFORM_H_
