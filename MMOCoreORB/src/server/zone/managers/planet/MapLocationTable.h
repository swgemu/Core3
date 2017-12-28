/*
 * MapLocationTable.h
 *
 *  Created on: 18/06/2010
 *      Author: victor
 */

#ifndef MAPLOCATIONTABLE_H_
#define MAPLOCATIONTABLE_H_

#include <algorithm>

#include "MapLocationEntry.h"
#include "engine/stm/mm/TransactionalObjectCloner.h"
#include "system/lang/Object.h"
#include "system/lang/String.h"
#include "system/mm/ObjectCloner.h"
#include "system/platform.h"
#include "system/thread/ReadWriteLock.h"
#include "system/util/SortedVector.h"
#include "system/util/VectorMap.h"


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

	bool containsObject(SceneObject* object);

	void updateObjectsIcon(SceneObject* object, byte icon);

	SortedVector<MapLocationEntry>& getLocation(const String& name);

	SortedVector<MapLocationEntry>& get(int index) {
		return locations.elementAt(index).getValue();
	}

	int findLocation(const String& name);

	int size() {
		return locations.size();
	}
};

#endif /* MAPLOCATIONTABLE_H_ */
