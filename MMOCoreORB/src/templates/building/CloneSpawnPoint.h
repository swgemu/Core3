/*
 * CloneSpawnPoint.h
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#ifndef CLONESPAWNPOINT_H_
#define CLONESPAWNPOINT_H_

#include "engine/util/u3d/Coordinate.h"
#include "engine/util/u3d/Quaternion.h"

class CloneSpawnPoint : public Object {
	Coordinate coordinate;
	Quaternion direction;
	int cellid;
public:
	CloneSpawnPoint() : cellid(0) {
	}

	CloneSpawnPoint(const CloneSpawnPoint& p) : Object() {
		coordinate.setPositionX(p.getPositionX());
		coordinate.setPositionZ(p.getPositionZ());
		coordinate.setPositionY(p.getPositionY());

		direction.set(p.direction.getW(), p.direction.getZ(), p.direction.getY(), p.direction.getZ());
		cellid = p.cellid;
	}

	void parseFromLua(LuaObject* luaObject) {
		coordinate.setPositionX(luaObject->getFloatField("x"));
		coordinate.setPositionZ(luaObject->getFloatField("z"));
		coordinate.setPositionY(luaObject->getFloatField("y"));

		direction.set(luaObject->getFloatField("ow"), luaObject->getFloatField("ox"), luaObject->getFloatField("oy"), luaObject->getFloatField("oz"));

		cellid = luaObject->getIntField("cellid");
	}

	float getPositionX() const {
		return coordinate.getPositionX();
	}

	float getPositionY() const {
		return coordinate.getPositionY();
	}

	float getPositionZ() const {
		return coordinate.getPositionZ();
	}

	inline Coordinate* getCoordinate() {
		return &coordinate;
	}

	inline Quaternion* getDirection() {
		return &direction;
	}

	inline int getCellID() {
		return cellid;
	}
};

#endif /* CLONESPAWNPOINT_H_ */
