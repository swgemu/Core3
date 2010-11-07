/*
 * SpawnAreaMap.h
 *
 *  Created on: Nov 2, 2010
 *      Author: da
 */

#ifndef SPAWNAREAMAP_H_
#define SPAWNAREAMAP_H_

#include "engine/engine.h"
#include "server/zone/objects/area/DynamicSpawnArea.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/object/ObjectManager.h"

class SpawnAreaMap : public VectorMap<uint32, ManagedReference<DynamicSpawnArea*> >, private Lua {
protected:
	Zone* zone;

	Vector<ManagedReference<DynamicSpawnArea*> > noSpawnAreas;

public:
	SpawnAreaMap() {
		setAllowDuplicateInsertPlan();
	}

	virtual ~SpawnAreaMap() {}

	void loadMap(Zone* z) {
		zone = z;
		String planetName = zone->getPlanetName();

		Lua::init();

		runFile("scripts/managers/spawn_manager/" + planetName + ".lua");

		LuaObject obj = getGlobalObject(planetName + "_regions");

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

					uint32 crc = String("object/dynamic_spawn_area.iff").hashCode();
					ManagedReference<DynamicSpawnArea*> area = dynamic_cast<DynamicSpawnArea*>(ObjectManager::instance()->createObject(crc, 2, "spawnareas"));

					StringId nameID(planetName + "_region_names", name);
					area->setObjectName(nameID);

					area->setPosition(x, 0, y);

					area->setRadius(radius);

					area->setTier(tier);

					area->setSpawnConstant(constant);

					for (int j = 7; j <= areaObj.getTableSize(); ++j)
						area->addTemplate(areaObj.getStringAt(j).hashCode());

					area->insertToZone(zone);

					put(nameID.getStringID().hashCode(), area);

					if (tier < 2)
						noSpawnAreas.add(area);
				}

				areaObj.pop();
			}
		}

		Lua::deinit();

		for (int i = 0; i < size(); ++i) {
			ManagedReference<DynamicSpawnArea*> area = get(i);
			Vector3 d(area->getPositionX(), area->getPositionY(), 0);

			for (int j = 0; j < noSpawnAreas.size(); ++j) {
				ManagedReference<DynamicSpawnArea*> notHere = noSpawnAreas.get(j);
				Vector3 offset(notHere->getPosition());

				if (d.distanceTo(offset) < area->getRadius() + notHere->getRadius())
					area->addNoSpawnArea(notHere);
			}
		}
	}
};


#endif /* SPAWNAREAMAP_H_ */
