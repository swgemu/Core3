/*
 * PlanetTravelPoint.h
 *
 *  Created on: May 13, 2011
 *      Author: crush
 *  Updated on: Sat Oct 15 10:40:05 PDT 2011 by lordkator - Converted to Vector3, arrival/departure and a number of fixes to make travel more stable
 */

#ifndef PLANETTRAVELPOINT_H_
#define PLANETTRAVELPOINT_H_

#include "engine/engine.h"
#include "engine/util/u3d/Coordinate.h"
#include "server/zone/objects/creature/CreatureObject.h"

using namespace server::zone::objects::creature;

class PlanetTravelPoint : public Object {
	ManagedWeakReference<CreatureObject*> shuttleObject;

	String pointZone;
	String pointName;
	Vector3 arrivalVector;
	Vector3 departureVector;
	bool interplanetaryTravelAllowed;

public:
	PlanetTravelPoint(const String& zoneName) {
		pointZone = zoneName;
		arrivalVector.set(0.f, 0.f, 0.f);
		interplanetaryTravelAllowed = false;
		shuttleObject = NULL;
	}

	PlanetTravelPoint(const String& zoneName, const String& cityName, Vector3 arrVector, Vector3 departVector, CreatureObject* shuttle) {
			pointZone = zoneName;
			pointName = cityName;
			arrivalVector = arrVector;
			departureVector = departVector;
			interplanetaryTravelAllowed = false;
			shuttleObject = shuttle;
	}

	PlanetTravelPoint(const PlanetTravelPoint& ptp) : Object() {
		pointZone = ptp.pointZone;
		pointName = ptp.pointName;
		arrivalVector = ptp.arrivalVector;
		departureVector = ptp.departureVector;
		interplanetaryTravelAllowed = ptp.interplanetaryTravelAllowed;
		shuttleObject = ptp.shuttleObject;
	}

	PlanetTravelPoint& operator= (const PlanetTravelPoint& ptp) {
		if (this == &ptp)
			return *this;

		pointZone = ptp.pointZone;
		pointName = ptp.pointName;
		arrivalVector = ptp.arrivalVector;
		departureVector = ptp.departureVector;
		interplanetaryTravelAllowed = ptp.interplanetaryTravelAllowed;
		shuttleObject = ptp.shuttleObject;

		return *this;
	}

	void readLuaObject(LuaObject* luaObject) {
		pointName = luaObject->getStringField("name");
		arrivalVector.set(
				luaObject->getFloatField("x"),
				luaObject->getFloatField("z"),
				luaObject->getFloatField("y")
		);
		departureVector = arrivalVector;

		interplanetaryTravelAllowed = (bool) luaObject->getByteField("interplanetaryTravelAllowed");
	}

	// Called by the shuttles and transports to set the shuttle object for the nearest travel point
	void setShuttle(CreatureObject* shuttle) {
		shuttleObject = shuttle;

		// Departure point is the shuttle's position itself
		departureVector = shuttle->getWorldPosition();
	}

	inline String& getPointZone() {
		return pointZone;
	}

	inline String& getPointName() {
		return pointName;
	}

	inline float getArrivalPositionX() const {
		return arrivalVector.getX();
	}

	inline float getArrivalPositionY() const {
		return arrivalVector.getY();
	}

	inline float getArrivalPositionZ() const {
		return arrivalVector.getZ();
	}

	inline Vector3 getArrivalPosition() const {
		return arrivalVector;
	}

	inline float getDeparturePositionX() const {
		return departureVector.getX();
	}

	inline float getDeparturePositionY() const {
		return departureVector.getY();
	}

	inline float getDeparturePositionZ() const {
		return departureVector.getZ();
	}

	inline Vector3 getDeparturePosition() const {
		return departureVector;
	}

	/**
	 * Returns true if this point is has the same zone and name that is passed in.
	 */
	inline bool isPoint(const String& zoneName, const String& name) {
		return (zoneName == pointZone && name == pointName);
	}

	/**
	 * Returns true if this location allows interplanetary travel
	 */
	inline bool isInterplanetary() {
		return interplanetaryTravelAllowed;
	}

	/**
	 * Returns true if travel between this point and the passed in point is permitted.
	 * @param arrivalPoint The destination point.
	 */
	bool canTravelTo(PlanetTravelPoint* arrivalPoint) {
		if (arrivalPoint->getPointZone() == pointZone)
			return true;

		return (interplanetaryTravelAllowed);
	}

	ManagedReference<CreatureObject*> getShuttle() {
		return shuttleObject.get();
	}

	String toString() {
		StringBuffer buf;

		buf << "[PlanetTravelPoint 0x" + String::hexvalueOf((int64)this)
			<< " Zone = '" << pointZone
			<< "' Name = '" << pointName
			<< "' StarPort = " << interplanetaryTravelAllowed
			<< " Departure: " << departureVector.toString()
			<< " Arrival: " << arrivalVector.toString()
			<< " shuttle = ";

		if(shuttleObject == NULL) {
			buf << "NULL";
		} else {
			buf << "[oid:" << shuttleObject.get()->getObjectID()
				<< " " << shuttleObject.get()->getObjectNameStringIdName()
				<< " @ " << shuttleObject.get()->getWorldPosition().toString()
				<< "]";
		}

		buf << "]";

		return buf.toString();
	}
};

#endif /* PLANETTRAVELPOINT_H_ */
