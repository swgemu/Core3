/*
 * MapLocationEntry.h
 *
 *  Created on: 18/06/2010
 *      Author: victor
 */

#ifndef MAPLOCATIONENTRY_H_
#define MAPLOCATIONENTRY_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {

class SceneObject;

} // namespace scene
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::scene;

class MapLocationEntry : public Object {
	ManagedReference<SceneObject*> object;
	int mapLoc1;
	int mapLoc2;
	int mapLoc3;

public:
	MapLocationEntry() {
		mapLoc1 = 0;
		mapLoc2 = 0;
		mapLoc3 = 0;
	}

	MapLocationEntry(SceneObject* obj, const int type1, const int type2, const int type3) {
		object = obj;

		mapLoc1 = type1;
		mapLoc2 = type2;
		mapLoc3 = type3;
	}

	MapLocationEntry(const MapLocationEntry& entry) : Object() {
		object = entry.object;
		mapLoc1 = entry.mapLoc1;
		mapLoc2 = entry.mapLoc2;
		mapLoc3 = entry.mapLoc3;
	}

	int compareTo(const MapLocationEntry& entry) const;

	MapLocationEntry& operator=(const MapLocationEntry& entry);

	inline void setObject(SceneObject* obj) {
		object = obj;
	}

	inline SceneObject* getObject() {
		return object;
	}

	uint64 getObjectID() const;

	inline void setType1(int type) {
		mapLoc1 = type;
	}

	inline void setType2(int type) {
		mapLoc2 = type;
	}

	inline void setType3(int type) {
		mapLoc3 = type;
	}

	inline int getType1() {
		return mapLoc1;
	}

	inline int getType2() {
		return mapLoc2;
	}

	inline int getType3() {
		return mapLoc3;
	}
};


#endif /* MAPLOCATIONENTRY_H_ */
