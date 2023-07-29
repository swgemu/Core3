/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef SPACEPATROLPOINT_H_
#define SPACEPATROLPOINT_H_

#include "system/lang.h"

#include "engine/util/json_utils.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/WorldCoordinates.h"

class SpacePatrolPoint : public Serializable {
	WorldCoordinates position;

	bool reached;
	bool evadePoint;

	SerializableTime estimatedTimeOfArrival;

	Quaternion direction;

public:
	SpacePatrolPoint() {
		reached = true;
		evadePoint = false;

		addSerializableVariables();
	}

	SpacePatrolPoint(const Vector3& pos) : position(pos, nullptr) {
		reached = false;
		evadePoint = false;

		addSerializableVariables();
	}

	SpacePatrolPoint(const SpacePatrolPoint& point) : Object(), Serializable() {
		position = point.position;
		direction = point.direction;
		reached = point.reached;
		evadePoint = point.evadePoint;

		addSerializableVariables();
	}

#ifdef CXX11_COMPILER
	SpacePatrolPoint(SpacePatrolPoint&& point) : Object(), Serializable(), position(std::move(point.position)), reached(point.reached), evadePoint(point.evadePoint), estimatedTimeOfArrival(point.estimatedTimeOfArrival) {
		addSerializableVariables();
	}
#endif

	SpacePatrolPoint& operator=(const SpacePatrolPoint& p) {
		if (this == &p)
			return *this;

		position = p.position;
		reached = p.reached;
		evadePoint = p.evadePoint;
		direction = p.direction;
		estimatedTimeOfArrival = p.estimatedTimeOfArrival;

		return *this;
	}

#ifdef CXX11_COMPILER
	SpacePatrolPoint& operator=(SpacePatrolPoint&& p) {
		if (this == &p)
			return *this;

		position = std::move(p.position);
		reached = p.reached;
		evadePoint = p.evadePoint;
		direction = p.direction;
		estimatedTimeOfArrival = p.estimatedTimeOfArrival;

		return *this;
	}
#endif

	inline void addSerializableVariables() {
		addSerializableVariable("position", &position);
		addSerializableVariable("reached", &reached);
		addSerializableVariable("evadePoint", &evadePoint);
		addSerializableVariable("direction", &direction);
		addSerializableVariable("estimatedTimeOfArrival", &estimatedTimeOfArrival);
	}

	friend void to_json(nlohmann::json& j, const SpacePatrolPoint& p) {
		j["position"] = p.position;
		j["reached"] = p.reached;
		j["evadePoint"] = p.evadePoint;
		j["direction"] = p.direction;
		j["estimatedTimeOfArrival"] = p.estimatedTimeOfArrival;
	}

	Vector3 getWorldPosition() {
		return position.getWorldPosition();
	}

	virtual bool isInRange(SceneObject* obj, float range) {
		Vector3 thisWorldPos = getWorldPosition();
		Vector3 objWorldPos = obj->getWorldPosition();

		return thisWorldPos.squaredDistanceTo(objWorldPos) <= (range * range);
	}

	bool isInRange(SpacePatrolPoint* obj, float range) {
		Vector3 thisWorldPos = getWorldPosition();
		Vector3 objWorldPos = obj->getWorldPosition();

		return thisWorldPos.squaredDistanceTo(objWorldPos) <= (range * range);
	}

	inline const WorldCoordinates& getCoordinates() const {
		return position;
	}

	//getters
	inline float getPositionX() const {
		return position.getX();
	}

	inline float getPositionY() const {
		return position.getY();
	}

	inline float getPositionZ() const {
		return position.getZ();
	}

	inline Quaternion getDirection() const {
		return direction;
	}

	inline Time* getEstimatedTimeOfArrival() {
		return &estimatedTimeOfArrival;
	}

	inline bool isReached() const {
		return reached;
	}

	inline bool isEvadePoint() const {
		return evadePoint;
	}

	inline bool isPastTimeOfArrival() {
		return estimatedTimeOfArrival.isPast() || estimatedTimeOfArrival.isPresent();
	}

	//setters
	inline void setPosition(float x, float z, float y) {
		position.setCoordinates(Vector3(x, y, z));
	}

	inline void setPositionX(float x) {
		position.setX(x);
	}

	inline void setPositionZ(float z) {
		position.setZ(z);
	}

	inline void setPositionY(float y) {
		position.setY(y);
	}

	inline void setCell(CellObject* cell) {
		position.setCell(cell);
	}

	inline void setDirection(float fw, float fx, float fy, float fz) {
		direction.set(fw, fx, fy, fz);
	}

	inline void setReached(bool value) {
		reached = value;
	}

	inline void setEvadePoint(bool value) {
		evadePoint = value;
	}

	inline void addEstimatedTimeOfArrival(uint32 mili) {
		estimatedTimeOfArrival.updateToCurrentTime();
		estimatedTimeOfArrival.addMiliTime(mili);
	}

	/**
	 * Returns the string representation of the vector in (x, y, z) format plus the cellID.
	 */
	inline String toString() const {
		StringBuffer msg;
		msg << position.toString() << " isReached: " << (reached ? "true" : "false") << " isEvadePoint: " << (evadePoint ? "true" : "false");
		return msg.toString();
	}
};

#endif /*SPACEPATROLPOINT_H_*/
