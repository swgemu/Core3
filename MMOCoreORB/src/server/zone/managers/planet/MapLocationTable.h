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

class MapLocationTable : public VectorMap<String, SortedVector<MapLocationEntry> >, public ReadWriteLock {
public:
	void addObject(SceneObject* object);

	void dropObject(SceneObject* object);
};

#endif /* MAPLOCATIONTABLE_H_ */
