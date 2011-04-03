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
		region->setClientObject(true);
		StringId* objectName = region->getObjectName();
		objectName->setStringId(name);

		region->insertToZone(zone);

		regions.put(region);
	}

	inline void addRegion(Region* region) {
		regions.put(region);
	}

	inline void dropRegion(Region* region) {
		regions.drop(region);
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

	Vector<ManagedReference<Region*> > getRegions(StringId* regionName) {
		Vector<ManagedReference<Region*> > regionsToReturn;
		String fullId;
		regionName->getFullPath(fullId);

		for (int i = 0; i < regions.size(); ++i) {
			Region* region = regions.get(i);

			StringId* objectName = region->getObjectName();
			//UnicodeString custom = objectName->getCustomString();

			String fullPath;
			objectName->getFullPath(fullPath);

			if (fullPath == fullId)
				regionsToReturn.add(region);
		}

		return regionsToReturn;
	}

	bool containsRegion(const String& name) {
		for (int i = 0; i < regions.size(); ++i) {
			Region* region = regions.get(i);

			StringId* objectName = region->getObjectName();
			UnicodeString custom = objectName->getCustomString();

			String lowName = name.toLowerCase();
			String customName = custom.toString().toLowerCase();
			String file = objectName->getStringID();

			if (customName.indexOf(lowName) != -1)
				return true;

			if (file.indexOf(lowName) != -1)
				return true;
		}

		return false;
	}

	inline Region* getRegion(int index) {
		return regions.get(index);
	}

	inline int size() {
		return regions.size();
	}
};


#endif /* REGIONMAP_H_ */
