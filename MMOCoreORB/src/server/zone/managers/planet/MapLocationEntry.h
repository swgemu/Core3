/*
 * MapLocationEntry.h
 *
 *  Created on: 18/06/2010
 *      Author: victor
 */

#ifndef MAPLOCATIONENTRY_H_
#define MAPLOCATIONENTRY_H_

#include "engine/engine.h"
#include "PlanetMapCategory.h"

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
	Reference<PlanetMapCategory*> planetMapCategory;

public:
	MapLocationEntry() {

	}

	MapLocationEntry(SceneObject* obj, PlanetMapCategory* pmc) {
		object = obj;

		planetMapCategory = pmc;
	}

	MapLocationEntry(const MapLocationEntry& entry) : Object() {
		object = entry.object;
		planetMapCategory = entry.planetMapCategory;
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

	inline void setPlanetMapCategory(PlanetMapCategory* pmc) {
		planetMapCategory = pmc;
	}

	inline PlanetMapCategory* getPlanetMapCategory() {
		return planetMapCategory.get();
	}
};


#endif /* MAPLOCATIONENTRY_H_ */
