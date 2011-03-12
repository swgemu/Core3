/*
 * WorldCoordinate.h
 *
 *  Created on: 02/03/2011
 *      Author: victor
 */

#ifndef WORLDCOORDINATES_H_
#define WORLDCOORDINATES_H_

#include "engine/engine.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
   	   class SceneObject;
   }
  }
 }
}

using namespace server::zone::objects::scene;

class WorldCoordinates : public Object {
protected:
	Vector3 point;

	ManagedReference<SceneObject*> cell;

public:
	WorldCoordinates();
	WorldCoordinates(const WorldCoordinates& c);
	WorldCoordinates(SceneObject* obj);
	WorldCoordinates(const Vector3& position, SceneObject* cell);

	WorldCoordinates& operator=(const WorldCoordinates& c);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	bool isInRange(const WorldCoordinates& obj, float range) const;

	Vector3 getWorldPosition() const;

	inline void setCell(SceneObject* obj) {
		cell = obj;
	}

	inline void setCoordinates(const Vector3& pos) {
		point = pos;
	}

	inline void setX(float x) {
		point.setX(x);
	}

	inline void setY(float y) {
		point.setY(y);
	}

	inline void setZ(float z) {
		point.setZ(z);
	}

	inline Vector3 getPoint() const {
		return point;
	}

	inline SceneObject* getCell() const {
		return cell;
	}

	inline float getX() const {
		return point.getX();
	}

	inline float getY() const {
		return point.getY();
	}

	inline float getZ() const {
		return point.getZ();
	}

};


#endif /* WORLDCOORDINATE_H_ */
