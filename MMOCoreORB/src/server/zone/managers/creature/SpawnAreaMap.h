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

	static const int UNDEFINEDAREA       = 0x00000000;
	static const int SPAWNAREA           = 0x00000001;
	static const int NOSPAWNAREA         = 0x00000002;
	static const int WORLDSPAWNAREA      = 0x00000010;
	static const int NOBUILDZONEAREA     = 0x00000100;

	SpawnAreaMap() : Logger("SpawnAreaMap") {
		lua = new Lua();
		setAllowDuplicateInsertPlan();
	}

	SpawnAreaMap(const SpawnAreaMap& l) : VectorMap<uint32, ManagedReference<SpawnArea*> >(l) , Logger("SpawnAreaMap") {
		lua = l.lua;

		noSpawnAreas = l.noSpawnAreas;
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
