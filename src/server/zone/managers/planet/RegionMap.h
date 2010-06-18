/*
 * RegionMap.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef REGIONMAP_H_
#define REGIONMAP_H_

#include "engine/engine.h"

#include "server/zone/objects/region/Region.h"
#include "server/zone/managers/object/ObjectManager.h"

class RegionMap : public Serializable {
	SortedVector<ManagedReference<Region*> > regions;

public:
	RegionMap() {
		addSerializableVariable("regions", &regions);
		regions.setNoDuplicateInsertPlan();
	}

	~RegionMap() {

	}

	void addRegion(Zone* zone, const String& name, float x, float y, float radius) {
		uint32 crc = String("object/region_area.iff").hashCode();

		Region* region = (Region*) ObjectManager::instance()->createObject(crc, 0, "");
		region->initializePosition(x, 0, y);
		region->setRadius(radius);
		StringId* objectName = region->getObjectName();
		objectName->setStringId(name);

		region->insertToZone(zone);

		regions.put(region);
	}

	Region* getRegion(float x, float y) {
		Region* region = NULL;

		for (int i = 0; i < regions.size(); ++i) {
			region = regions.get(i);

			if (region->containsPoint(x, y)) {
				return region;
			}
		}

		return NULL;
	}

	inline Region* getRegion(int index) {
		return regions.get(index);
	}

	inline int size() {
		return regions.size();
	}
};


#endif /* REGIONMAP_H_ */
