#ifndef CITYCONTROLLANDINGPOINT_H_
#define CITYCONTROLLANDINGPOINT_H_

#include <atomic>

#include "server/zone/objects/creature/CreatureObject.h"

using namespace server::zone::objects::creature;

class CityControlLandingPoint : public Object {
	ManagedWeakReference<CreatureObject*> shuttleObject;

	String pointZone;
	String pointName;
	Vector3 landingVector;

public:
	CityControlLandingPoint(const String& zoneName) {
		pointZone = zoneName;
		landingVector.set(0.f, 0.f, 0.f);
		shuttleObject = nullptr;
	}

	CityControlLandingPoint(const String& zoneName, const String& cityName, Vector3 lVector, CreatureObject* shuttle) {
		pointZone = zoneName;
		pointName = cityName;
		landingVector = lVector;
		shuttleObject = shuttle;
	}

	CityControlLandingPoint(const CityControlLandingPoint& cclp) : Object() {
		pointZone = cclp.pointZone;
		pointName = cclp.pointName;
		landingVector = cclp.landingVector;
		shuttleObject = cclp.shuttleObject;
	}

	CityControlLandingPoint& operator= (const CityControlLandingPoint& cclp) {
		if (this == &cclp)
			return *this;

		pointZone = cclp.pointZone;
		pointName = cclp.pointName;
		landingVector = cclp.landingVector;
		shuttleObject = cclp.shuttleObject;

		return *this;
	}

	void readLuaObject(LuaObject* luaObject) {
		pointName = luaObject->getStringField("name");
		landingVector.set(
				luaObject->getFloatField("x"),
				luaObject->getFloatField("z"),
				luaObject->getFloatField("y")
		);
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

	inline float getLandingPositionX() const {
		return landingVector.getX();
	}

	inline float getLandingPositionY() const {
		return landingVector.getY();
	}

	inline float getLandingPositionZ() const {
		return landingVector.getZ();
	}

	inline Vector3 getLandingPosition() const {
		return landingVector;
	}

	inline bool isPoint(const String& zoneName, const String& name) const {
		return (zoneName == pointZone && name == pointName);
	}

	ManagedReference<CreatureObject*> getShuttle() {
		return shuttleObject.get();
	}

};

#endif /* CITYCONTROLLANDINGPOINT_H_ */