/*
 * RegionMap.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef REGIONMAP_H_
#define REGIONMAP_H_

#include "engine/engine.h"

#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/object/ObjectManager.h"

class RegionMap : public ReadWriteLock, public Object {
	VectorMap<String, ManagedReference<CityRegion*> > regions;

public:
	RegionMap() {
		regions.setNoDuplicateInsertPlan();
		regions.setNullValue(NULL);
	}

	~RegionMap() {
	}

	inline void addRegion(CityRegion* region) {
		wlock();

		regions.put(region->getRegionName(), region);

		unlock();
	}

	inline void dropRegion(const String& regionName) {
		wlock();

		regions.drop(regionName);

		unlock();
	}

	CityRegion* getRegion(float x, float y) {
		rlock();

		for (int i = 0; i < regions.size(); ++i) {
			ManagedReference<CityRegion*> region = regions.get(i);

			if (region->containsPoint(x, y)) {
				runlock();

				return region;
			}
		}

		runlock();

		return NULL;
	}

	/**
	 * Gets the first city region in the region map found at the specified coordinates.
	 * @param x The x coordinate.
	 * @param y The y coordinate.
	 * @return Returns a city region or NULL if one was not found.
	 */
	CityRegion* getCityRegionAt(float x, float y) {
		rlock();

		for (int i = 0; i < regions.size(); ++i) {
			ManagedReference<CityRegion*> cityRegion = regions.get(i);

			if (cityRegion->containsPoint(x, y)) {
				runlock();
				return cityRegion;
			}
		}

		runlock();

		return NULL;
	}

	Vector<ManagedReference<CityRegion*> > getRegions(StringId* regionName) {
		Vector<ManagedReference<CityRegion*> > matches;

		rlock();

		for (int i = 0; i < regions.size(); ++i) {
			ManagedReference<CityRegion*> region = regions.get(i);

			if (region->getRegionName() == regionName->getDisplayedName())
				matches.add(region);
		}

		runlock();

		return matches;
	}

	inline bool containsRegion(const String& name) {
		return regions.contains(name);
	}

	inline CityRegion* getRegion(int index) {
		return regions.get(index);
	}

	inline CityRegion* getRegion(const String& name) {
		return regions.get(name);
	}

	inline int getTotalRegions() {
		return regions.size();
	}
};


#endif /* REGIONMAP_H_ */
