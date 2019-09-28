/*
 * SpawnAreaMap.h
 *
 *  Created on: Nov 2, 2010
 *      Author: da
 */

#ifndef SPAWNAREAMAP_H_
#define SPAWNAREAMAP_H_

#include "server/zone/objects/area/SpawnArea.h"
#include "server/zone/Zone.h"

class SpawnAreaMap : public SynchronizedVectorMap<uint32, ManagedReference<SpawnArea*> > , public Logger {
	Lua* lua;
protected:

	ManagedReference<Zone*> zone;

	SynchronizedVector<ManagedReference<SpawnArea*> > noSpawnAreas;

	SynchronizedVector<ManagedReference<SpawnArea*> > worldSpawnAreas;

	void readAreaObject(LuaObject& areaObj);
	void loadRegions();

public:

	enum {
		UNDEFINEDAREA       = 0x00000000,
		SPAWNAREA           = 0x00000001,
		NOSPAWNAREA         = 0x00000002,
		WORLDSPAWNAREA      = 0x00000010,
		NOWORLDSPAWNAREA    = 0x00000020,
		NOBUILDZONEAREA     = 0x00000100
	};

	enum {
		CIRCLE = 1,
		RECTANGLE,
		RING
	};

	SpawnAreaMap() : Logger("SpawnAreaMap") {
		lua = new Lua();
		setAllowDuplicateInsertPlan();
	}

	SpawnAreaMap(const SpawnAreaMap& l) : SynchronizedVectorMap<uint32, ManagedReference<SpawnArea*> >(l) , Logger("SpawnAreaMap"),
			zone(l.zone), noSpawnAreas(l.noSpawnAreas), worldSpawnAreas(l.worldSpawnAreas) {

		lua = l.lua;
	}

	virtual ~SpawnAreaMap() {
		if (lua != nullptr) {
			delete lua;
			lua = nullptr;
		}
	}

	void loadMap(Zone* z);

	void unloadMap();

	SynchronizedVector<ManagedReference<SpawnArea*> >* getWorldSpawnAreas() {
		return &worldSpawnAreas;
	}

};


#endif /* SPAWNAREAMAP_H_ */
