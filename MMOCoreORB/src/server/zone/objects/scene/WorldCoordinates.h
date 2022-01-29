/*
 * WorldCoordinate.h
 *
 *  Created on: 02/03/2011
 *      Author: victor
 */

#ifndef WORLDCOORDINATES_H_
#define WORLDCOORDINATES_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

#include "server/zone/objects/cell/CellObject.h"

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
	ManagedReference<CellObject*> cell;

public:
	WorldCoordinates();
	WorldCoordinates(const WorldCoordinates& c);
	WorldCoordinates(SceneObject* obj);
	WorldCoordinates(const Vector3& position, CellObject* cell);

#ifdef CXX11_COMPILER
	WorldCoordinates(WorldCoordinates&& c) : Object(), point(c.point), cell(std::move(c.cell)) {

	}
#endif

	WorldCoordinates& operator=(const WorldCoordinates& c);

#ifdef CXX11_COMPILER
	WorldCoordinates& operator=(WorldCoordinates&& c) {
		if (this == &c)
			return *this;

		point = c.point;
		cell = std::move(c.cell);

		return *this;
	}
#endif

	bool operator==(const WorldCoordinates& c) {
		return (point == c.point) && (cell == c.cell);
	}

	friend void to_json(nlohmann::json& j, const WorldCoordinates& c) {
		j["point"] = c.point;
		j["cell"] = c.cell;
	}

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	bool isInRange(const WorldCoordinates& obj, float range) const;

	Vector3 getWorldPosition() const;

	inline void setCell(CellObject* obj) {
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

	inline const Vector3& getPoint() const {
		return point;
	}

	inline Vector3 getPoint() {
		return point;
	}

	inline CellObject* getCell() const {
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

	inline String toString() const {
		StringBuffer buf;

		buf <<"WorldCoordinates(x:" << point.getX()
			<< ", y:" << point.getY()
			<< ", z:" << point.getZ()
			<< ", cell: ";

		if (cell == nullptr) {
			buf << "nullptr";
		} else {
			buf << cell->getCellNumber();
		}

		buf << ")";

		return buf.toString();
	}

	String toStringData() const {
		return toString();
	}
};


#endif /* WORLDCOORDINATE_H_ */
