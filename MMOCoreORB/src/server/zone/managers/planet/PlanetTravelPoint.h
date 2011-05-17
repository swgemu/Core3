/*
 * PlanetTravelPoint.h
 *
 *  Created on: May 13, 2011
 *      Author: crush
 */

#ifndef PLANETTRAVELPOINT_H_
#define PLANETTRAVELPOINT_H_

#include "engine/engine.h"

class PlanetTravelPoint : public Object {
	String pointName;
	float x;
	float z;
	float y;
	bool interplanetaryTravelAllowed;

public:
	PlanetTravelPoint() {
		x = 0.f;
		z = 0.f;
		y = 0.f;
		interplanetaryTravelAllowed = false;
	}

	PlanetTravelPoint(const PlanetTravelPoint& ptp) : Object() {
		pointName = ptp.pointName;
		x = ptp.x;
		z = ptp.z;
		y = ptp.y;
		interplanetaryTravelAllowed = ptp.interplanetaryTravelAllowed;
	}

	PlanetTravelPoint& operator= (const PlanetTravelPoint& ptp) {
		if (this == &ptp)
			return *this;

		pointName = ptp.pointName;
		x = ptp.x;
		z = ptp.z;
		y = ptp.y;
		interplanetaryTravelAllowed = ptp.interplanetaryTravelAllowed;

		return *this;
	}

	int compareTo(const PlanetTravelPoint& ptp) const {
		return pointName.compareTo(ptp.pointName);
	}

	int compareTo(const String& name) const {
		return pointName.compareTo(name);
	}

	void readLuaObject(LuaObject* luaObject) {
		pointName = luaObject->getStringField("name");
		x = luaObject->getFloatField("x");
		z = luaObject->getFloatField("z");
		y = luaObject->getFloatField("y");
		interplanetaryTravelAllowed = (bool) luaObject->getByteField("interplanetaryTravelAllowed");
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
};

#endif /* PLANETTRAVELPOINT_H_ */
