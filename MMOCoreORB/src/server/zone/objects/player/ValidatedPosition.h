/*
 * ValidatedPosition.h
 *
 *  Created on: 27/11/2010
 *      Author: victor
 */

#ifndef VALIDATEDPOSITION_H_
#define VALIDATEDPOSITION_H_

#include "engine/engine.h"

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
	Vector3 point;
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

	Vector3 getWorldPosition(server::zone::ZoneServer* zoneServer);

	void update(server::zone::objects::scene::SceneObject* object);

	inline uint64 getParent() {
		return parent;
	}

	inline Vector3 getPosition() {
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

	inline void addSerVariables() {
		addSerializableVariable("point", &point);
		addSerializableVariable("parent", &parent);
	}

};

#endif /* VALIDATEDPOSITION_H_ */
