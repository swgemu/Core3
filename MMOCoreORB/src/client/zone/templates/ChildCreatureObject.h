/*
 * ChildCreatureObject.h
 *
 *  Created on: Jan 7, 2013
 *      Author: root
 */

#ifndef CHILDCREATUREOBJECT_H_
#define CHILDCREATUREOBJECT_H_

#include "engine/engine.h"

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

	inline Vector3& getPosition() {
		return position;
	}

	inline int getCellId() {
		return cellid;
	}

	inline int getContainmentType() {
		return containmentType;
	}

	inline String getMobile(){
		return mobileName;
	}

	inline float getHeading(){
		return heading;
	}

	inline int getRespawnTimer(){
		return respawnTime;
	}
};

#endif /* CHILDCREATUREOBJECT_H_ */
