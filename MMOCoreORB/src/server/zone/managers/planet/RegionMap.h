/*
 * RegionMap.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef REGIONMAP_H_
#define REGIONMAP_H_

#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/region/Region.h"

class RegionMap : public ReadWriteLock, public Object, public Logger {
	VectorMap<String, ManagedReference<CityRegion*> > cityRegions;

	VectorMap<String, ManagedReference<Region*> > regions;

public:
	RegionMap() {
		cityRegions.setNoDuplicateInsertPlan();
		cityRegions.setNullValue(nullptr);

		regions.setNoDuplicateInsertPlan();
		regions.setNullValue(nullptr);

		setLoggingName("Region Map");
	}

	~RegionMap() {
	}

	inline void addCityRegion(CityRegion* cityRegion) {
		wlock();

		cityRegions.put(cityRegion->getCityRegionName(), cityRegion);

		unlock();
	}

	inline void dropCityRegion(const String& regionName) {
		wlock();

		cityRegions.drop(regionName);

		unlock();
	}

	inline void addRegion(Region* region) {
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
	 * Gets the first city region in the region map found at the specified coordinates.
	 * @param x The x coordinate.
	 * @param y The y coordinate.
	 * @return Returns a city region or nullptr if one was not found.
	 */
	CityRegion* getCityRegionAt(float x, float y) {
		rlock();

		for (int i = 0; i < cityRegions.size(); ++i) {
			CityRegion* cityRegion = cityRegions.get(i);

			if (cityRegion->containsPoint(x, y)) {
				runlock();
				return cityRegion;
			}
		}

		runlock();

		return nullptr;
	}

	/**
	 * Gets the first city region in the region map found at the specified coordinates.
	 * @param x The x coordinate.
	 * @param y The y coordinate.
	 * @return Returns a city region or nullptr if one was not found.
	 */
	Region* getRegionAt(float x, float y) {
		rlock();

		for (int i = 0; i < cityRegions.size(); ++i) {
			Region* region = regions.get(i);

			if (region->containsPoint(x, y)) {
				runlock();
				return region;
			}
		}

		runlock();

		return nullptr;
	}

	inline bool containsCityRegion(const String& name) {
		return cityRegions.contains(name);
	}

	inline bool containsRegion(const String& name) {
		return regions.contains(name);
	}

	inline CityRegion* getCityRegion(int index) {
		return cityRegions.get(index);
	}

	inline CityRegion* getCityRegion(const String& name) {
		return cityRegions.get(name);
	}

	inline int getTotalCityRegions() {
		return cityRegions.size();
	}

	inline Region* getRegion(int index) {
		return regions.get(index);
	}

	inline Region* getRegion(const String& name) {
		return regions.get(name);
	}

	inline int getTotalRegions() {
		return regions.size();
	}
};


#endif /* REGIONMAP_H_ */
