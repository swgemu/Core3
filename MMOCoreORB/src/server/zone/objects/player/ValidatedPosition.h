/*
 * ValidatedPosition.h
 *
 *  Created on: 27/11/2010
 *      Author: victor
 */

#ifndef VALIDATEDPOSITION_H_
#define VALIDATEDPOSITION_H_

#include "engine/engine.h"

#include "engine/util/json_utils.h"

namespace server {
 namespace zone {
  class ZoneServer;

  namespace objects {
   namespace scene {
    class SceneObject;
   }
  }
 }
}

class ValidatedPosition : public Serializable {
	SerializableVector3 point;
	uint64 parent;
public:
	ValidatedPosition() {
		parent = 0;

		addSerVariables();
	}

	ValidatedPosition(const Vector3& pos) {
		parent = 0;
		point = pos;

		addSerVariables();
	}

	ValidatedPosition(const ValidatedPosition& a) : Object(), Serializable() {
		point = a.point;
		parent = a.parent;

		addSerVariables();
	}

	ValidatedPosition& operator=(const ValidatedPosition& a) {
		point = a.point;
		parent = a.parent;

		return *this;
	}

	friend void to_json(nlohmann::json& j, const ValidatedPosition& pos) {
		j["point"] = pos.point;
		j["parent"] = pos.parent;
	}

	Vector3 getWorldPosition(server::zone::ZoneServer* zoneServer);

	void update(server::zone::objects::scene::SceneObject* object);

	inline uint64 getParent() const {
		return parent;
	}

	inline const Vector3& getPosition() const {
		return point;
	}

	inline void setParent(uint64 par) {
		parent = par;
	}

	inline void setPosition(const Vector3& pos) {
		point = pos;
	}

	inline void setPosition(float x, float z, float y) {
		point.set(x, z, y);
	}

private:
	inline void addSerVariables() {
		addSerializableVariable("point", &point);
		addSerializableVariable("parent", &parent);
	}

};

#endif /* VALIDATEDPOSITION_H_ */
