/*
 * PlanetTravelPoint.h
 *
 *  Created on: May 13, 2011
 *      Author: crush
 *  Updated on: Sat Oct 15 10:40:05 PDT 2011 by lordkator - Converted to Vector3, arrival/departure and a number of fixes to make travel more stable
 */

#ifndef PLANETTRAVELPOINT_H_
#define PLANETTRAVELPOINT_H_

#include <atomic>

#include "server/zone/objects/creature/CreatureObject.h"

using namespace server::zone::objects::creature;

class PlanetTravelPoint : public Object {
	ManagedWeakReference<CreatureObject*> shuttleObject;

	String pointZone;
	String pointName;
	Vector3 arrivalVector;
	std::atomic<Vector3> departureVector{};
	bool interplanetaryTravelAllowed;
	bool incomingTravelAllowed;

public:
	PlanetTravelPoint(const String& zoneName) {
		pointZone = zoneName;
		arrivalVector.set(0.f, 0.f, 0.f);
		interplanetaryTravelAllowed = false;
		incomingTravelAllowed = true;
		shuttleObject = nullptr;
	}

	PlanetTravelPoint(const String& zoneName, const String& cityName, Vector3 arrVector, Vector3 departVector, CreatureObject* shuttle) {
		pointZone = zoneName;
		pointName = cityName;
		arrivalVector = arrVector;
		departureVector = departVector;
		interplanetaryTravelAllowed = false;
		incomingTravelAllowed = true;
		shuttleObject = shuttle;
	}

	PlanetTravelPoint(const PlanetTravelPoint& ptp) : Object() {
		pointZone = ptp.pointZone;
		pointName = ptp.pointName;
		arrivalVector = ptp.arrivalVector;
		departureVector = ptp.departureVector.load();
		interplanetaryTravelAllowed = ptp.interplanetaryTravelAllowed;
		incomingTravelAllowed = ptp.incomingTravelAllowed;
		shuttleObject = ptp.shuttleObject;
	}

	PlanetTravelPoint& operator= (const PlanetTravelPoint& ptp) {
		if (this == &ptp)
			return *this;

		pointZone = ptp.pointZone;
		pointName = ptp.pointName;
		arrivalVector = ptp.arrivalVector;
		departureVector = ptp.departureVector.load();
		interplanetaryTravelAllowed = ptp.interplanetaryTravelAllowed;
		incomingTravelAllowed = ptp.incomingTravelAllowed;
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
		incomingTravelAllowed = (bool) luaObject->getByteField("incomingTravelAllowed");
	}

	// Called by the shuttles and transports to set the shuttle object for the nearest travel point
	void setShuttle(CreatureObject* shuttle) {
		shuttleObject = shuttle;

		// Departure point is the shuttle's position itself
		departureVector = shuttle->getWorldPosition();
	}

	void setPointName(const String& name){
		pointName = name;
	}

	inline const String& getPointZone() const {
		return pointZone;
	}

	inline const String& getPointName() const {
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
		return departureVector.load().getX();
	}

	inline float getDeparturePositionY() const {
		return departureVector.load().getY();
	}

	inline float getDeparturePositionZ() const {
		return departureVector.load().getZ();
	}

	inline Vector3 getDeparturePosition() const {
		return departureVector.load(std::memory_order_relaxed);
	}

	/**
	 * Returns true if this point is has the same zone and name that is passed in.
	 */
	inline bool isPoint(const String& zoneName, const String& name) const {
		return (zoneName == pointZone && name == pointName);
	}

	/**
	 * Returns true if this location allows interplanetary travel
	 */
	inline bool isInterplanetary() const {
		return interplanetaryTravelAllowed;
	}

	/**
	 * Returns true if this location allows incoming travel
	 */
	inline bool isIncomingAllowed() const {
		return incomingTravelAllowed;
	}

	/**
	 * Returns true if travel between this point and the passed in point is permitted.
	 * @param arrivalPoint The destination point.
	 */
	bool canTravelTo(const PlanetTravelPoint* arrivalPoint) const {
		if (arrivalPoint->getPointZone() == pointZone && arrivalPoint->isIncomingAllowed())
			return true;

		return (interplanetaryTravelAllowed && arrivalPoint->isIncomingAllowed());
	}

	ManagedReference<CreatureObject*> getShuttle() {
		return shuttleObject.get();
	}

	String toString() const {
		StringBuffer buf;

		buf << "[PlanetTravelPoint 0x" + String::hexvalueOf((int64)this)
			<< " Zone = '" << pointZone
			<< "' Name = '" << pointName
			<< "' StarPort = " << interplanetaryTravelAllowed
			<< " Departure: " << departureVector.load().toString()
			<< " Arrival: " << arrivalVector.toString()
			<< " shuttle = ";

			buf << "[oid:" << shuttleObject.getSavedObjectID() << "]";

		buf << "]";

		return buf.toString();
	}
};

#endif /* PLANETTRAVELPOINT_H_ */
