/*
 * SpaceLaunchPoint.h
 *
 *	Created on: Jan. 22, 2023
 *	Author: H
 */

#ifndef SPACELAUNCHPOINT_H_
#define SPACELAUNCHPOINT_H_

#include "engine/util/json_utils.h"

class SpaceLaunchPoint : public Object {
	String groundZoneName;
	String cityName;
	Vector3 location;

public:
	SpaceLaunchPoint() : Object() {
		groundZoneName = "";
		cityName = "";
	}

	SpaceLaunchPoint(const SpaceLaunchPoint& point) : Object() {
		initialize(point);
	}

	SpaceLaunchPoint& operator=(const SpaceLaunchPoint& point) {
		if (this == &point)
			return *this;

		initialize(point);

		return *this;
	}

	friend void to_json(nlohmann::json& j, const SpaceLaunchPoint& l) {
		j["groundZoneName"] = l.groundZoneName;
		j["cityName"] = l.cityName;
		j["location"] = l.location;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		groundZoneName.toBinaryStream(stream);
		cityName.toBinaryStream(stream);
		location.toBinaryStream(stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		groundZoneName.parseFromBinaryStream(stream);
		cityName.parseFromBinaryStream(stream);
		location.parseFromBinaryStream(stream);

		return true;
	}

	void initialize(const SpaceLaunchPoint& point) {
		groundZoneName = point.groundZoneName;
		cityName = point.cityName;
		location = point.location;
	}

	inline void setGroundZoneName(String zoneName) {
		groundZoneName = zoneName;
	}

	inline void setCityName(String name) {
		cityName = name;
	}

	inline void setLocation(float x, float z, float y) {
		location.setX(x);
		location.setZ(z);
		location.setY(y);
	}

	inline void setLocation(Vector3 loc) {
		location = loc;
	}

	inline String getGoundZoneName() {
		return groundZoneName;
	}

	inline String getCityName() {
		return cityName;
	}

	inline Vector3 getLocation() {
		return location;
	}
};

#endif /* SPACELAUNCHPOINT_H_ */
