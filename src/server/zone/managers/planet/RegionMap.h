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
	VectorMap<String, ManagedReference<Region*> > regions;

public:
	RegionMap() {
		addSerializableVariable("regions", &regions);
		regions.setNoDuplicateInsertPlan();
		regions.setNullValue(NULL);
	}

	~RegionMap() {

	}

	void addRegion(const String& name, float x, float y, float radius) {
		StringId nameid;
		nameid.setStringId(name);

		Region* region = regions.get(nameid.getStringID());

		if (region == NULL) {
			region = new Region(name, x, y, radius);
			region->deploy();
			regions.put(nameid.getStringID(), region);
		} else {
			region->addPoint(x, y, radius);
		}
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

	inline Region* getRegion(const String& name) {
		return regions.get(name);
	}

	bool getRegion(StringId* name, float x, float y) {
		for (int i = 0; i < regions.size(); ++i) {
			Region* region = regions.get(i);

			if (region->containsPoint(x, y)) {
				name = region->getName();

				return true;
			}
		}

		return false;
	}

	inline int size() {
		return regions.size();
	}
};


#endif /* REGIONMAP_H_ */
