/*
 * ChildObject.h
 *
 *  Created on: 28/07/2010
 *      Author: victor
 */

#ifndef CHILDOBJECT_H_
#define CHILDOBJECT_H_

#include "engine/engine.h"

class ChildObject : public Object {
	Vector3 position;
	Quaternion direction;
	String templateFile;
	int cellid;
	int containmentType;

public:
	ChildObject() {
		cellid = 0;
		containmentType = 0;
	}

	ChildObject(const ChildObject& obj) : Object() {
		position = obj.position;
		direction = obj.direction;
		templateFile = obj.templateFile;
		cellid = obj.cellid;
		containmentType = obj.containmentType;
	}

	ChildObject& operator=(const ChildObject& obj) {
		if (this == &obj)
			return *this;

		position = obj.position;
		direction = obj.direction;
		templateFile = obj.templateFile;
		cellid = obj.cellid;
		containmentType = obj.containmentType;

		return *this;
	}

	void parseFromLua(LuaObject* luaObject) {
		templateFile = luaObject->getStringField("templateFile");
		position.setX(luaObject->getFloatField("x"));
		position.setZ(luaObject->getFloatField("z"));
		position.setY(luaObject->getFloatField("y"));

		direction.set(luaObject->getFloatField("ow"), luaObject->getFloatField("ox"), luaObject->getFloatField("oy"), luaObject->getFloatField("oz"));

		cellid = luaObject->getIntField("cellid");

		containmentType = luaObject->getIntField("containmentType");
	}

	inline void setPosition(float x, float z, float y) {
		position.set(x, z, y);
	}

	inline void setDirection(float fw, float fx, float fy, float fz) {
		direction.set(fw, fx, fy, fz);
	}

	inline void setCellId(int id) {
		cellid = id;
	}

	inline void setContainmentType(int containment) {
		containmentType = containment;
	}

	inline void setTemplateFile(const String& file) {
		templateFile = file;
	}

	inline Vector3& getPosition() {
		return position;
	}

	inline Quaternion& getDirection() {
		return direction;
	}

	inline String& getTemplateFile() {
		return templateFile;
	}

	inline int getCellId() {
		return cellid;
	}

	inline int getContainmentType() {
		return containmentType;
	}
};

#endif /* CHILDOBJECT_H_ */
