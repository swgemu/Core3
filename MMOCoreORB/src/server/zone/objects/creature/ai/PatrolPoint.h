/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PATROLPOINT_H_
#define PATROLPOINT_H_

#include "system/lang.h"

#include "engine/util/json_utils.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/scene/WorldCoordinates.h"

class PatrolPoint : public Serializable {
	WorldCoordinates position;

	bool reached;

	SerializableTime estimatedTimeOfArrival;

	float direction;

public:
	PatrolPoint() {
		reached = true;

		addSerializableVariables();
	}

	PatrolPoint(const Vector3& pos, CellObject* cell = nullptr) : position(pos, cell) {
		reached = false;

		addSerializableVariables();
	}

	PatrolPoint(float posX, float posZ, float posY, CellObject* cell = nullptr) : position(Vector3(posX, posY, posZ), cell) {
		reached = false;

		addSerializableVariables();
	}

	PatrolPoint(const PatrolPoint& point) : Object(), Serializable() {
		position = point.position;

		reached = point.reached;

		addSerializableVariables();
	}

#ifdef CXX11_COMPILER
	PatrolPoint(PatrolPoint&& point) : Object(), Serializable(),
			position(std::move(point.position)), reached(point.reached), estimatedTimeOfArrival(point.estimatedTimeOfArrival) {

		addSerializableVariables();
	}
#endif

	PatrolPoint& operator=(const PatrolPoint& p) {
		if (this == &p)
			return *this;

		position = p.position;

		reached = p.reached;

		direction = p.direction;

		estimatedTimeOfArrival = p.estimatedTimeOfArrival;

		return *this;
	}

#ifdef CXX11_COMPILER
	PatrolPoint& operator=(PatrolPoint&& p) {
		if (this == &p)
			return *this;

		position = std::move(p.position);

		reached = p.reached;

		direction = p.direction;

		estimatedTimeOfArrival = p.estimatedTimeOfArrival;

		return *this;
	}
#endif

	inline void addSerializableVariables() {
		addSerializableVariable("position", &position);
		addSerializableVariable("reached", &reached);
		addSerializableVariable("direction", &direction);
		addSerializableVariable("estimatedTimeOfArrival", &estimatedTimeOfArrival);
	}

	friend void to_json(nlohmann::json& j, const PatrolPoint& p) {
		j["position"] = p.position;
		j["reached"] = p.reached;
		j["direction"] = p.direction;
		j["estimatedTimeOfArrival"] = p.estimatedTimeOfArrival;
	}

	Vector3 getWorldPosition() {
		return position.getWorldPosition();
	}

	virtual bool isInRange(SceneObject* obj, float range) {
		Vector3 thisWorldPos = getWorldPosition();
		Vector3 objWorldPos = obj->getWorldPosition();

		return thisWorldPos.squaredDistanceTo(objWorldPos) < (range * range);
	}

	bool isInRange(PatrolPoint* obj, float range) {
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

	inline CellObject* getCell() const {
		return position.getCell();
	}

	inline float getDirection() const {
		return direction;
	}

	inline Time* getEstimatedTimeOfArrival() {
		return &estimatedTimeOfArrival;
	}

	inline bool isReached() const {
		return reached;
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

	inline void setDirection(float dir) {
		direction = dir;
	}

	inline void setReached(bool value) {
		reached = value;
	}

	inline void addEstimatedTimeOfArrival(uint32 mili) {
		estimatedTimeOfArrival.updateToCurrentTime();
		estimatedTimeOfArrival.addMiliTime(mili);
	}

	/**
	 * Returns the string representation of the vector in (x, y, z) format plus the cellID.
	 */
	inline String toString() const {
		return position.toString();
	}
};

#endif /*PATROLPOINT_H_*/
