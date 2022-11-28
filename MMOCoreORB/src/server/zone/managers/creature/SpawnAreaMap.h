/*
 * SpawnAreaMap.h
 *
 *  Created on: Nov 2, 2010
 *      Author: da
 */

#ifndef SPAWNAREAMAP_H_
#define SPAWNAREAMAP_H_

#include "server/zone/objects/region/SpawnArea.h"
#include "server/zone/Zone.h"

class SpawnAreaMap : public SynchronizedVectorMap<uint32, ManagedReference<SpawnArea*> > , public Logger {
protected:

	ManagedReference<Zone*> zone;

	SynchronizedVector<ManagedReference<SpawnArea*> > noSpawnAreas;

	SynchronizedVector<ManagedReference<SpawnArea*> > worldSpawnAreas;

public:
	SpawnAreaMap() : Logger("SpawnAreaMap") {
		setAllowDuplicateInsertPlan();
	}

	SpawnAreaMap(const SpawnAreaMap& l) : SynchronizedVectorMap<uint32, ManagedReference<SpawnArea*> >(l) , Logger("SpawnAreaMap"),
			zone(l.zone), noSpawnAreas(l.noSpawnAreas), worldSpawnAreas(l.worldSpawnAreas) {
	}

	SpawnAreaMap& operator=(const SpawnAreaMap& m) {
		if (this == &m) {
			return *this;
		}

		zone = m.zone;
		noSpawnAreas = m.noSpawnAreas;
		worldSpawnAreas = m.worldSpawnAreas;

		return *this;
	}

	virtual ~SpawnAreaMap() {
	}

	void unloadMap();

	SynchronizedVector<ManagedReference<SpawnArea*> >* getWorldSpawnAreas() {
		return &worldSpawnAreas;
	}

	void addSpawnArea(uint32 spawnHash, ManagedReference<SpawnArea*> area) {
		put(spawnHash, area);
	}

	void addWorldSpawnArea(ManagedReference<SpawnArea*> area) {
		worldSpawnAreas.add(area);
	}

	void addNoSpawnArea(ManagedReference<SpawnArea*> area) {
		noSpawnAreas.add(area);
	}
};


#endif /* SPAWNAREAMAP_H_ */
