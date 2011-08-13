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
#include "server/zone/objects/area/DynamicSpawnArea.h"
#include "server/zone/objects/area/StaticSpawnArea.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/object/ObjectManager.h"

class SpawnAreaMap : public VectorMap<uint32, ManagedReference<SpawnArea*> > , public Logger {
	Lua* lua;
protected:
	ManagedReference<Zone*> zone;

	Vector<ManagedReference<SpawnArea*> > noSpawnAreas;

	void readAreaObject(LuaObject& areaObj);
	void loadStaticSpawns();

public:
	SpawnAreaMap() : Logger("SpawnAreaMap") {
		lua = new Lua();
		setAllowDuplicateInsertPlan();
	}

	virtual ~SpawnAreaMap() {
		delete lua;
		lua = NULL;
	}

	void loadMap(Zone* z);
};


#endif /* SPAWNAREAMAP_H_ */
