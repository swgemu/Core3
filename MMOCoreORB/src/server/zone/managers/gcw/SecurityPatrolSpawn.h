#ifndef SECURITYPATROLSPAWN_H_
#define SECURITYPATROLSPAWN_H_

#include "system/lang/Object.h"
#include "engine/util/u3d/Vector3.h"

class SecurityPatrolSpawn : public Object {
protected:
	String patrol;
	int faction;
	Vector3 location;
	float direction;

public:
	SecurityPatrolSpawn() {
		patrol = "";
		faction = 0;
		direction = 0.f;
	}

	SecurityPatrolSpawn(const SecurityPatrolSpawn& obj) : Object() {
		patrol = obj.patrol;
		faction = obj.faction;
		location = obj.location;
		direction = obj.direction;
	}

	SecurityPatrolSpawn& operator=(const SecurityPatrolSpawn& obj) {
		if (this == &obj)
			return *this;

		patrol = obj.patrol;
		faction = obj.faction;
		location = obj.location;
		direction = obj.direction;

		return *this;
	}

	void parseFromLua(LuaObject* luaObject) {
		patrol = luaObject->getStringField("patrol");

		location.setX(luaObject->getFloatField("x"));
		location.setZ(luaObject->getFloatField("z"));
		location.setY(luaObject->getFloatField("y"));

		direction = luaObject->getFloatField("heading");
	}

	inline void setlocation(float x, float z, float y) {
		location.set(x, z, y);
	}

	inline void setPatrol(String pat) {
		patrol = pat;
	}

	inline const Vector3& getLocation() const {
		return location;
	}

	inline float getDirection() const {
		return direction;
	}

	inline String getPatrol() const {
		return patrol;
	}

	inline int getFaction() const {
		return faction;
	}
};

#endif /* SECURITYPATROLSPAWN_H_ */