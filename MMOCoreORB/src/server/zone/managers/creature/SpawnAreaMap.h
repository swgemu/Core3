/*
 * SpawnAreaMap.h
 *
 *  Created on: Nov 2, 2010
 *      Author: da
 */

#ifndef SPAWNAREAMAP_H_
#define SPAWNAREAMAP_H_

#include "engine/engine.h"
#include "server/zone/objects/area/SpawnArea.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/object/ObjectManager.h"

class SpawnAreaMap : public VectorMap<uint32, ManagedReference<SpawnArea*> > , public Logger {
	Lua* lua;
protected:

	ManagedReference<Zone*> zone;

	Vector<ManagedReference<SpawnArea*> > noSpawnAreas;

	Vector<ManagedReference<SpawnArea*> > worldSpawnAreas;

	Vector<Vector3> trainerObjects;

	void readAreaObject(LuaObject& areaObj);
	void loadStaticSpawns();

public:

	enum {
		UNDEFINEDAREA       = 0x00000000,
		SPAWNAREA           = 0x00000001,
		NOSPAWNAREA         = 0x00000002,
		WORLDSPAWNAREA      = 0x00000010,
		NOBUILDZONEAREA     = 0x00000100
	};

	SpawnAreaMap() : Logger("SpawnAreaMap") {
		lua = new Lua();
		setAllowDuplicateInsertPlan();
	}

	SpawnAreaMap(const SpawnAreaMap& l) : VectorMap<uint32, ManagedReference<SpawnArea*> >(l) , Logger("SpawnAreaMap"),
			zone(l.zone), noSpawnAreas(l.noSpawnAreas), worldSpawnAreas(l.worldSpawnAreas), trainerObjects(l.trainerObjects) {

		lua = l.lua;
	}

	virtual ~SpawnAreaMap() {
		if (lua != NULL) {
			delete lua;
			lua = NULL;
		}
	}

	void loadMap(Zone* z);

	Vector3 getRandomJediTrainer();

	Vector<ManagedReference<SpawnArea*> >* getWorldSpawnAreas() {
		return &worldSpawnAreas;
	}

};


#endif /* SPAWNAREAMAP_H_ */
