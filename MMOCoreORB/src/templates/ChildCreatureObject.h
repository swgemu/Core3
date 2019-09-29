/*
 * ChildCreatureObject.h
 *
 *  Created on: Jan 7, 2013
 *      Author: root
 */

#ifndef CHILDCREATUREOBJECT_H_
#define CHILDCREATUREOBJECT_H_

#include "system/lang/Object.h"
#include "engine/util/u3d/Vector3.h"
#include "engine/lua/LuaObject.h"

class ChildCreatureObject : public Object {
	Vector3 position;

	int cellid;
	int containmentType;
	String mobileName;
	int respawnTime;
	float heading;

public:
	ChildCreatureObject() {
		cellid = 0;
		containmentType = 0;
		respawnTime = 0;
		heading = 0;
	}

	ChildCreatureObject(const ChildCreatureObject& obj) : Object() {
		position = obj.position;
		cellid = obj.cellid;
		containmentType = obj.containmentType;
		mobileName = obj.mobileName;
		respawnTime = obj.respawnTime;
		heading = obj.heading;
	}

	ChildCreatureObject& operator=(const ChildCreatureObject& obj) {
		if (this == &obj)
			return *this;

		position = obj.position;
		cellid = obj.cellid;
		containmentType = obj.containmentType;
		mobileName = obj.mobileName;
		respawnTime = obj.respawnTime;
		heading = obj.heading;

		return *this;
	}

	void parseFromLua(LuaObject* luaObject) {
		position.setX(luaObject->getFloatField("x"));
		position.setZ(luaObject->getFloatField("z"));
		position.setY(luaObject->getFloatField("y"));
		cellid = luaObject->getIntField("cellid");
		containmentType = luaObject->getIntField("containmentType");
		mobileName = luaObject->getStringField("mobile");
		respawnTime = luaObject->getIntField("respawn");
		heading = luaObject->getFloatField("heading");

	}

	inline void setPosition(float x, float z, float y) {
		position.set(x, z, y);
	}

	inline void setCellId(int id) {
		cellid = id;
	}

	inline void setContainmentType(int containment) {
		containmentType = containment;
	}

	inline void setMobileName(String name) {
		mobileName = name;
	}

	inline void setRespawnTime(int respawn) {
		respawnTime = respawn;
	}

	inline void setHeading(float head) {
		heading = head;
	}

	inline const Vector3& getPosition() const {
		return position;
	}

	inline int getCellId() const {
		return cellid;
	}

	inline int getContainmentType() const {
		return containmentType;
	}

	inline const String& getMobile() const {
		return mobileName;
	}

	inline float getHeading() const {
		return heading;
	}

	inline int getRespawnTimer() const {
		return respawnTime;
	}
};

#endif /* CHILDCREATUREOBJECT_H_ */
