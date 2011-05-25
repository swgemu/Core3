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

class SpawnAreaMap : public VectorMap<uint32, ManagedReference<SpawnArea*> > {
protected:
	Zone* zone;

	Vector<ManagedReference<SpawnArea*> > noSpawnAreas;

	Lua* luaInstance;

public:
	SpawnAreaMap() {
		setAllowDuplicateInsertPlan();
		luaInstance = new Lua();
	}

	virtual ~SpawnAreaMap() {}

	void loadMap(Zone* z) {
		zone = z;
		String planetName = zone->getPlanetName();

		luaInstance->init();

		luaInstance->runFile("scripts/managers/spawn_manager/" + planetName + ".lua");

		LuaObject obj = luaInstance->getGlobalObject(planetName + "_regions");

		if (obj.isValidTable()) {
			lua_State* s = obj.getLuaState();

			for (int i = 1; i <= obj.getTableSize(); ++i) {
				lua_rawgeti(s, -1, i);
				LuaObject areaObj(s);

				if (areaObj.isValidTable()) {
					String name = areaObj.getStringAt(1);
					float x = areaObj.getFloatAt(2);
					float y = areaObj.getFloatAt(3);
					float radius = areaObj.getFloatAt(4);
					int tier = areaObj.getIntAt(5);
					int constant = areaObj.getIntAt(6);

					uint32 crc;
					if (tier < 2)
						crc = String("object/static_spawn_area.iff").hashCode();
					else
						crc = String("object/dynamic_spawn_area.iff").hashCode();

					ManagedReference<SpawnArea*> area = dynamic_cast<SpawnArea*>(ObjectManager::instance()->createObject(crc, 2, "spawnareas"));
					if (area == NULL)
						continue;

					StringId nameID(planetName + "_region_names", name);

					area->setObjectName(nameID);

					area->setPosition(x, 0, y);

					area->setRadius(radius);

					area->setTier(tier);

					area->setSpawnConstant(constant);

					for (int j = 7; j <= areaObj.getTableSize(); ++j)
						area->addTemplate(areaObj.getStringAt(j).hashCode());

					area->insertToZone(zone);

					area->updateToDatabase();

					put(nameID.getStringID().hashCode(), area);

					if (area->isStaticArea()) {
						noSpawnAreas.add(area);
						if (tier == 1) {
							StaticSpawnArea* staticArea = (StaticSpawnArea*)area.get();
							staticArea->spawnCreatures();
						}
					}
				}

				areaObj.pop();
			}
		}

		luaInstance->deinit();

		for (int i = 0; i < size(); ++i) {
			SpawnArea* area = get(i);
			if (area->isDynamicArea()) {
				DynamicSpawnArea* dynamicArea = (DynamicSpawnArea*)area;

				Vector3 d(dynamicArea->getPositionX(), dynamicArea->getPositionY(), 0);

				for (int j = 0; j < noSpawnAreas.size(); ++j) {
					SpawnArea* notHere = noSpawnAreas.get(j);
					Vector3 offset(notHere->getPosition());

					if (d.distanceTo(offset) < dynamicArea->getRadius() + notHere->getRadius())
						dynamicArea->addNoSpawnArea(notHere);
				}
			}
		}
	}
};


#endif /* SPAWNAREAMAP_H_ */
