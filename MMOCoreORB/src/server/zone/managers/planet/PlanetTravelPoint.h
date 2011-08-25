/*
 * PlanetTravelPoint.h
 *
 *  Created on: May 13, 2011
 *      Author: crush
 */

#ifndef PLANETTRAVELPOINT_H_
#define PLANETTRAVELPOINT_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;

class PlanetTravelPoint : public Object {
	ManagedWeakReference<CreatureObject*> shuttleObject;

	String pointZone;
	String pointName;
	float x;
	float z;
	float y;
	bool interplanetaryTravelAllowed;

public:
	PlanetTravelPoint(const String& zoneName) {
		pointZone = zoneName;
		x = 0.f;
		z = 0.f;
		y = 0.f;
		interplanetaryTravelAllowed = false;

		shuttleObject = NULL;
	}

	PlanetTravelPoint(const PlanetTravelPoint& ptp) : Object() {
		pointZone = ptp.pointZone;
		pointName = ptp.pointName;
		x = ptp.x;
		z = ptp.z;
		y = ptp.y;
		interplanetaryTravelAllowed = ptp.interplanetaryTravelAllowed;

		shuttleObject = ptp.shuttleObject;
	}

	PlanetTravelPoint& operator= (const PlanetTravelPoint& ptp) {
		if (this == &ptp)
			return *this;

		pointZone = ptp.pointZone;
		pointName = ptp.pointName;
		x = ptp.x;
		z = ptp.z;
		y = ptp.y;
		interplanetaryTravelAllowed = ptp.interplanetaryTravelAllowed;
		shuttleObject = ptp.shuttleObject;

		return *this;
	}

	void readLuaObject(LuaObject* luaObject) {
		pointName = luaObject->getStringField("name");
		x = luaObject->getFloatField("x");
		z = luaObject->getFloatField("z");
		y = luaObject->getFloatField("y");
		interplanetaryTravelAllowed = (bool) luaObject->getByteField("interplanetaryTravelAllowed");
	}

	inline String& getPointZone() {
		return pointZone;
	}

	inline String& getPointName() {
		return pointName;
	}

	inline float getX() const {
		return x;
	}

	inline float getY() const {
		return y;
	}

	inline float getZ() const {
		return z;
	}

	inline bool isInterplanetary() {
		return interplanetaryTravelAllowed;
	}

	/**
	 * Returns true if this point is has the same zone and name that is passed in.
	 */
	inline bool isPoint(const String& zoneName, const String& name) {
		return (zoneName == pointZone && name == pointName);
	}

	/**
	 * Returns true if travel between this point and the passed in point is permitted.
	 * @param arrivalPoint The destination point.
	 */
	bool canTravelTo(PlanetTravelPoint* arrivalPoint) {
		if (arrivalPoint->getPointZone() == pointZone)
			return true;

		return (interplanetaryTravelAllowed && arrivalPoint->isInterplanetary());
	}

	void setShuttle(CreatureObject* shuttle) {
		shuttleObject = shuttle;
	}

	CreatureObject* getShuttle() {
		return shuttleObject;
	}
};

#endif /* PLANETTRAVELPOINT_H_ */
