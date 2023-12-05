/*
 * MapLocationTable.h
 *
 *  Created on: 18/06/2010
 *      Author: victor
 */

#ifndef MAPLOCATIONTABLE_H_
#define MAPLOCATIONTABLE_H_

#include "MapLocationEntry.h"


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

class MapLocationTable : public Object, public ReadWriteLock {
	VectorMap<String, SortedVector<MapLocationEntry> > locations;

public:
	MapLocationTable() {
		locations.setNoDuplicateInsertPlan();
	}

	MapLocationTable(const MapLocationTable& t) : Object(), ReadWriteLock() {
		locations = t.locations;
	}

	Object* clone() {
		return ObjectCloner<MapLocationTable>::clone(this);
	}

	Object* clone(void* object) {
		return TransactionalObjectCloner<MapLocationTable>::clone(this);
	}

	void transferObject(SceneObject* object);

	void dropObject(SceneObject* object);

	bool containsObject(SceneObject* object) const;

	void updateObjectsIcon(SceneObject* object, byte icon);

	const SortedVector<MapLocationEntry> getLocation(const String& name) const;

	const SortedVector<MapLocationEntry>& get(int index) const {
		return locations.elementAt(index).getValue();
	}

	int findLocation(const String& name) const;

	int size() const {
		return locations.size();
	}
};

#endif /* MAPLOCATIONTABLE_H_ */
