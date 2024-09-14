/*
 * SpaceRegionMap.h
 *
 *	Created on: 30/01/2010
 *	Author: victor
 */

#ifndef SPACEREGIONMAP_H_
#define SPACEREGIONMAP_H_

#include "server/zone/objects/region/space/SpaceRegion.h"

class SpaceRegionMap : public ReadWriteLock, public Object, public Logger {
	VectorMap<String, ManagedReference<SpaceRegion*> > regions;

public:
	SpaceRegionMap() {
		regions.setNoDuplicateInsertPlan();
		regions.setNullValue(nullptr);

		setLoggingName("SpaceRegionMap");
	}

	~SpaceRegionMap() {
	}

	inline void addRegion(SpaceRegion* region) {
		wlock();

		regions.put(region->getAreaName(), region);

		unlock();
	}

	inline void dropRegion(const String& regionName) {
		wlock();

		regions.drop(regionName);

		unlock();
	}

	/**
	 * Gets the first region in the region map found at the specified coordinates.
	 * @param x The x coordinate.
	 * @param y The y coordinate.
	 * @return Returns a city region or nullptr if one was not found.
	 */
	SpaceRegion* getRegionAt(float x, float y) {
		rlock();

		for (int i = 0; i < regions.size(); ++i) {
			SpaceRegion* region = regions.get(i);

			if (region->containsPoint(x, y)) {
				runlock();
				return region;
			}
		}

		runlock();

		return nullptr;
	}

	inline bool containsRegion(const String& name) {
		return regions.contains(name);
	}

	inline SpaceRegion* getRegion(int index) {
		return regions.get(index);
	}

	inline SpaceRegion* getRegion(const String& name) {
		return regions.get(name);
	}

	inline int getTotalRegions() {
		return regions.size();
	}
};

#endif /* SPACEREGIONMAP_H_ */
