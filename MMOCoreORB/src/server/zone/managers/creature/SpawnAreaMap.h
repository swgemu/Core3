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

public:
	SpawnAreaMap() : Logger("SpawnAreaMap") {
		setAllowDuplicateInsertPlan();
	}

	SpawnAreaMap(const SpawnAreaMap& l) : SynchronizedVectorMap<uint32, ManagedReference<SpawnArea*> >(l) , Logger("SpawnAreaMap"),
		zone(l.zone), noSpawnAreas(l.noSpawnAreas) {
	}

	SpawnAreaMap& operator=(const SpawnAreaMap& m) {
		if (this == &m) {
			return *this;
		}

		zone = m.zone;
		noSpawnAreas = m.noSpawnAreas;

		return *this;
	}

	virtual ~SpawnAreaMap() {
	}

	void unloadMap();

	void addSpawnArea(uint32 spawnHash, ManagedReference<SpawnArea*> area) {
		put(spawnHash, area);
	}

	void addNoSpawnArea(ManagedReference<SpawnArea*> area) {
		noSpawnAreas.add(area);
	}
};


#endif /* SPAWNAREAMAP_H_ */
